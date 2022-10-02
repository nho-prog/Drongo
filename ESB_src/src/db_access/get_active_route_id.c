/**
 * @file get_active_route_id.c
 * @author MubeenS
 * @brief Function returns route_id of a route if exists by performing
 * sql query:SELECT route_id                                 
 * FROM routes WHERE sender = ?                                         
 * AND message_type = ? AND destination = ? AND is_active=1
 * 
 * returns 0 if route does not exist.
 * @version 0.1
 * @date 2020-09-05
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <stdio.h>
#include <string.h>
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
#define SELECT_QUERY "SELECT route_id                                 \
FROM routes WHERE sender = ?                                          \
AND message_type = ? AND destination = ? AND is_active=1"


 
 
int get_active_route_id(char *sender,char *destination, char *message_type) {
    
    printf("Getting active route id..\n");
    MYSQL_STMT *stmt; /* store statement */
    MYSQL_BIND input_bind[3]; /* to bind input */
    char input_data[3][STRING_SIZE];
    unsigned long input_length[3];
    MYSQL_BIND bind[1];
    //my_ulonglong affected_rows;
    MYSQL_RES *prepare_meta_result;
    //unsigned long length[4];
    int param_count;
    //char small_data[STRING_SIZE];
    int int_data;
    //bool is_null[3];

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
    if (con == NULL) {

        fprintf(stderr, "mysql_init() failed\n");
        return -1;
    }

    /**
   * @brief Checks if connection is 
   * properly established.
   * 
   */
    if (mysql_real_connect(con, HOST, USER, PASS,DB_NAME, 
                            PORT, UNIX_SOCKET, FLAG) == NULL) {
        finish_with_error(con);
    }

    stmt = mysql_stmt_init(con);
    if (!stmt) {
        fprintf(stderr, " mysql_stmt_init(), out of memory\n");
        return -1;
    }

    if (mysql_stmt_prepare(stmt, SELECT_QUERY, strlen(SELECT_QUERY))) {
        fprintf(stderr, " mysql_stmt_prepare(), SELECT failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        return -1;
    }

    /* Get the parameter count from the statement */
    param_count = mysql_stmt_param_count(stmt);

    /* validate parameter count */
    if (param_count != 3) {
        fprintf(stderr, " invalid parameter count returned by MySQL\n");
        return -1;
    }

    /* Fetch result set meta information */
    prepare_meta_result = mysql_stmt_result_metadata(stmt);
    if (!prepare_meta_result) {
        fprintf(stderr,"mysql_stmt_result_metadata(),           \
        returned no meta information\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        return -1;
    }

    memset(input_bind, 0, sizeof(input_bind));

    /* Sender */
    input_bind[0].buffer_type = MYSQL_TYPE_STRING;
    input_bind[0].buffer = (char *)input_data[0];
    input_bind[0].buffer_length = STRING_SIZE;
    input_bind[0].is_null = 0;
    input_bind[0].length = &input_length[0];

    /* Message_type */
    input_bind[1].buffer_type = MYSQL_TYPE_STRING;
    input_bind[1].buffer = (char *)&input_data[1];
    input_bind[1].is_null = 0;
    input_bind[1].length = &input_length[1];
    input_bind[1].buffer_length = STRING_SIZE;
    
    /* destination */
    input_bind[2].buffer_type = MYSQL_TYPE_STRING;
    input_bind[2].buffer = (char *)&input_data[2];
    input_bind[2].is_null = 0;
    input_bind[2].length = &input_length[2];
    input_bind[2].buffer_length = STRING_SIZE;

    /* Bind the buffers */
    if (mysql_stmt_bind_param(stmt, input_bind))  {
        fprintf(stderr, " mysql_stmt_bind_param() failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        return -1;
    }
    
    /* Copy input data from function parameters */
    strncpy(input_data[0], sender, STRING_SIZE);
    input_length[0] = strlen(input_data[0]);
    strncpy(input_data[1], message_type, STRING_SIZE);
    input_length[1] = strlen(input_data[1]);
    strncpy(input_data[2], destination, STRING_SIZE);
    input_length[2] = strlen(input_data[2]);

    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, " mysql_stmt_execute, 2 failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        return -1;
    }

    /* Bind the result buffers for all 4 columns before fetching them */

    memset(bind, 0, sizeof(bind));

    /*  route_id */
    bind[0].buffer_type = MYSQL_TYPE_LONG;
    bind[0].buffer = &int_data;
    bind[0].buffer_length = STRING_SIZE;
    bind[0].is_null = 0;

    /* Bind the result buffers */
    if (mysql_stmt_bind_result(stmt, bind)) {
        fprintf(stderr, " mysql_stmt_bind_result() failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        return -1;
    }

    /* Now buffer all results to client */
    if (mysql_stmt_store_result(stmt))  {
        fprintf(stderr, " mysql_stmt_store_result() failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        return -1;
    }
    int route_id=0;

    if(!mysql_stmt_fetch(stmt)) {
        
        route_id = int_data;
        /* Free the result */
        mysql_free_result(prepare_meta_result);
        
        /* Close the statement */
         if (mysql_stmt_close(stmt)) {
        fprintf(stderr, " failed while closing the statement\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        return -1;
        }
        /*closes the database connection*/
       mysql_close(con);
        
        return route_id;
    }else{
        printf("No routes found..\n");
    }

    /* Free the prepared result metadata */
    mysql_free_result(prepare_meta_result);

    /* Close the statement */
    if (mysql_stmt_close(stmt)) {
        fprintf(stderr, " failed while closing the statement\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        return -1;
    }

    /*closes the database connection*/
    mysql_close(con);
    /* returns number of rows in result */
    return 0;
}

/*int main(int argc, char **argv) {
    char *sender = "A";
    char *message_type = "xml";
    int id = get_active_route_id(sender,"Y",message_type);
    printf("id = %d",id);
    return 0;
}*/