/**
 * @file get_active_route_id.c
 * @author MubeenS
 * @brief Function returns id of a route if exists by performing
 * sql query:SELECT config_key,config_value, FROM transform_config 
 * WHERE route_id = ?
 * returns 0 if route does not exist.
 * 
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

/** Contains transform_config structure */

#include "adapter/adapter.h"

#define STRING_SIZE 100
#define SELECT_QUERY "SELECT config_key,config_value   \
FROM transform_config WHERE route_id = ? "

transform_t* fetch_transform_config(int route_id)
{  
    printf(">> Fetching transform details..\n");

    MYSQL_STMT *stmt;         /* store statement */
    MYSQL_BIND input_bind[1]; /* to bind input */
    MYSQL_BIND res_bind[2];
    int route_id_data;
    MYSQL_RES *prepare_meta_result;
    unsigned long length[3];
    int param_count,column_count;
    char config_key[STRING_SIZE];
    char config_value[STRING_SIZE];
    bool is_null[3];
    bool error[3];

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
       return NULL;
    }

    /**
   * @brief Checks if connection is 
   * properly established.
   * 
   */
    if (mysql_real_connect(con, HOST, USER, PASS, DB_NAME,
                           PORT, UNIX_SOCKET, FLAG) == NULL)
    {
        finish_with_error(con);
    }

    stmt = mysql_stmt_init(con);
    if (!stmt)
    {
        fprintf(stderr, " mysql_stmt_init(), out of memory\n");
       return NULL;
    }

    if (mysql_stmt_prepare(stmt, SELECT_QUERY, strlen(SELECT_QUERY)))
    {
        fprintf(stderr, " mysql_stmt_prepare(), SELECT failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
       return NULL;
    }

    /* Get the parameter count from the statement */
    param_count = mysql_stmt_param_count(stmt);

    /* validate parameter count */
    if (param_count != 1)
    {
        fprintf(stderr, " invalid parameter count returned by MySQL\n");
       return NULL;
    }

    /* Fetch result set meta information */
    prepare_meta_result = mysql_stmt_result_metadata(stmt);
    if (!prepare_meta_result)
    {
        fprintf(stderr, "mysql_stmt_result_metadata(),           \
        returned no meta information\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
       return NULL;
    }
    	/* Get total columns in the query */
	column_count= mysql_num_fields(prepare_meta_result);
	//fprintf(stdout, " total columns in SELECT statement: %d\n", column_count);

	if (column_count != 2) /* validate column count */
	{
	  fprintf(stderr, " invalid column count returned by MySQL\n");
	    return 0;
	}

    memset(input_bind, 0, sizeof(input_bind));

    /* Route-id */
    input_bind[0].buffer_type = MYSQL_TYPE_LONG;
    input_bind[0].buffer = (char *)&route_id_data;
    input_bind[0].is_null = 0;
    input_bind[0].length = &length[0];
    /* Bind the buffers */
    if (mysql_stmt_bind_param(stmt, input_bind))
    {
        fprintf(stderr, " mysql_stmt_bind_param() failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
       return NULL;
    }

    /* Copy input data from function parameters */
    route_id_data = route_id;

    if (mysql_stmt_execute(stmt))
    {
        fprintf(stderr, " mysql_stmt_execute, 2 failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
       return NULL;
    }

    /* Bind the result buffers for all 4 columns before fetching them */

    memset(res_bind, 0, sizeof(res_bind));

    /* Config_key*/
    res_bind[0].buffer_type = MYSQL_TYPE_STRING;
    res_bind[0].buffer = (char *)&config_key;
    res_bind[0].buffer_length = STRING_SIZE;
    res_bind[0].is_null = &is_null[1];
    res_bind[0].length = &length[1];
    res_bind[0].error  = &error[1];

    /* Config_value */
    res_bind[1].buffer_type = MYSQL_TYPE_STRING;
    res_bind[1].buffer = (char *)&config_value;
    res_bind[1].buffer_length = STRING_SIZE;
    res_bind[1].is_null = &is_null[2];
    res_bind[1].length = &length[2];
    res_bind[1].error  = &error[2];


    /* Bind the result buffers */
    if (mysql_stmt_bind_result(stmt, res_bind))
    {
        fprintf(stderr, " mysql_stmt_bind_result() failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
       return NULL;
    }

    /* Now buffer all results to client */
    if (mysql_stmt_store_result(stmt))
    {
        fprintf(stderr, " mysql_stmt_store_result() failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
       return NULL;
    }
    
    /* allocating config structure to return */
    transform_t *config;
    config = (transform_t *)malloc(sizeof(transform_t));

    if (!mysql_stmt_fetch(stmt))
    {
        config->key = strdup(config_key);
        config->value = strdup(config_value);
        /* Free the result */
        mysql_free_result(prepare_meta_result);

        /* Close the statement */
        if (mysql_stmt_close(stmt))
        {
            fprintf(stderr, " failed while closing the statement\n");
            fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
           return NULL;
        }
        /*closes the database connection*/
        mysql_close(con);

        return config;
    }
    else
    {
        printf("No transform_config exists for route_id.");
    }

    /* Free the prepared result metadata */
    mysql_free_result(prepare_meta_result);

    /* Close the statement */
    if (mysql_stmt_close(stmt))
    {
        fprintf(stderr, " failed while closing the statement\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
       return NULL;
    }

    /*closes the database connection*/
    mysql_close(con);
    /* returns number of rows in result */
    return NULL;
}

/*int main(int argc, char **argv)
{
    transform_t* t = fetch_transform_config(1);
    printf("%s  %s", t->key,t->value);
    return 0;
}*/