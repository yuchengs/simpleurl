#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "url.h"

#define ufree(p) if (p) { free(p); p = NULL; }

static __inline__ bool _isSchemeChar(char c) {
  return (isalpha(c) || c == '+' || c == '-' || c == '.');
}

char* _updateField(char* start, char* end) {
  char* field = malloc(sizeof(char) * (end - start + 1));
  strncpy(field, start, (end - start));
  field[end - start] = '\0';
  return field;
}

Url* urlParse(char* urlString) {
  char* tmp;
  char* cur;
  int iter;
  bool optional_field_flag;

  Url* url = malloc(sizeof(Url));
  memset(url, 0, sizeof(Url));

  cur = urlString;
  tmp = strchr(cur, ':');
  for (iter = 0; iter < tmp - cur; iter++) {
    if (!_isSchemeChar(cur[iter])) {
      urlFree(url);
      return NULL;
    }
  }
  url->scheme = _updateField(cur, tmp);

  tmp++;
  cur = tmp;

  if (*cur != '/' || *(cur + 1) != '/') {
    urlFree(url);
    return NULL;
  }
  cur += 2;
  tmp = cur;

  optional_field_flag = false;
  while (*tmp != '\0') {
    if (*tmp == '@') {
      optional_field_flag = true;
      break;
    } else if (*tmp == '/') {
      optional_field_flag = false;
      break;
    }
    tmp++;
  }
  tmp = cur;

  if (optional_field_flag) {
    // username and password
    while (*tmp != ':' && *tmp != '@') {
      tmp++;
    }
    url->username = _updateField(cur, tmp);
    cur = tmp;
    if (*cur == ':') {
      cur++;
      tmp = cur;
      while (*tmp != '@') {
        tmp++;
      }
      url->password = _updateField(cur, tmp);
      cur = tmp;
    }
    // assert( *cur == '@');
    cur++;
  }

  tmp = cur;
  optional_field_flag = (*cur == '[') ? true : false;

  while (*tmp != '\0') {
    if (optional_field_flag && *tmp == ']') {
      tmp++;
      break;
    }
    else if (!optional_field_flag && (*tmp == '/' || *tmp == ':')) {
      break;
    }
    tmp++;
  }
  if (tmp == cur) {
    urlFree(url);
    return NULL;
  }
  url->hostname = _updateField(cur, tmp);
  cur = tmp;

  if (*cur == ':') {
    cur++;
    tmp = cur;
    while (*tmp != '\0' && *tmp != '/' ) {
        tmp++;
    }
    url->port = _updateField(cur, tmp);
    cur = tmp;
  }

  if (*cur == '\0') {
    return url;
  }

  if (*cur != '/') {
    urlFree(url);
    return NULL;
  }
  cur++;
  tmp = cur;

  while (*tmp != '\0' && *tmp != '#'  && *tmp != '?' ) {
    tmp++;
  }
  url->path = _updateField(cur, tmp);
  cur = tmp;

  if (*cur == '?') {
    cur++;
    tmp = cur;
    while (*tmp != '\0' && *tmp != '#' ) {
      tmp++;
    }
    url->query = _updateField(cur, tmp);
    cur = tmp;
  }
  if (*cur == '#') {
    cur++;
    tmp = cur;
    while (*tmp != '\0') {
      tmp++;
    }
    url->fragment = _updateField(cur, tmp);
    cur = tmp;
  }

  return url;
}

void urlFree(Url* url) {
  if (url) {
    ufree(url->scheme);
    ufree(url->hostname);
    ufree(url->port);
    ufree(url->path);
    ufree(url->query);
    ufree(url->fragment);
    ufree(url->username);
    ufree(url->password);
    free(url);
    url = NULL;
  }
}
