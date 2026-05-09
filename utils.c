#include <regex.h>
#include <stddef.h>

int match_regex(const char *string, const char *pattern) {
  regex_t regex;

  if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
    return 0;
  }

  if (regexec(&regex, string, 0, NULL, 0) != 0) {
    regfree(&regex);
    return 0;
  }
  regfree(&regex);

  return 1;
}
