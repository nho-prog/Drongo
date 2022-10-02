/**
 * @file http_post.c
 * @author MubeenS
 * @brief The program posts a HTTP request 
 * to specified url and returns file path.
 * @version 0.1
 * @date 2020-09-13
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <stdlib.h>
#include <stdio.h>

#include <curl/curl.h>

#include "adapter.h"

#define STRING_SIZE 100

int print_file(char *file_name)
{
  FILE *fptr;

  char c;

  // Open file
  fptr = fopen(file_name, "r");
  if (fptr == NULL)
  {
    printf("Cannot open file \n");
    return 0;
  }

  // Read contents from file
  c = fgetc(fptr);
  while (c != EOF)
  {
    printf("%c", c);
    c = fgetc(fptr);
  }

  fclose(fptr);
  return 1;
}

/**
 * @brief posts request to HTTP url
 * and stores response in a file and 
 * returns it's path.
 * 
 * @param to URL to post
 * @param data to be posted
 * @return char* File path of response
 */
void* http_post(void *toptr, void *dataptr)
{
  char *to = (char *)toptr;
  char *data = (char *)dataptr;

  CURL *curl;
  CURLcode res;

  char *file_name = "Returnfile.json";

  FILE *fp = fopen(file_name, "wb");

  curl_global_init(CURL_GLOBAL_ALL);

  /* get a curl handle */
  curl = curl_easy_init();
  if (curl)
  {

    /* Req res is a free api we can test on it 
     * "https://reqres.in/api/users"*/
    curl_easy_setopt(curl, CURLOPT_URL, to);
    /* Now specify the POST data */

    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);

    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);
    /* Check for errors */
    if (res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    /* always cleanup */
    curl_easy_cleanup(curl);
  }
  curl_global_cleanup();
  fclose(fp);
  return (void*)file_name;
}

/*int main()
{
  char *fn = http_post("https://reqres.in/api/users", "name=Test&job=Testing");

  int b = print_file(fn);

  return b;
}*/