#include "parser.h"
#include "alloc.h/alloc.h"
#include <stdio.h>

// custom allocator
extern void *mem_alloc(size_t size);

Tokens_Stack *STACK = NULL;

void Tokens_Stack_push(Token_Data *data) {
  if (data == NULL)
    return;

  if (STACK == NULL) {
    STACK = mem_alloc(sizeof(Tokens_Stack));
    STACK->items = NULL;
    STACK->size = 0;
    STACK->capacity = 0;
  }

  if (STACK->items == NULL) {
    STACK->capacity = 256;
    STACK->size = 0;
    STACK->items = mem_alloc(STACK->capacity * sizeof(Token_Data));

  } else if (STACK->size >= STACK->capacity) {

    STACK->capacity <<= 1;

    Token_Data *temp =
        realloc(STACK->items, STACK->capacity * sizeof(Token_Data));

    if (temp == NULL) {
      perror("realloc failed");
      exit(EXIT_FAILURE);
    }

    STACK->items = temp;
  }

  STACK->items[STACK->size] = *data;
  STACK->size++;
}

int Tokens_Stack_is_empty(void) {
  if (STACK == NULL)
    return 1;
  return STACK->size == 0 ? 1 : 0;
}

int Tokens_Stack_pop(Token_Data *out_data) {
  if (Tokens_Stack_is_empty())
    return 0;

  STACK->size--;

  if (out_data != NULL) {
    *out_data = STACK->items[STACK->size];
  }

  memset(&STACK->items[STACK->size], 0, sizeof(Token_Data));

  return 1;
}

int transform_array_to_stack() {
  if (TOKENS == NULL)
    return 0;

  STACK = mem_alloc(sizeof(Tokens_Stack));
  if (STACK == NULL) {
    perror("Failed mem_alloc");
    exit(EXIT_FAILURE);
  }
  STACK->items = TOKENS->items;
  STACK->size = TOKENS->size;
  STACK->capacity = TOKENS->capacity;

  return 1;
}

int parse() {
  transform_array_to_stack();

  Token_Data token;

  if (!Tokens_Stack_pop(&token)) {
    perror("Failed pop");
  }

  printf("================== Parser =====================\n\n");
  printf("Token: %s\n"
         "Value: %s\n"
         "Line: %d\n\n",
         token_to_string(token.type), token.value, token.line);

  return 1;
}
