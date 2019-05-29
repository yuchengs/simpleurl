#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "url.h"

int main() {
  char* urlString01 = "http://www.baidu.com";
  Url* url01 = urlParse(urlString01);
  assert(strcmp(url01->scheme, "http") == 0);
  assert(strcmp(url01->hostname, "www.baidu.com") == 0);

  char* urlString02 = "https://euca:123@www.baidu.com:80";
  Url* url02 = urlParse(urlString02);
  assert(strcmp(url02->scheme, "https") == 0);
  assert(strcmp(url02->username, "euca") == 0);
  assert(strcmp(url02->password, "123") == 0);
  assert(strcmp(url02->hostname, "www.baidu.com") == 0);
  assert(strcmp(url02->port, "80") == 0);

  char* urlString03 = "https://euca:123@www.baidu.com:80/this/is/a/path?search=item";
  Url* url03 = urlParse(urlString03);
  assert(strcmp(url03->scheme, "https") == 0);
  assert(strcmp(url03->username, "euca") == 0);
  assert(strcmp(url03->password, "123") == 0);
  assert(strcmp(url03->hostname, "www.baidu.com") == 0);
  assert(strcmp(url03->port, "80") == 0);
  assert(strcmp(url03->path, "this/is/a/path") == 0);
  assert(strcmp(url03->query, "search=item") == 0);

  return 0;
}
