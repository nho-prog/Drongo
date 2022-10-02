/**
 * @file update_esb_request.c
 * @author MubeenS
 * @brief The program is a C API for the SQL query
 * UPDATE esb_request SET status = ? WHERE id = ? .
 * The function returns 1 if update is successful,
 * else returns zero.
 * @version 1.0
 * @date 2020-09-01
 * 
 * @copyright Copyright (c) 2020
 * 
 */

/*Required C standard libraries*/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
/* Contains necessary C functions of mysql */
#include <mysql.h>

/**
 * Holds the info to connect to DB and
 * error specifying function for 
 * databse connection handle 
 */
#include "connector.h"

#define STRING_SIZE 100

#define UPDATE_QUERY "UPDATE esb_request SET status = ? WHERE id = ? "

int update_esb_request(char *status, int id)
{

  printf("Updating esb_request status...\n");

  MYSQL_STMT *stmt;
  MYSQL_BIND bind[2];
  my_ulonglong affected_rows;
  int param_count;
  int id_data;
  char status_data[STRING_SIZE];
  unsigned long str_length;
  bool is_null;

  MYSQL *con; /*database connection handle*/
  /**
   * @brief Allocates or initialises a MYSQL object 
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
  /* Prepare an UPDATE query with 3 parameters */
  stmt = mysql_stmt_init(con);
  if (!stmt)
  {
    fprintf(stderr, " mysql_stmt_init(), out of memory\n");
    return -1;
  }

  if (mysql_stmt_prepare(stmt, UPDATE_QUERY, strlen(UPDATE_QUERY)))
  {
    fprintf(stderr, " mysql_stmt_prepare(), UPDATE failed\n");
    fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
    return -1;
  }
  //fprintf(stdout, "prepare, UPDATE successful\n");

  /* Get the parameter count from the statement */
  param_count = mysql_stmt_param_count(stmt);
  //fprintf(stdout, " total parameters in UPDATE: %d\n", param_count);

  /* validate parameter count */
  if (param_count != 2)
  {
    fprintf(stderr, " invalid parameter count returned by MySQL\n");
    return -1;
  }

  /* Bind the data for 2 parameters */
  memset(bind, 0, sizeof(bind));

  /* STRING PARAM */
  bind[0].buffer_type = MYSQL_TYPE_STRING;
  bind[0].buffer = (char *)&status_data;
  bind[0].is_null = 0;
  bind[0].length = &str_length;
  bind[0].buffer_length = STRING_SIZE;

  /* INTEGER id PARAM */
  bind[1].buffer_type = MYSQL_TYPE_LONG;
  bind[1].buffer = (char *)&id_data;
  bind[1].is_null = 0;
  bind[1].length = 0;

  /* Bind the buffers */
  if (mysql_stmt_bind_param(stmt, bind))
  {
    fprintf(stderr, " mysql_stmt_bind_param() failed\n");
    fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
    return -1;
  }

  id_data = id;
  strncpy(status_data, status, STRING_SIZE);
  str_length = strlen(status_data);

  /* Execute the UPDATE statement*/
  if (mysql_stmt_execute(stmt))
  {
    fprintf(stderr, " mysql_stmt_execute, failed\n");
    fprintf(stderr, " [%d]%s\n", mysql_stmt_errno(stmt),
            mysql_stmt_error(stmt));
    return -1;
  }

  /* Get the total rows affected */
  //affected_rows = mysql_stmt_affected_rows(stmt);
  //fprintf(stdout, " total affected rows(UPDATE 2): %lu\n",
    //      (unsigned long)affected_rows);

  /* validate affected rows */
  /*if (affected_rows != 1) {
  fprintf(stderr, " invalid affected rows by MySQL\n");
  return -1;
   }*/

  /* Close the statement */
  if (mysql_stmt_close(stmt))
  {
    fprintf(stderr, " failed while closing the statement\n");
    fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
    return -1;
  }
  //printf("connection id: %ld\n", mysql_thread_id(con));

  mysql_close(con);
  return 1;
}

/*testing with a sample input*/
/*int main() {
  char *s;
  s = "done";
 update_esb_request(&s,1);
 return 0;
}*/