#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define STRING_SIZE 100
struct string
{
  char *ptr;
  size_t len;
};

int init_string(struct string *s)
{
  s->len = 0;
  s->ptr = malloc(s->len + 1);
  if (s->ptr == NULL)
  {
    fprintf(stderr, "malloc() failed\n");
    return -1;
  }
  s->ptr[0] = '\0';
}

size_t write_callback(void *ptr, size_t size, size_t nmemb, struct string *s)
{
  size_t new_len = s->len + size * nmemb;
  s->ptr = realloc(s->ptr, new_len + 1);
  if (s->ptr == NULL)
  {
    fprintf(stderr, "realloc() failed\n");
    return -1;
  }
  memcpy(s->ptr + s->len, ptr, size * nmemb);
  s->ptr[new_len] = '\0';
  s->len = new_len;
  return size * nmemb;
}

void *call_destination_service(void *urlptr, void *apiptr)
{
  /* Converting URL to string */
  char *url = (char *)urlptr;
  char *api = (char *)apiptr;
  CURL *curl;
  CURLcode res;

  curl = curl_easy_init();
  struct string s;
  int rc = init_string(&s);
  if(rc==-1) {
    printf("String init failed.\n");
  }
  /* Checks if curl is initialised properly and 
   * performs required operations */

  if (curl)
  {
    printf(">> Contacting destination service %s\n", api);
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
    /* Verbose is to check what happens within curl */
    //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    res = curl_easy_perform(curl);

    if (res != CURLE_OK)
    {
      fprintf(stderr, "Contacting destination service failed.\n  \
                               Please try again..!\n");
      return (void *)res;
    }

    /* always cleanup */
    curl_easy_cleanup(curl);
  }
  curl_global_cleanup();

  return (void *)s.ptr;
}

/*int main()
{
  char *s = call_destination_service("IDIB000N068");
  printf("%s", s);
  return 0;
}*/