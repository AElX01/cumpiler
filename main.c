#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ALLOC_IMPLEMENTATION
#include "alloc.h/alloc.h"
#include "lexer.h"

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

int main(void) {
  char *data = get_file_data("json_files/example_1.json");

  tokenize(data);

  Tokens_List_printf();

  return 0;
}
