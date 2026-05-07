#pragma once

#ifndef TOKENS_H
#define TOKENS_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

typedef struct {
  Token type;
  char *value;
  int line;
} Token_Data;

typedef struct {
  Token_Data *items;
  size_t size;
  size_t capacity;
} Tokens_Array;

// GLOBAL TOKEN LIST
extern Tokens_Array *TOKENS;

// FUNCTIONS
void Tokens_Array_append(Token_Data *data);
void Tokens_Array_printf(void);

const char *token_to_string(Token token);

Tokens_Array *tokenize(char *data);

#endif
