#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "esb.h"
#include "adapter/adapter.h"

void free_bmd(bmd *b)
{
    free(b->envelop_data->CreationDateTime);
    free(b->envelop_data->Destination);
    free(b->envelop_data->MessageID);
    free(b->envelop_data->MessageType);
    free(b->envelop_data->Sender);
    free(b->envelop_data->Signature);
    free(b->envelop_data->ReferenceID);
    free(b->envelop_data->User_properties);
    free(b->envelop_data);
    free(b->payload);
}

char *get_dir_name(const char *s)
{
    char t = '/';
    const char *last = strrchr(s, t);
    if (last != NULL)
    {
        const size_t len = (size_t)(last - s);
        char *const n = malloc(len + 1);
        memcpy(n, s, len);
        n[len] = '\0';
        return strdup(n);
    }
    return NULL;
}
void clean_dir(char *path)
{ /* Deletes the BMD file specified by the path */
    
    remove(path);
    printf("removed :%s", path);
    path = get_dir_name(path);
    /* Removes the directory created by random numberes*/
    rmdir(path);
    printf("removed :%s", path);
    free(path);
}
void free_req(task_t *t)
{
    clean_dir(t->data_location);
    free(t->data_location);
    free(t->message_type);
    free(t->sender);
    free(t);
}

void free_config(config_t *config)
{
    free(config->key);
    free(config->value);
    free(config);
}
