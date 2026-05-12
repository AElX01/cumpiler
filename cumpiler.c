#include "lexer.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ALLOC_IMPLEMENTATION
#include "parser.h"
#include "thirdparty/alloc.h/alloc.h"

void *get_file_data(const char *path) {
  FILE *file = fopen(path, "r");

  if (file == NULL) {
    perror("Error: File not found");
    exit(EXIT_FAILURE);
  }

  fseek(file, 0, SEEK_END);

  size_t file_length = ftell(file);

  char *data = mem_alloc(file_length);

  fseek(file, 0, SEEK_SET);

  fread(data, sizeof(char), file_length, file);

  fclose(file);

  return data;
}

void print_help() { printf("Usage: cumpiler file"); }

int main(int argc, char **argv) {
  if (argc <= 1)
    print_help();

  char *file = argv[1];

  char *data = get_file_data(file);

  tokenize(data);

  // Tokens_Array_printf();

  if (TOKENS == NULL || TOKENS->size == 0) {
    printf("Lexer Error: No valid tokens found\n");
    free_all();
    return EXIT_FAILURE;
  }

  start_parsing();

  free_all();

  return 0;
}
