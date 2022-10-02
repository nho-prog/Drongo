/**
 * @brief Contains:
 * 1.Envelop structure
 * 2.Complete BMD structure
 * 3.Declarations of XML(BMD) handling functions
 * 
 */

#include <stdio.h>
#ifndef BMD_H
#define BMD_H
typedef struct bmdMessage_ {
   char *MessageID;
   char *MessageType;
   char *Sender;
   char *Destination;
   char *CreationDateTime;
   char *Signature;
   char *ReferenceID;
   char *User_properties;
}envelop;

typedef struct bmd_ {
  envelop *envelop_data;
  char * payload;
}bmd;

envelop*  extract_envelop(char * filepath);
bmd* parse_bmd_xml(char *bmd_xml_file);
char * extract_payload(char * filepath);
int is_bmd_valid(bmd *bmd_file);
long int find_size(char *);
#endif