#pragma once

#ifndef PARSER_H
#define PARSER_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"

typedef struct Tokens_Stack Tokens_Stack;

struct Tokens_Stack {
  Token_Data *items;
  size_t size;
  size_t capacity;
};

// GLOBAL TOKEN LIST
extern Tokens_Stack *STACK;

// FUNCTIONS
void Tokens_Stack_push(Token_Data *data);
int Tokens_Stack_is_empty(void);
int Tokens_Stack_pop(Token_Data *out_data);

int transform_array_to_stack();

int parse();

#endif
