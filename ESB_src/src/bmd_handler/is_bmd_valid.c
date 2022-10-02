/**
 * @file is_bmd_valid.c
 * @author MubeenS
 * @brief 
 * @version 0.1
 * @date 2020-09-08
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <stdio.h>

/* xml handling library */
#include <libxml/parser.h>

#include <stdlib.h>
#include <string.h>

/* BMD structure */
#include "bmd.h"
/* DB access function declarations */
#include "db_access/connector.h"

#include "adapter/adapter.h"
int is_bmd_complete(bmd *bmd_file);

#define STRING_SIZE 100

#define VALID 1
#define INVALID 0
/* Size definiton for 5MB */
#define MAX_SIZE 5000000

/**
 * @brief Check if bmd has all
 * mandatory fields.
 * 
 * @param bmd_file to be checked
 * @return int 1 if ok. INVALID if not
 */
int is_bmd_complete(bmd *bmd_file)
{

  /* MessageID */
  if (bmd_file->envelop_data->MessageID == NULL)
  {
    fprintf(stderr, "Message ID doesnot exist in bmd");
    return INVALID;
  }
  /*printf("MessageID :%s\n",bmd_file->envelop_data->MessageID);*/
  /* MessageType */
  if (bmd_file->envelop_data->MessageType == NULL)
  {
    fprintf(stderr, "Message Type doesnot exist in bmd");
    return INVALID;
  }
  /*printf("MessageType :%s\n",bmd_file->envelop_data->MessageType);*/
  /* Sender */
  if (bmd_file->envelop_data->Sender == NULL)
  {
    fprintf(stderr, "Sender doesnot exist in bmd");
    return INVALID;
  }
  /*printf("Sender :%s\n",bmd_file->envelop_data->Sender);*/

  /* Destination */
  if (bmd_file->envelop_data->Destination == NULL)
  {
    fprintf(stderr, "Destination doesnot exist in bmd");
    return INVALID;
  }
  /*printf("Destination :%s\n",bmd_file->envelop_data->Destination);*/

  /* CreationDateTime */
  if (bmd_file->envelop_data->CreationDateTime == NULL)
  {
    fprintf(stderr, "CreationDateTime doesnot exist in bmd");
    return INVALID;
  }
  /*printf("CreationDateTime :%s\n",bmd_file->envelop_data->CreationDateTime);*/

  /* Signature */
  if (bmd_file->envelop_data->Signature == NULL)
  {
    fprintf(stderr, "Signature doesnot exist in bmd");
    return INVALID;
  }
  /*printf("Signature :%s\n",bmd_file->envelop_data->Signature);*/
  /* ReferenceID */
  if (bmd_file->envelop_data->ReferenceID == NULL)
  {
    fprintf(stderr, "ReferenceID doesnot exist in bmd");
    return INVALID;
  }
  /*printf("ReferenceID :%s\n",bmd_file->envelop_data->ReferenceID);*/
  /* payload */
  if (bmd_file->payload == NULL)
  {
    fprintf(stderr, "Payload doesnot exist in bmd");
    return INVALID;
  }
  /*printf("Payload :%s\n",bmd_file->payload);*/
  printf("BMD is complete ☑\n");
  return VALID;
}

// C program to find the size of file
#include <stdio.h>

long int find_size(char file_name[])
{
  // opening the file in read mode
  FILE *fp = fopen(file_name, "r");

  // checking if the file exist or not
  if (fp == NULL)
  {
    printf("File Not Found!\n");
    return -1;
  }

  fseek(fp, 0L, SEEK_END);

  // calculating the size of the file
  long int res = ftell(fp);

  // closing the file
  fclose(fp);

  return res;
}

int is_bmd_valid(bmd *bmd_file)
{
  printf(">> Validating BMD..\n");
  /* Checks if BMD has all fields */
  if (!is_bmd_complete(bmd_file))
  {
    printf("Incomplete data.!\n");
    return INVALID;
  }
  int route_id;
  printf("To validate,");
  route_id = get_active_route_id(bmd_file->envelop_data->Sender,
                                 bmd_file->envelop_data->Destination,
                                 bmd_file->envelop_data->MessageType);
  /* Check if active routes are present */
  if (route_id == 0)
  {
    printf("No active routes are present.\n");
    return INVALID;
  }

  if (route_id < 0)
  {
    printf("Route_id fetching failed.\n");
    return INVALID;
  }

  printf("Has active route ☑\n");
  /* Checks if route has transform_config info */
  if (has_transform_config(route_id) <= 0)
  {
    printf("No transform configuration.\n");
    return INVALID;
  }
  printf("Has transform config ☑\n");
  /* Checks if route has transport_config info */
  if (has_transport_config(route_id) <= 0)
  {
    printf("No transport configuration.\n");
    return INVALID;
  }
  printf("Has transport config ☑\n");

  /* Checks size of payload file created */
  /* Generate HTTP url required to call
           destination service */
  char url[STRING_SIZE];

  transport_t *transport = fetch_transport_config(route_id);

  sprintf(url, "%s%s", transport->value, bmd_file->payload);
  //to_be_sent = (char *)call_function(transport->key, (void *)url,
  //  (void *)transport->key);
  /** Payload to json contacts destination service
          * Stores the received data in a file and returns
          * the file path.*/
  char *payload = payload_to_json(bmd_file, url);
  long int size = find_size(payload);
  /* Cleanup */
  int rc = remove(payload);
  if (rc != 0)
  {
    printf("File deletion failed.\n");
  }
  printf("Size under 5MB ☑\n");
  free(transport->key);
  free(transport->value);
  if (size > MAX_SIZE)
  {
    return INVALID;
  }
  return VALID;
}

/*int main () {
  bmd *bmd_file = parse_bmd_xml("bmd.xml");
  int check = is_bmd_valid(bmd_file);
  if(check == VALID) printf("valid");
  return 0;
}*/
