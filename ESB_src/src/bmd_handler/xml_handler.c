/**
 * @file xml_handler.c
 * @author MubeenS
 * @brief 
 * @version 1.0
 * @date 2020-09-02
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <stdio.h>

/* xml handling library */
#include <libxml/parser.h>

#include<stdlib.h>
#include<string.h>
/* BMD structure */
#include "bmd.h"

#ifndef XML_HANDLER
#define XML_HANDLER
/**
 * @brief Checks if a Node is a leaf
 * 
 * @param node will be checked
 * @return int 1 if it is leaf
 */
int is_leaf(xmlNode *node) {
  xmlNode *child = node->children;
  while(child) {
    if(child->type == XML_ELEMENT_NODE){
      return 0;
    } child = child->next;
  } return 1;
}

/**
 * @brief Extracts envelop elements
 * 
 */
void extract_envelop_details(xmlNode * node,envelop *envl)
{
    int size;
    while(node){
        if(node->type == XML_ELEMENT_NODE && is_leaf(node))
        {    size = strlen((char*) xmlNodeGetContent(node));

                /* MessageID*/
                if(!(strcmp(((char *) node->name),"MessageID"))) {
                    envl->MessageID = malloc((size+1)* sizeof(char));
                    strcpy(envl->MessageID,(char *) xmlNodeGetContent(node));
                    if(strcmp(envl->MessageID, "") ==0){
                       envl->MessageType=NULL;  
                    } 
                }

                /*MessageType */
                else if(!(strcmp((char *) node->name,"MessageType"))) {
	                  envl->MessageType =  (char *)malloc((size+1)* sizeof(char));
                    strcpy(envl->MessageType ,(char *)xmlNodeGetContent(node));
                    if(!(strcmp(envl->MessageType, ""))){
                       envl->MessageType=NULL;  
                    }    
	               }

                /*Sender */
                else if(!(strcmp(((char *) node->name), "Sender"))) {
		               envl->Sender =  (char *)malloc((size+1)* sizeof(char));
                   strcpy(envl->Sender ,(char *)xmlNodeGetContent(node));
                   if(!(strcmp(envl->Sender, ""))){
                       envl->Sender=NULL;  
                    } 
		             }
                 
                /*Destination*/
                else if(!(strcmp(((char *) node->name),"Destination"))) {
		               envl->Destination =  (char *)malloc((size+1)* sizeof(char));
                   strcpy(envl->Destination ,(char *)xmlNodeGetContent(node));
                   if(strcmp(envl->Destination, "") ==0){
                       envl->Destination=NULL;  
                    } 
	               }

                /*CreationDateTime*/
                else if(!(strcmp(((char *) node->name),"CreationDateTime"))) {
		               envl->CreationDateTime =  (char *)malloc((size+1)* sizeof(char));
                   strcpy(envl->CreationDateTime ,(char *)xmlNodeGetContent(node));
                   if(!(strcmp(envl->CreationDateTime, ""))){
                       envl->CreationDateTime=NULL;  
                    } 
	               }

                 /*Signature*/
	      	      else  if(!(strcmp(((char *) node->name),"Signature"))) {
         	         envl->Signature =  (char *)malloc((size+1)* sizeof(char));
                   strcpy(envl->Signature ,(char *)xmlNodeGetContent(node));
                   if(!strcmp(envl->Signature, "")){
                       envl->Signature=NULL;  
                    } 
                }
               else if(!(strcmp(((char *) node->name),"ReferenceID"))) {
		                envl->ReferenceID =  (char *)malloc((size+1)* sizeof(char));
                    strcpy(envl->ReferenceID ,(char *)xmlNodeGetContent(node));
                    if(!(strcmp(envl->ReferenceID, ""))) {
                       envl->ReferenceID=NULL;  
                    } 
                }

         }
        extract_envelop_details(node->children,envl);
        node = node->next;
     }
}

/* Extract envelop data */

envelop*  extract_envelop(char * filepath) {
  xmlDoc *doc = NULL;
  xmlNode *root_element = NULL;

  /*Open file in read mode */
  doc = xmlReadFile(filepath, NULL, 0);

  if (doc == NULL) {
    printf("Could not parse the XML file");
  }
  /*Get the root element node */
  root_element = xmlDocGetRootElement(doc);
  envelop *envl;
  /* Allocate memory for envl */
  envl = (envelop *) malloc(sizeof(envelop));
  extract_envelop_details(root_element,envl);

  /*free the document handle */
  xmlFreeDoc(doc);

   /*Cleans the variables created by Parser*/
  xmlCleanupParser();
  
  return envl;
}

/* extract payload data */
char * extract_payload(char * filepath) {
  int size;
  xmlDoc *doc = NULL;
  xmlNode *root = NULL;
  char * payload;
  /*Open file in read mode */
  doc = xmlReadFile(filepath, NULL, 0);

  if (doc == NULL) {
    printf("Could not parse the XML file");
  }
  /*Get the root element node */
  root = xmlDocGetRootElement(doc);

  /* Payload is present in child element of xml*/
  xmlNode *cur = root->children;
  while(cur) {
        if(cur->type == XML_ELEMENT_NODE && is_leaf(cur)) {    
          size = strlen((char*) xmlNodeGetContent(cur));
           /*PayLoad*/
           if (!(strcmp(((char *) cur->name),"Payload"))) {
                     payload = (char *)malloc((size+1)* sizeof(char));
                     strcpy(payload , (char *) xmlNodeGetContent(cur));
                     if(!(strcmp(payload, ""))){
                       payload=NULL;  
                     }
                 return payload;
                }
         }
         cur = cur->next;
     }
  }

bmd* parse_bmd_xml(char *bmd_xml_file) {
  bmd *bmd_file;
  bmd_file = (bmd *) malloc(sizeof(bmd));
  bmd_file->envelop_data = extract_envelop(bmd_xml_file);
  bmd_file->payload = extract_payload(bmd_xml_file);
  return bmd_file;
}

/**
 * @brief Extracts payload data from
 * bmd file and stores it in an .json file
 * 
 * @param bmd_file extacted bmd.
 * @return name of json file containing payload data.
 */

#endif
/*int main() { 
  bmd *bmd_file = parse_bmd_xml("../bmd_files/bmd1.xml");
  int check = is_bmd_valid(bmd_file);
  char *s = payload_to_json(bmd_file);
}*/
