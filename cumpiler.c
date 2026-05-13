// cumpiler.c
/**
 * @file cumpiler.c
 * @brief Entry point for the compiler application.
 *
 * This file coordinates the reading of the source file into memory,
 * invokes the lexical analyzer (lexer) to generate the token stream,
 * and initiates the recursive descent parser to validate the syntax
 * and semantics of the input.
 */

#include "lexer.h"
#include "parser.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#define ALLOC_IMPLEMENTATION
#include "thirdparty/alloc.h/alloc.h"

/**
 * @brief Reads the entire contents of a file into a dynamically allocated
 * buffer.
 *
 * @details This function is necessary to load the source code into memory so
 * that the lexical analyzer can process it as a contiguous string. It relies on
 * custom memory allocators to manage the buffer.
 *
 * @param path Null-terminated string representing the path to the target file.
 * @return A void pointer (castable to char*) containing the file data.
 * The application exits automatically with EXIT_FAILURE if the file
 * cannot be read or memory cannot be allocated.
 */
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

/**
 * @brief Prints the standard command-line usage instructions.
 */
void print_help(void) { printf("Usage: cumpiler file"); }

/**
 * @brief The main execution pipeline of the compiler.
 *
 * @param argc The count of command-line arguments.
 * @param argv The vector of command-line arguments.
 * @return Returns 0 upon successful compilation, or terminates via exit() on
 * failure.
 */
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
