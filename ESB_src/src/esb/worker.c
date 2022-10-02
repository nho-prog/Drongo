/**
 * @file worker.c
 * @author MubeenS
 * @brief A worker thread performs following operations:
 * 1.Fetches new request from database whose status = 'RECEIVED'
 * 2.Transforms if needed.
 * 3.Transports the payload to destination.
 * 4.Updates status of request in database.
 * 
 * @version 0.1
 * @date 2020-09-08
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <string.h>

#include <unistd.h>

#include "esb.h"

#include "db_access/connector.h"

#include "adapter/adapter.h"

#include <pthread.h>

#define STRING_SIZE 100
pthread_mutex_t lock;
void *poll_database_for_new_requests(void *vargp)
{
    while (true)
    {
        printf("\n%%%%%%%%%%");
        printf("\tWorker started\t");
        printf("%%%%%%%%%%\n");

        pthread_mutex_lock(&lock); 

        task_t *request = fetch_new_esb_request();
        if (request == NULL)
        {
            printf("No requests available.\n");
            pthread_mutex_unlock(&lock); 
            goto sleep;
        }
        else
        { /* Update request is being processed */
            update_esb_request("PROCESSING", request->id);
            pthread_mutex_unlock(&lock);
        }

         

        /* Get the route_id to handle the request */
        int route_id = get_active_route_id(request->sender,
                                           request->destination,
                                           request->message_type);

        /* Get transformation and transportation configuration */
        transform_t *transform = fetch_transform_config(route_id);
        transport_t *transport = fetch_transport_config(route_id);


        if (!(strcmp(transform->value, "No Transform")))
        {
            /** TODO: Invoke transform function.
              * For IFSC and EXCHNG rate no transform is needed.
              */
        }

        /* Parse xml file to get a bmd */
        bmd *bmd_file = parse_bmd_xml(request->data_location);

        /* String to store path of file to be sent */
        char *to_be_sent;

        /* Generate HTTP url required to call
           destination service */
        char url[STRING_SIZE];

        sprintf(url, "%s%s", transport->value, bmd_file->payload);

        /** Payload to json contacts destination service
          * Stores the received data in a file and returns
          * the file path.*/
        to_be_sent = payload_to_json(bmd_file, url);

        if (to_be_sent == NULL)
        {
            printf("Json creation failed.\n");
        }

        char *rc = call_function("EMAIL", "testmailtm02@gmail.com",
                                 to_be_sent);
        if (rc != NULL)
        {
            printf("Email sending failed.!\n");
            int status = update_esb_request("RECEIVED", request->id);
            if (status == 0)
            {
                printf("Update failed.!\n");
            }
        }
        else
        {
            printf("\n...............");
            printf("Mail sent");
            printf("...............\n");
        }

        char *response;
        /**
         * @brief REQ.RES is an api that gives
         * response to HTTP request. The response 
         * contains data sent along with creation time.
         * Choosen for testing purposes.
         * 
         */

        response = (char *)call_function("HTTP_POST",
                                         "https://reqres.in/api/users",
                                         to_be_sent);

        if (response == NULL)
        {
            printf("HTTP posting failed.!\n");
            int status = update_esb_request("RECEIVED", request->id);
            if (status == 0)
            {
                printf("Update failed.!\n");
            }
        }
        else
        {
            printf("\n...............");
            printf("Posted via HTTP.");
            printf("...............\n");
            printf("\n↓↓↓↓↓↓ File response from REQ.RES ↓↓↓↓↓↓\n");
            int check = print_file(response);
            if (check == 0)
            {
                printf("Printing response failed..\n");
            }
            printf("\n");
            update_esb_request("DONE", request->id);
            /* Exits the thread */
            //pthread_exit(NULL);
        }
        char *stat = sftp_upload(transform->key, to_be_sent);

        if (stat != NULL)
        {
            printf("SFTP upload failed ..\n");
        }

        else
        {
            printf("\n...............");
            printf("Uploaded via SFTP.");
            printf("...............\n\n");
        }

        /* Clean up */
        free(stat);
        int c = remove(response);
        if (c)
            printf("Removing response failed.\n");
        free(rc);
        c = remove(to_be_sent);
        if (c)
            printf("Removing payload failed.\n");
        free_bmd(bmd_file);
        free_config(transform);
        free_config(transport);
        free_req(request);
    sleep:
        printf("Sleeping for 5 seconds.\n");
        sleep(5);
    }
    printf("Worker exited..\n");
    // pthread_exit(NULL);
}

/*int main()
{

    pthread_t thread_id;
    printf("Before Thread\n");
    pthread_create(&thread_id, NULL, poll_database_for_new_requests, NULL);
    pthread_join(thread_id, NULL);
    printf("After Thread\n");
    return 0;
}*/