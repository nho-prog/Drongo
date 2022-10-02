#include <stdio.h>
#include "adapter/adapter.h"
#include "bmd_handler/bmd.h"

#ifndef ESB_H
#define ESB_H
/* A task tag that has request information */
typedef struct task {
    int id; /* Unique request_ID */
    char *sender;
    char *destination;
    char *message_type;
    char *data_location;
    int processing_attempts;
}task_t;

int queue_the_request(bmd *b,char *file_path);
int process_esb_request(char* bmd_file_path);
void *poll_database_for_new_requests(void *vargp);

/* Cleanup functions */
void free_bmd(bmd *b);
void free_req(task_t *t);
void free_config(config_t *config);
char *get_dir_name(const char *s);
void clean_dir(char *path);

#endif