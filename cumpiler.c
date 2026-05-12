#include "lexer.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
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

  size_t file_length = (size_t)ftell(file);

  char *data = mem_alloc((size_t)file_length);

  fseek(file, 0, SEEK_SET);

  if (fread(data, sizeof(char), file_length, file) != file_length) {
    fclose(file);
    free_all();
    exit(EXIT_FAILURE);
  }

  fclose(file);

  return data;
}

void print_help(void) { printf("Usage: cumpiler file"); }

int main(int argc, char **argv) {
  if (argc <= 1) {
    print_help();
    exit(EXIT_FAILURE);
  }

  char *file = argv[1];

  char *data = get_file_data(file);

  tokenize(data);

  if (TOKENS == NULL || TOKENS->size == 0) {
    printf("Lexer Error: No valid tokens found\n");
    free_all();
    exit(EXIT_FAILURE);
  }

  start_parsing();

  free_all();

  return 0;
}
