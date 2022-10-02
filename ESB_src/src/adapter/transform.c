
#include <stdio.h>

/* xml handling library */
#include <libxml/parser.h>

#include <stdlib.h>
#include <string.h>

/* BMD structure */
#include "bmd_handler/bmd.h"

#include "adapter.h"

#define STRING_SIZE 100
/**
 * @brief Creates a json file containing
 * payload data and returns the path of the file.
 * All such created files are stored in assets directory.
 * 
 * @param bmd_file bmd_file to get payload
 * @return char* Path of the file.
 */
char *payload_to_json(bmd *bmd_file, char *url)
{
    printf(">> Payload to json..\n");

    char file[STRING_SIZE]="Payload_";
    /*Creates file name of json as per bmd name*/
    /* Copying first 8 characters to keep the name unique */
    strncat(file,bmd_file->envelop_data->MessageID,8);
    //sprintf(file,"../assets/payload_%s.json",bmd_file->envelop_data->MessageID);
    

    /* Get data from destination service 
        that should be sent */
    char *payload_data = call_destination_service(url,
                                                  "IFSC.RAZORPAY");

    FILE *fp;
    fp = fopen(file, "w");
    if (fp == NULL)
    {
        printf("file opening failed");
        return NULL;
    }
    /* Writes into json file */
    fprintf(fp, "\n%s\n", payload_data);
    /* Closes file */
    fclose(fp);
    /* returns json filename */
    return strdup(file);
}

/**
 * @brief Creates an xml file that contains
 * payload data and returns the file path.
 * 
 * @param bmd_file to get payload
 * @return char* file path
 */
char *payload_to_xml(bmd *bmd_file)
{
    /*Creates file name of xml as per bmd name*/
    char file[STRING_SIZE]="payload_";
    /* Appends name of messageID */
    strncat(file,bmd_file->envelop_data->MessageID,5);

    char *payload_data = bmd_file->payload;
    FILE *fp;
    fp = fopen(file, "w");
    if (fp == NULL)
    {
        printf("file opening failed");
        return "FAIL";
    }
    /* Writes into xml file */
    char *version = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
    char *style = "<?xml-stylesheet type='text/xsl'?>";
    fprintf(fp, "%s\n%s\n<payload>%s</payload>", version, style, payload_data);
    /* Closes file */
    fclose(fp);
    /* returns xml filename */
    return strdup(file);
}

/*int main () {
    bmd *file = parse_bmd_xml("../bmd_files/bmd1.xml");
    char *xml_path = payload_to_xml(file);
    char *json_path = payload_to_json(file);
    send_mail("testmailtm02@gmail.com",json_path);
    printf("%s %s",json_path,xml_path);
}*/