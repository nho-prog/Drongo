/**
 * @file insert_to_esb_request.c
 * @author MubeenS 
 * @brief  The program is a C API for the SQL query 
 * "INSERT INTO                            
 * esb_request(sender_id,dest_id,message_type,reference_id,      
 * message_id,data_location,status,status_details)               
 * VALUES(?,?,?,?,?,?,?,?)"
 * @version 0.1
 * @date 2020-09-1
 * 
 * @copyright Copyright (c) 2020
 * 
 */

/*Required C standard libraries*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
/* Contains necessary C functions of mysql */
#include <mysql/mysql.h>

#ifndef INSERT_REQUEST
#define INSERT_REQUEST
/* C standard macro and library for handling datetime*/
#define __USE_XOPEN /* Compiler Warns without this macro*/
#include <time.h>
#include "connector.h"
/**
 * Holds the info to connect to DB and
 * error specifying function for 
 * databse connection handle 
 */

#define STRING_SIZE 1000
/*
#define INSERT "INSERT INTO                                  \
esb_request(sender_id,dest_id,message_type,reference_id,     \
message_id,data_location,status,status_details)              \
VALUES(?,?,?,?,?,?,?,?)"
*/
#define INSERT "INSERT INTO                                  \
esb_request(sender_id,dest_id,message_type,reference_id,     \
message_id,data_location,status,status_details,received_on)  \
VALUES(?,?,?,?,?,?,?,?,?)"

int insert_to_esb_request(char *sender_id, char *dest_id,
                          char *message_type, char *reference_id, char *message_id,
                          char *data_location, char *status, char *status_details, char *received_on)
{

  MYSQL_STMT *stmt;
  MYSQL_BIND bind[9];
  my_ulonglong affected_rows;
  int param_count;
  int id;
  char sender_id_data[STRING_SIZE];
  char dest_id_data[STRING_SIZE];
  char message_type_data[STRING_SIZE];
  char reference_id_data[STRING_SIZE];
  char message_id_data[STRING_SIZE];
  char data_location_data[STRING_SIZE];
  char status_data[STRING_SIZE];
  char status_details_data[STRING_SIZE];
  MYSQL_TIME received_on_data;
  unsigned long str_length[8];
  bool is_null;

  MYSQL *con; /*database connection handle*/
  /**
   * @brief Allocates and initialises a MYSQL object 
   * suitable for mysql_real_connect() function
   * 
   */
  con = mysql_init(NULL);

  /**
   * @brief Prints error message incase
   * initialisation of con fails.
   */
  if (con == NULL)
  {
    fprintf(stderr, "mysql_init() failed\n");
    return -1;
  }

  /**
   * @brief Checks if connection is 
   * properly established.
   * 
   */
  if (mysql_real_connect(con, HOST, USER, PASS,
                         DB_NAME, PORT, UNIX_SOCKET, FLAG) == NULL)
  {
    finish_with_error(con);
  }
  /* Prepare an INSERT query with 9 parameters */
  stmt = mysql_stmt_init(con);
  if (!stmt)
  {
    fprintf(stderr, " mysql_stmt_init(), out of memory\n");
    return -1;
  }

  if (mysql_stmt_prepare(stmt, INSERT, strlen(INSERT)))
  {
    fprintf(stderr, " mysql_stmt_prepare(), INSERT failed\n");
    fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
    return -1;
  }

  /* Get the parameter count from the statement */
  param_count = mysql_stmt_param_count(stmt);
  /*fprintf(stdout, " total parameters in INSERT: %d\n", param_count);*/

  /* validate parameter count */
  if (param_count != 9)
  {
    fprintf(stderr, " invalid parameter count returned by MySQL\n");
    return -1;
  }

  /* Bind the data for all 8 parameters */
  memset(bind, 0, sizeof(bind));

  /* Sender id */
  bind[0].buffer_type = MYSQL_TYPE_STRING;
  bind[0].buffer = (char *)&sender_id_data;
  bind[0].is_null = 0;
  bind[0].length = &str_length[0];
  bind[0].buffer_length = STRING_SIZE;

  /* dest_id */
  bind[1].buffer_type = MYSQL_TYPE_STRING;
  bind[1].buffer = (char *)dest_id_data;
  bind[1].buffer_length = STRING_SIZE;
  bind[1].is_null = 0;
  bind[1].length = &str_length[1];

  /* message_type */
  bind[2].buffer_type = MYSQL_TYPE_STRING;
  bind[2].buffer = (char *)&message_type_data;
  bind[2].is_null = 0;
  bind[2].buffer_length = STRING_SIZE;
  bind[2].length = &str_length[2];

  /* reference_id */
  bind[3].buffer_type = MYSQL_TYPE_STRING;
  bind[3].buffer = (char *)&reference_id_data;
  bind[3].is_null = 0;
  bind[3].buffer_length = STRING_SIZE;
  bind[3].length = &str_length[3];

  /* message_id  */
  bind[4].buffer_type = MYSQL_TYPE_STRING;
  bind[4].buffer = (char *)&message_id_data;
  bind[4].is_null = 0;
  bind[4].buffer_length = STRING_SIZE;
  bind[4].length = &str_length[4];

  /* data_location */
  bind[5].buffer_type = MYSQL_TYPE_STRING;
  bind[5].buffer = (char *)&data_location_data;
  bind[5].is_null = 0;
  bind[5].buffer_length = STRING_SIZE;
  bind[5].length = &str_length[5];

  /* status */
  bind[6].buffer_type = MYSQL_TYPE_STRING;
  bind[6].buffer = (char *)&status_data;
  bind[6].is_null = 0;
  bind[6].buffer_length = STRING_SIZE;
  bind[6].length = &str_length[6];

  /* status details */
  bind[7].buffer_type = MYSQL_TYPE_STRING;
  bind[7].buffer = (char *)&status_details_data;
  bind[7].is_null = 0;
  bind[7].buffer_length = STRING_SIZE;
  bind[7].length = &str_length[7];

  /* Received on */
  bind[8].buffer_type = MYSQL_TYPE_DATETIME;
  bind[8].buffer = (char *)&received_on_data;
  bind[8].is_null = 0;
  bind[8].length = 0;

  /* Bind the buffers */
  if (mysql_stmt_bind_param(stmt, bind))
  {
    fprintf(stderr, " mysql_stmt_bind_param() failed\n");
    fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
    return -1;
  }
  strncpy(sender_id_data, sender_id, STRING_SIZE);
  str_length[0] = strlen(sender_id_data);
  strncpy(dest_id_data, dest_id, STRING_SIZE);
  str_length[1] = strlen(dest_id_data);
  strncpy(message_type_data, message_type, STRING_SIZE);
  str_length[2] = strlen(message_type_data);
  strncpy(reference_id_data, reference_id, STRING_SIZE);
  str_length[3] = strlen(reference_id_data);
  strncpy(message_id_data, message_id, STRING_SIZE);
  str_length[4] = strlen(message_id_data);
  strncpy(data_location_data, data_location, STRING_SIZE);
  str_length[5] = strlen(data_location_data);
  strncpy(status_data, status, STRING_SIZE);
  str_length[6] = strlen(status_data);
  strncpy(status_details_data, status_details, STRING_SIZE);
  str_length[7] = strlen(status_details_data);

  /* C structure to store DATETIME format */
  struct tm result;
  /* Convert string to DATETIME format. Store the result*/
  strptime(received_on, "%Y-%m-%dT%H:%M:%S+%Z", &result);
  /* Epoch is 1900 in C standard */
  received_on_data.year = result.tm_year + 1900;
  /* Month count is from 0(JAN) */

  received_on_data.month = result.tm_mon + 1;
  received_on_data.day = result.tm_mday;
  received_on_data.hour = result.tm_hour;
  received_on_data.minute = result.tm_min;
  received_on_data.second = result.tm_sec;
  /* Execute the INSERT statement*/
  if (mysql_stmt_execute(stmt))
  {
    fprintf(stderr, " mysql_stmt_execute, failed\n");
    fprintf(stderr, " [%d]%s\n", mysql_stmt_errno(stmt),
            mysql_stmt_error(stmt));
    return -1;
  }

  /* Get the total rows affected */
  affected_rows = mysql_stmt_affected_rows(stmt);
  fprintf(stdout, "Total affected rows(insert 2): %lu\n",
          (unsigned long)affected_rows);

  /* validate affected rows */
  if (affected_rows != 1)
  {
    fprintf(stderr, " invalid affected rows by MySQL\n");
    return -1;
  }

  /* Close the statement */
  if (mysql_stmt_close(stmt))
  {
    fprintf(stderr, " failed while closing the statement\n");
    fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
    return -1;
  }
  printf("connection id: %ld\n", mysql_thread_id(con));

  /*No error occurred and insert is successful*/
  return 1;
  mysql_close(con);
}
#endif
/*testing with a sample input*/
/*int main() {
  char *s,*d,*mt,*rid,*mid,*dl,*st,*std;
  s="sender2"; d = "dest3"; mt = "CreditReports"; mid = "2";
  dl = "dat_loc"; st ="Active"; std="process";
  rid = "ref_id1";
 insert_to_esb_request(s,d,mt,rid,mid,dl,st,std,"2020-08-12T05:18:00+00001");
 return 0;
}
*/