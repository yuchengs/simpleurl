// Based on RFC 1738 and RFC 3986, url parser

#ifndef URL_H
#define URL_H

#include <string.h>
#include <stdbool.h>

typedef struct Url {
  char *scheme;
  char *hostname;
  char *port;
  char *path;
  char *query;
  char *fragment;
  char *username;
  char *password;
} Url;


Url* urlParse(char* urlString);
void urlFree(Url *url);

#endif
