/**
 * @file test_adapter.c
 * @author Nikhil
 * @brief 
 * @version 0.1
 * @date 2020-09-17
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <stdio.h>
#include "../test/munit.h"
#include "adapter.h"
#include "../bmd_handler/bmd.h"
#include "../db_access/connector.h"
#include <stdlib.h>


#define STRING_SIZE 100

char *get_str_data(char *file) {
  long f_size;
  char *str_data;
  size_t file_size,result;

  FILE *f;
  f=fopen(file,"r");
  //read the size of the file

  fseek(f,0,SEEK_END);
  f_size=ftell(f);

  fseek(f,0,SEEK_SET);

  file_size=sizeof(char)*f_size+1;
  str_data=malloc(file_size);

/* fread returns number of items actually read. */
  result =fread(str_data,1,f_size,f);
  return strdup(str_data);
}

/* Test setup function */
static void *
payload_to_json_setup(const MunitParameter params[], void *user_data)
{
  char *file = "../bmd_files/bmd1.xml";
  bmd *bmd_file= parse_bmd_xml(file);
  /* Generate HTTP url required to call
           destination service */
   int route_id = get_active_route_id(bmd_file->envelop_data->Sender,
                                           bmd_file->envelop_data->Destination,
                                           bmd_file->envelop_data->MessageType);
  transport_t *transport = fetch_transport_config(route_id);

  char url[STRING_SIZE];
  
  sprintf(url, "%s%s", transport->value, bmd_file->payload);
  //to_be_sent = (char *)call_function(transport->key, (void *)url,
  //  (void *)transport->key);
  /** Payload to json contacts destination service
          * Stores the received data in a file and returns
          * the file path.*/
  
  char *file_created = payload_to_json(bmd_file, url);
  /* Copy file data into string */

  char *json_data = get_str_data(file_created);
  return strdup(file_created);
}

/* Test function */
static MunitResult
test_payload_to_json(const MunitParameter params[], void *fixture)
{
  char *file_created = (char *)fixture;
  char *json_data = get_str_data(file_created);
  char *test_data = get_str_data("Payload_4ac268c2");
  munit_assert_string_equal(json_data, test_data);
  return MUNIT_OK;
}

static void
payload_to_json_tear_down(void *fixture) {
  char *file_created = (char *)fixture;
  int del = remove(file_created);
  /* Checks if file is deleted */
  munit_assert(!del);
  free(file_created);
}

static void*
payload_to_xml_setup(const MunitParameter params[], void *user_data) {
    char * file="../bmd_files/bmd1.xml";
    bmd* b=parse_bmd_xml(file);
      
    return b;
}

static MunitResult
test_payload_to_xml(const MunitParameter params[], void *fixture) {
    bmd *b=(bmd*)fixture;
    char *file_created= payload_to_xml(b);
    char *xml_data=get_str_data(file_created);
    char *test_data=get_str_data("payload_4ac26");
    munit_assert_string_equal(xml_data,test_data);
    return MUNIT_OK;
}

static void
payload_to_xml_tear_down(void *fixture) {
  bmd *b = (bmd *)fixture;
  free(b);
}


static MunitResult
test_send_mail(const MunitParameter params[], void *fixture) {
    int rc=send_mail("testmailtm02@gmail.com","Returnfile.json");
    munit_assert(rc == 0);
    return MUNIT_OK;
}

static MunitResult
test_http_post(const MunitParameter params[], void *fixture) {
    char* rc=http_post("https://reqres.in/api/users", "name=Test&job=Testing");
    munit_assert_string_equal(rc,"Returnfile.json");
    return MUNIT_OK;
}

static MunitResult
test_call_destination_service(const MunitParameter params[], void *fixture) {
    char* rc=call_destination_service("https://ifsc.razorpay.com/","API_URL");
    munit_assert(rc!=0);
    return MUNIT_OK;
}



MunitTest adapter_tests[]={ 
    {
        "/test_send_mail",       /* name */
        test_send_mail,          /* test function */
        NULL,                    /* setup function for the test */
        NULL,                    /* tear_down */
        MUNIT_TEST_OPTION_NONE,  /* options */
        NULL                     /* parameters */
    },
    {
        "/test_http_post",       /* name */
        test_http_post,          /* test function */
        NULL,                    /* setup function for the test */
        NULL,                    /* tear_down */
        MUNIT_TEST_OPTION_NONE,  /* options */
        NULL                     /* parameters */
    },
    {
        "/payload_to_xml_test",   /* name */
        test_payload_to_xml,      /* test function */
        payload_to_xml_setup,     /* setup function for the test */
        payload_to_xml_tear_down, /* tear_down */
        MUNIT_TEST_OPTION_NONE,    /* options */
        NULL                       /* parameters */
    },
        {
        "/payload_to_json_test",   /* name */
        test_payload_to_json,      /* test function */
        payload_to_json_setup,     /* setup function for the test */
        payload_to_json_tear_down, /* tear_down */
        MUNIT_TEST_OPTION_NONE,    /* options */
        NULL                       /* parameters */
    },
    {
        "/test_call_destination_service",   /* name */
        test_call_destination_service,      /* test function */
        NULL,                               /* setup function for the test */
        NULL,                               /* tear_down */
        MUNIT_TEST_OPTION_NONE,             /* options */
        NULL                                /* parameters */
    },
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}    
};

static const MunitSuite suite = {
    "/adapter_tests",           /* name */
    adapter_tests,              /* tests */
    NULL,                       /* suites */
    1,                          /* iterations */
    MUNIT_SUITE_OPTION_NONE     /* options */
};

/* Run the the test suite */
/*int main(int argc, const char *argv[])
{
  return munit_suite_main(&suite, NULL, argc, NULL);
}*/
