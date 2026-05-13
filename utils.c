// utils.c
#include "thirdparty/tiny-regex-c/re.h"
#include <stddef.h>

int match_regex(const char *string, const char *pattern) {
  int match_length;

  int match_index = re_match(pattern, string, &match_length);

  return (match_index != -1);
}
