// lexer.h
/**
 * @file lexer.h
 * @brief Lexical analyzer definitions and state structures.
 *
 * This header defines the token types, token metadata, and the core data
 * structures used to capture and traverse the token stream generated from
 * the raw input source.
 */

#pragma once

#ifndef LEXER_H
#define LEXER_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Enumeration of all valid terminal symbols in the grammar.
 */
typedef enum {
  // STRUCTURAL
  T_LBRACE,
  T_RBRACE,
  T_LBRACKET,
  T_RBRACKET,
  T_COLON,
  T_COMMA,

  // LITERALS
  T_STRING,
  T_NUMBER,

  // REGEX VALIDATION
  T_V_DATE,
  T_V_ID,

  // KEYWORDS
  T_K_RECETA,
  T_K_FECHA,
  T_K_PACIENTE,
  T_K_MEDICO,
  T_K_NOMBRE,
  T_K_EDAD,
  T_K_CEDULA,
  T_K_MEDICAMENTOS,
  T_K_DOSIS,
  T_K_FRECUENCIA,
  T_K_DURACION,
  T_K_CANTIDAD,
  T_K_UNIDAD,
  T_K_INTERVALO,
  T_K_CONDICION,
  T_K_INDICACIONES,

  // UNITS
  T_U_MG,
  T_U_ML,
  T_U_HORAS,
  T_U_DIAS,

  // SPECIAL
  T_EOF,
  T_ERROR
} Token;

/**
 * @brief Encapsulates a single lexical token along with its source metadata.
 */
typedef struct {
  Token type;  /**< The categorized terminal type of the token. */
  char *value; /**< The string literal value parsed from the source. */
  int line;    /**< The source line number where this token was encountered. */
  int column;  /**< The source column number. */
} Token_Data;

/**
 * @brief A dynamic array serving as the primary input tape for the parser.
 *
 * @details
 * Conceptually, `Tokens_Array` serves as the sequential input tape for the
 * syntactic analyzer. In the context of parsing a context-free grammar,
 * the compiler operates as a Pushdown Automaton (PDA). A deterministic PDA
 * relies on an input string of terminal symbols and a stack to keep track
 * of nested grammatical rules.
 *
 * Here, `Tokens_Array` functions precisely as that theoretical input tape.
 * The `items` array dynamically stores the sequential symbols recognized by
 * the lexer. The `current_token` integer acts as the "read-head" of the PDA.
 * As the recursive descent parser executes, it implicitly utilizes the C
 * function call stack as the PDA's pushdown stack. When a transition occurs
 * (via the `match()` function), the read-head (`current_token`) advances to
 * the next input state.
 *
 * By dynamically resizing (`capacity` and `size`), we emulate the theoretically
 * infinite input stream capacity required by mathematical PDA models, bounded
 * only by the system's underlying memory constraints.
 */
typedef struct {
  Token_Data
      *items;  /**< The dynamically allocated buffer of tokens (the tape). */
  size_t size; /**< The total number of valid tokens currently in the array. */
  size_t capacity;   /**< The allocated capacity of the array. */
  int current_token; /**< The active read-head index used during the parsing
                        phase. */
} Tokens_Array;

extern Tokens_Array *TOKENS;

/**
 * @brief Appends a new token into the global token array.
 * @details Dynamically resizes the underlying buffer if capacity is reached.
 *
 * @param data A pointer to the initialized Token_Data structure to be stored.
 */
void Tokens_Array_append(Token_Data *data);

/**
 * @brief Dumps the contents of the token array to standard output.
 * @details Used primarily for debugging and tracing the lexer's output state.
 */
void Tokens_Array_printf(void);

/**
 * @brief Converts a Token enumeration value to its string representation.
 *
 * @param token The Token type to stringify.
 * @return A constant null-terminated string representing the token name.
 */
const char *token_to_string(Token token);

/**
 * @brief Performs lexical analysis on the raw source string.
 *
 * @details Reads the raw character data sequentially, matching literal
 * characters, keywords, numbers, and validating complex fields (like dates
 * and IDs) via regular expressions. Populates the global TOKENS array.
 *
 * @param data The raw character buffer containing the source code.
 * @return A pointer to the initialized and populated Tokens_Array structure.
 */
Tokens_Array *tokenize(char *data);

#endif
