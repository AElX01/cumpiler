#include "parser.h"
#include <stdio.h>

// custom allocator
extern void *mem_alloc(size_t size);

int match(Token_Data *expected_type) {
  if (TOKENS->items[TOKENS->current_token].type == expected_type->type) {
    TOKENS->current_token++;
    return 1;
  }

  printf("Error in line %d. Expected '%s' and found '%s'",
         TOKENS->items[TOKENS->current_token].line,
         token_to_string(expected_type->type),
         token_to_string(TOKENS->items[TOKENS->current_token].type));

  return 0;
}

void parse_Receta() {}

int start_parsing(void) {
  parse_Receta();
  return 0;
}
