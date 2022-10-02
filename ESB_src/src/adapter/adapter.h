#include "bmd_handler/bmd.h"
#ifndef ADAPTER_H
#define ADAPTER_H
/* Function that dynamically calls required transport and transform*/
char *call_function(const char *name, void *data, void *data1);

typedef struct transport_config {
    char *key;
    char *value;
}transport_t,transform_t,config_t;

char * payload_to_json(bmd *bmd_file,char* url);

char * payload_to_xml(bmd *bmd_file);

/* Email */
void* send_mail(void *toptr, void *file_path_ptr);

/* Destination Service ifsc */
void* call_destination_service(void *urlptr,void *apiptr);

/* Posts to destination */
void* http_post(void *toptr, void *dataptr);

/* SFTP upload */
void *sftp_upload(void *asptr, void *fileptr);

/* Can be used to print HTTP response */
int print_file(char *file_name);


#endif