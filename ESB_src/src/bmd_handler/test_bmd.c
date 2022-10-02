/**
 * @file test_bmd.c
 * @author Nikhil
 * @brief µnit testing of Bmd validation and Parsing 
 * of the bmd.xml file.
 * @version 0.1
 * @date 2020-09-17
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <stdio.h>
#include "../test/munit.h"
#include "bmd.h"

#include "../adapter/adapter.h"

#include "../db_access/connector.h"


#define STRING_SIZE 100

/* Test setup function creates bmd and returns it */
static void *
is_bmd_valid_setup(const MunitParameter params[], void *user_data)
{
  char *file = "../bmd_files/bmd2.xml";
  bmd *b = parse_bmd_xml(file);
  return b;
}

/* Test function */
static MunitResult
test_is_bmd_valid(const MunitParameter params[], void *fixture)
{
  bmd *test_bmd = (bmd *)fixture;
  /* is_bmd_valid returns 1 if valid */
  munit_assert(is_bmd_valid(test_bmd) == 1);
  return MUNIT_OK;
}

static void
is_bmd_valid_tear_down(void *fixture)
{
  free(fixture);
}

/* Test setup function creates bmd and returns it */
static void *
parse_bmd_xml_setup(const MunitParameter params[], void *user_data)
{
  char *file = "../bmd_files/bmd2.xml";
  bmd *b = parse_bmd_xml(file);
  return b;
}

bmd *get_bmd(void)
{
  bmd *bmd_file = (bmd *)malloc(sizeof(bmd));
  envelop *envl = (envelop *)malloc(sizeof(envelop));
  envl->Sender = "4ac26e80-f658-11ea-adc1-0242ac120002";
  envl->Destination = "4ac271fa-f658-11ea-adc1-0242ac120002";
  envl->CreationDateTime = "2020-08-12T05:18:00+00001";
  envl->MessageID = "4ac26db8-f658-11ea-adc1-0242ac120002";
  envl->MessageType = "CreditReport";
  envl->ReferenceID = "4ac272d6-f658-11ea-adc1-0242ac120002";
  envl->Signature = "S2";
  bmd_file->envelop_data = envl;
  bmd_file->payload = "SBIN0000847";

  return bmd_file;
}
/* Test function */
static MunitResult
test_parse_bmd_xml(const MunitParameter params[], void *fixture)
{
  bmd *test_bmd = (bmd *)fixture;
  bmd *expected_bmd = get_bmd();
  /* is_bmd_valid returns 1 if valid */
  munit_assert_string_equal(test_bmd->envelop_data->Sender,
                            expected_bmd->envelop_data->Sender);
  munit_assert_string_equal(test_bmd->envelop_data->Destination,
                            expected_bmd->envelop_data->Destination);
  munit_assert_string_equal(test_bmd->envelop_data->MessageType,
                            expected_bmd->envelop_data->MessageType);
  munit_assert_string_equal(test_bmd->envelop_data->CreationDateTime,
                            expected_bmd->envelop_data->CreationDateTime);
  munit_assert_string_equal(test_bmd->envelop_data->MessageID,
                            expected_bmd->envelop_data->MessageID);
  munit_assert_string_equal(test_bmd->envelop_data->Signature,
                            expected_bmd->envelop_data->Signature);
  munit_assert_string_equal(test_bmd->envelop_data->ReferenceID,
                            expected_bmd->envelop_data->ReferenceID);
  munit_assert_string_equal(test_bmd->payload, expected_bmd->payload);

  return MUNIT_OK;
}

static void
parse_bmd_xml_tear_down(void *fixture)
{
  bmd *b = (bmd *)fixture;

  free(b->envelop_data);
  free(b->payload);
  free(b);
}

/**
 * @brief Parameterised testing for bmd.xml files
 * 
 * @param params 
 * @param user_data 
 * @return MunitResult 
 */

static MunitResult
test_bmd_xml(const MunitParameter params[], void* user_data) {
  const char* correct;

  correct = munit_parameters_get(params, "correct");
    
    //printf("%s\n",(char *) correct);

  /*if (strcmp(correct, "../bmd_files/bmd1.xml") == 0 ||
      strcmp(correct, "../bmd_files/bmd2.xml") == 0 ||
      strcmp(correct, "../bmd_files/bmd3.xml") == 0)
      return MUNIT_OK;*/

  bmd *test_bmd= parse_bmd_xml((char*)correct);

  printf("testing for each bmd file\n");

  if(strcmp(correct,"../bmd_files/bmd1.xml")==0)
  {
    munit_assert_string_equal(test_bmd->envelop_data->MessageID,"4ac268c2-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->MessageType,"CreditReport");
    munit_assert_string_equal(test_bmd->envelop_data->Sender,"4ac26b10-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->Destination,"4ac26c14-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->CreationDateTime,"2020-08-12T05:18:00+00001");
    munit_assert_string_equal(test_bmd->envelop_data->ReferenceID,"4ac26ce6-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->Signature,"S1");
    munit_assert_string_equal(test_bmd->payload,"SBIN0000882");
  }  

    if(strcmp(correct,"../bmd_files/bmd2.xml")==0)
  {
    munit_assert_string_equal(test_bmd->envelop_data->MessageID,"4ac26db8-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->MessageType,"CreditReport");
    munit_assert_string_equal(test_bmd->envelop_data->Sender,"4ac26e80-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->Destination,"4ac271fa-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->CreationDateTime,"2020-08-12T05:18:00+00001");
    munit_assert_string_equal(test_bmd->envelop_data->ReferenceID,"4ac272d6-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->Signature,"S2");
    munit_assert_string_equal(test_bmd->payload,"SBIN0000847");
  }    



    if(strcmp(correct,"../bmd_files/bmd3.xml")==0)
  {
    munit_assert_string_equal(test_bmd->envelop_data->MessageID,"4ac2739e-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->MessageType,"CreditReport");
    munit_assert_string_equal(test_bmd->envelop_data->Sender,"4ac27466-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->Destination,"4ac2752e-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->CreationDateTime,"2020-08-12T05:18:00+00001");
    munit_assert_string_equal(test_bmd->envelop_data->ReferenceID,"4ac275f6-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->Signature,"S3");
    munit_assert_string_equal(test_bmd->payload,"BKID0008605");
  }    

   if(strcmp(correct,"../bmd_files/bmd4.xml")==0)
  {
    munit_assert_string_equal(test_bmd->envelop_data->MessageID,"4ac278b2-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->MessageType,"CreditReport");
    munit_assert_string_equal(test_bmd->envelop_data->Sender,"4ac27984-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->Destination,"4ac27a42-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->CreationDateTime,"2020-08-12T05:18:00+00001");
    munit_assert_string_equal(test_bmd->envelop_data->ReferenceID,"4ac27af6-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->Signature,"S4");
    munit_assert_string_equal(test_bmd->payload,"IBKL0000001");
  }    
  

  if(strcmp(correct,"../bmd_files/bmd5.xml")==0)
  {
    munit_assert_string_equal(test_bmd->envelop_data->MessageID,"4ac27bb4-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->MessageType,"CreditReport");
    munit_assert_string_equal(test_bmd->envelop_data->Sender,"4ac27c68-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->Destination,"4ac27d26-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->CreationDateTime,"2020-08-12T05:18:00+00001");
    munit_assert_string_equal(test_bmd->envelop_data->ReferenceID,"4ac27de4-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->Signature,"S5");
    munit_assert_string_equal(test_bmd->payload,"ICIC0002652");
  }    
   

  if(strcmp(correct,"../bmd_files/bmd6.xml")==0)
  {
    munit_assert_string_equal(test_bmd->envelop_data->MessageID,"4ac27fe2-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->MessageType,"CreditReport");
    munit_assert_string_equal(test_bmd->envelop_data->Sender,"4ac280aa-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->Destination,"4ac28172-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->CreationDateTime,"2020-08-12T05:18:00+00001");
    munit_assert_string_equal(test_bmd->envelop_data->ReferenceID,"4ac2823a-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->Signature,"S6");
    munit_assert_string_equal(test_bmd->payload,"ICIC0006271");
  }    
     

  if(strcmp(correct,"../bmd_files/bmd7.xml")==0)
  {
    munit_assert_string_equal(test_bmd->envelop_data->MessageID,"4ac282f8-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->MessageType,"CreditReport");
    munit_assert_string_equal(test_bmd->envelop_data->Sender,"4ac283b6-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->Destination,"4ac2860e-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->CreationDateTime,"2020-08-12T05:18:00+00001");
    munit_assert_string_equal(test_bmd->envelop_data->ReferenceID,"4ac286cc-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->Signature,"S7");
    munit_assert_string_equal(test_bmd->payload,"ICIC0003239");
  }  

  if(strcmp(correct,"../bmd_files/bmd8.xml")==0)
  {
    munit_assert_string_equal(test_bmd->envelop_data->MessageID,"4ac2878a-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->MessageType,"CreditReport");
    munit_assert_string_equal(test_bmd->envelop_data->Sender,"4ac28848-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->Destination,"4ac28910-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->CreationDateTime,"2020-08-12T05:18:00+00001");
    munit_assert_string_equal(test_bmd->envelop_data->ReferenceID,"4ac289ce-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->Signature,"S7");
    munit_assert_string_equal(test_bmd->payload,"UTIB0000051");
  }  
 

  if(strcmp(correct,"../bmd_files/bmd9.xml")==0)
  {
    munit_assert_string_equal(test_bmd->envelop_data->MessageID,"4ac28c58-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->MessageType,"CreditReport");
    munit_assert_string_equal(test_bmd->envelop_data->Sender,"4ac28d16-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->Destination,"4ac28dde-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->CreationDateTime,"2020-08-12T05:18:00+00001");
    munit_assert_string_equal(test_bmd->envelop_data->ReferenceID,"4ac28e9c-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->Signature,"S7");
    munit_assert_string_equal(test_bmd->payload,"UTIB0001648");
  }  

  if(strcmp(correct,"../bmd_files/bmd9.xml")==0)
  {
    munit_assert_string_equal(test_bmd->envelop_data->MessageID,"4ac28c58-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->MessageType,"CreditReport");
    munit_assert_string_equal(test_bmd->envelop_data->Sender,"4ac28d16-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->Destination,"4ac28dde-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->CreationDateTime,"2020-08-12T05:18:00+00001");
    munit_assert_string_equal(test_bmd->envelop_data->ReferenceID,"4ac28e9c-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->Signature,"S7");
    munit_assert_string_equal(test_bmd->payload,"UTIB0001648");
  }

  if(strcmp(correct,"../bmd_files/bmd10.xml")==0)
  {
    munit_assert_string_equal(test_bmd->envelop_data->MessageID,"4ac28f5a-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->MessageType,"CURR_EXCHG");
    munit_assert_string_equal(test_bmd->envelop_data->Sender,"4ac29018-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->Destination,"4ac290d6-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->CreationDateTime,"2020-08-12T05:18:00+00001");
    munit_assert_string_equal(test_bmd->envelop_data->ReferenceID,"4ac292fc-f658-11ea-adc1-0242ac120002");
    munit_assert_string_equal(test_bmd->envelop_data->Signature,"S7");
    munit_assert_string_equal(test_bmd->payload,"USD");
  }

  
  return MUNIT_OK;
}



static char* correct_params[] = {
 (char*) "../bmd_files/bmd1.xml" ,
 (char*) "../bmd_files/bmd2.xml" ,
 (char*) "../bmd_files/bmd3.xml" ,
 (char*) "../bmd_files/bmd4.xml" ,
 (char*) "../bmd_files/bmd5.xml" ,
 (char*) "../bmd_files/bmd6.xml" ,
 (char*) "../bmd_files/bmd7.xml" ,
 (char*) "../bmd_files/bmd8.xml" ,
 (char*) "../bmd_files/bmd9.xml" ,
 (char*) "../bmd_files/bmd10.xml",
  NULL
};


static MunitParameterEnum test_params[] = {
  { (char*) "correct", correct_params }
};


/* Put all unit tests here. */
MunitTest bmd_tests[] = {
    {
        "/parse_bmd_xml_test",   /* name */
        test_parse_bmd_xml,      /* test function */
        parse_bmd_xml_setup,     /* setup function for the test */
        parse_bmd_xml_tear_down, /* tear_down */
        MUNIT_TEST_OPTION_NONE,  /* options */
        NULL                     /* parameters */
    },

    {
        "/is_bmd_valid_test",   /* name */
        test_is_bmd_valid,      /* test function */
        is_bmd_valid_setup,     /* setup function for the test */
        is_bmd_valid_tear_down, /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL                    /* parameters */
    },
    {
        "/test_bmd_files" ,
        test_bmd_xml, 
        NULL,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        test_params 
    },
    /* Mark the end of the array with an entry where the test
   * function is NULL */
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

/* Arrange the test cases into a test suite. */
static const MunitSuite suite = {
    "/bmd_tests",           /* name */
    bmd_tests,              /* tests */
    NULL,                   /* suites */
    1,                      /* iterations */
    MUNIT_SUITE_OPTION_NONE /* options */
};

/* Run the the test suite */
 int main(int argc, const char *argv[])
 {
  return munit_suite_main(&suite, NULL, argc, NULL);
 }

