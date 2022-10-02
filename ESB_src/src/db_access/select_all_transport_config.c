/**
 * @file select_all_routes.c
 * @author MubeenS 
 * @brief  The program is a C API for the SQL query 
 * SELECT * FROM transport_config WHERE route_id=? ;
 * @version 0.1
 * @date 2020-08-29
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <stdio.h>
/* Contains necessary C functions of mysql */
#include <mysql.h>
/**
 * Holds the info to connect to DB and
 * error specifying function for 
 * databse connection handle 
 */
#include "connector.h"
#define STRING_SIZE 100

 
void select_all_transport_config(int route_id) {      

  MYSQL *con ;  /*database connection handle*/
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
  if (con == NULL) {

      fprintf(stderr, "mysql_init() failed\n");
      exit(1);
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
  char query[STRING_SIZE]; /*to store query*/

  /*Fill in the query with parameters*/
  sprintf(query,
  "SELECT * FROM transport_config WHERE route_id = %d ",
  route_id);
  printf("For query :%s\n",query);
  /*checks execution of SQL statement*/
  if (mysql_query(con, query)) {
      finish_with_error(con);
  }

  MYSQL_RES *result;/*structure that holds result set*/

  /* Gets the result set and stores in result */
  result = mysql_store_result(con); 
  
  /* if there is no result error will be returned*/
  if (result == NULL) {
      finish_with_error(con);
  }

  /* stores number of fields in the result*/ 
  int num_fields = mysql_num_fields(result);
  /*mysql structure that holds a row*/
  MYSQL_ROW row;
  /*mysql structure that holds field values*/
  MYSQL_FIELD *field;

  /*prints all the rows from the result*/
  while ((row = mysql_fetch_row(result))) { 
      for(int i = 0; i < num_fields; i++) { 
          if(i==0) {
              while((field = mysql_fetch_field(result))) {
                  printf(" %s |", field->name);
              } 
              printf("\n");
            }

          printf(" %s |", row[i] ? (char *)row[i] : "NULL"); 
      } 
          printf("\n"); 
  }
  
  /*frees the result*/
  mysql_free_result(result);
  /*closes the database connection*/
  mysql_close(con);
  
  exit(0);
}

/*int main () {
    int route_id = 1;
    select_all_transport_config(route_id);
    return 0;
}*/