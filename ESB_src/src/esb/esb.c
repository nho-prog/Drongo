#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
/** Include Module that has bmd handling 
 * functions and  bmd structure declaration 
 * 
 */
#include "bmd_handler/bmd.h"

/** Module that has mysql C API functions */

#include "db_access/connector.h"

#include "adapter/adapter.h"
#include "esb.h"


int queue_the_request(bmd *b, char *file_path)
{
    int success = 1; // 1 => OK, -1 => Error cases

    /**
     * @brief Implements the Query:
     * INSERT INTO                            
     * esb_request(sender_id,dest_id,message_type,reference_id,      
     * message_id,data_location,status,status_details)               
     * VALUES(?,?,?,?,?,?,?,?)
     * function returns 1 on successful insertion. 
     * function is defined in db_access module
     */
    int rc = insert_to_esb_request(b->envelop_data->Sender,
                                   b->envelop_data->Destination,
                                   b->envelop_data->MessageType,
                                   b->envelop_data->ReferenceID,
                                   b->envelop_data->MessageID,
                                   file_path, "RECEIVED",
                                   "received successfully",
                                   b->envelop_data->CreationDateTime);
    if (rc >= 1)
    {
        return success;
    }

    return -1;
}

/**
 * This is the main entry point into the ESB. 
 * It will start processing of a BMD received at the HTTP endpoint.
 */
int process_esb_request(char *bmd_file_path)
{
    int status = connect_to_db();

    //int status = 1; // 1 => OK, -ve => Errors
    printf(">> Processing the BMD %s\n", bmd_file_path);

    /* Parse to extract bmd */
    bmd *b = parse_bmd_xml(bmd_file_path);

    /* Check if bmd is valid */
    if (is_bmd_valid(b) != 1)
    {
        //TODO: Process the error case
        printf("BMD is invalid! Try again with proper BMD\n");
        status = -2;
        clean_dir(bmd_file_path);
    }
    else
    {
        // Step 3:
        status = queue_the_request(b, bmd_file_path);
        if (status >= 0)
        {
            printf("Queued..!");
        }
        else
        {   
            printf("Request not inserted.\n");
            clean_dir(bmd_file_path);
        }
    }

    return status;
}

/*int main()
{
    int status = process_esb_request("../bmd_files/bmd3.xml");

    if (status != 1)
    {
        printf("Status[%d]: Request processing failed", status);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}*/