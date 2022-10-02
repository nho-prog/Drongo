#include <stdio.h>

#include "../test/munit.h"
#include "esb.h"
/** Include Module that has bmd handling 
 * functions and  bmd structure declaration 
 * 
 */ 
#include "../bmd_handler/bmd.h"

/** Module that has mysql C API functions */

#include "../db_access/connector.h"



static MunitResult
test_queue_the_request(const MunitParameter params[], void *fixture)
{
    bmd *b = parse_bmd_xml("../bmd_files/bmd2.xml");

    munit_assert(queue_the_request(b,"../bmd_files/bmd2.xml")==1);
    return MUNIT_OK;
}


static MunitResult
test_process_esb_request(const MunitParameter params[], void *fixture)
{
    bmd *b = (bmd *)fixture;

    munit_assert(process_esb_request("../bmd_files/bmd2.xml")==1);
    return MUNIT_OK;
}

/* Put all unit tests here. */
MunitTest esb_tests[] = {
     {
        "/process_esb_request",   /* name */
        test_process_esb_request,  /* test function */
        NULL,    /* setup function for the test */
        NULL,    /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL                    /* parameters */
    },
    
    {
        "/queue_the_request",   /* name */
        test_queue_the_request,  /* test function */
        NULL,    /* setup function for the test */
        NULL,    /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL                    /* parameters */
    },
    /* Mark the end of the array with an entry where the test
   * function is NULL */
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

/* Arrange the test cases into a test suite. */
static const MunitSuite suite = {
  "/esb_tests", /* name */
  esb_tests, /* tests */
  NULL, /* suites */
  1, /* iterations */
  MUNIT_SUITE_OPTION_NONE /* options */
};

/* Run the the test suite */
/*int main (int argc, const char* argv[]) {
  return munit_suite_main(&suite, NULL, argc, NULL);
}*/