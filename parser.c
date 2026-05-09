#include "parser.h"
#include "lexer.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// custom allocator
extern void *mem_alloc(size_t size);

Token peek(size_t offset) {
  if (TOKENS->current_token + offset < TOKENS->size) {
    return TOKENS->items[TOKENS->current_token + offset].type;
  }
  return T_EOF;
}

void match(Token expected_type) {
  if (TOKENS->current_token >= (int)TOKENS->size) {
    printf("Error: Unexpected End of File. Expected '%s'\n",
           token_to_string(expected_type));
    return;
  }

  Token current_type = TOKENS->items[TOKENS->current_token].type;
  int current_line = TOKENS->items[TOKENS->current_token].line;

  if (current_type == expected_type) {
    TOKENS->current_token++;
  } else {
    printf("Error in line %d. Expected '%s' and found '%s'\n", current_line,
           token_to_string(expected_type), token_to_string(current_type));

    static int last_error_token_index = -1;
    static int consecutive_failures_on_token = 0;

    if (last_error_token_index == TOKENS->current_token) {
      consecutive_failures_on_token++;
    } else {
      last_error_token_index = TOKENS->current_token;
      consecutive_failures_on_token = 1;
    }

    if (consecutive_failures_on_token > 4) {
      TOKENS->current_token++;
      consecutive_failures_on_token = 0;
    }
  }

  return;
}

void parse_Recipe() {
  match(T_LBRACE);
  match(T_K_RECETA);
  match(T_COLON);

  parse_Body_Recipe();

  match(T_RBRACE);

  return;
}

void parse_Body_Recipe() {
  match(T_LBRACE);

  parse_Date();

  match(T_COMMA);

  parse_Pacient();

  match(T_COMMA);

  parse_Doctor();

  match(T_COMMA);

  parse_Medicine();
  parse_Opt_Indications();

  match(T_RBRACE);
}

void parse_Date() {
  match(T_K_FECHA);
  match(T_COLON);
  match(T_STRING);
}

void parse_Pacient() {
  match(T_K_PACIENTE);
  match(T_COLON);
  match(T_LBRACE);
  match(T_K_NOMBRE);
  match(T_COLON);
  match(T_STRING);
  match(T_COMMA);
  match(T_K_EDAD);
  match(T_COLON);
  match(T_NUMBER);
  match(T_RBRACE);
}

void parse_Doctor() {
  match(T_K_MEDICO);
  match(T_COLON);
  match(T_LBRACE);
  match(T_K_NOMBRE);
  match(T_COLON);
  match(T_STRING);
  match(T_COMMA);
  match(T_K_CEDULA);
  match(T_COLON);

  parse_ID();

  match(T_RBRACE);
}

void parse_ID() {
  if (peek(0) == T_STRING) {
    match(T_STRING);
  } else if (peek(0) == T_NUMBER) {
    match(T_NUMBER);
  } else {
    match(T_STRING);
  }
}

void parse_Medicine() {
  match(T_K_MEDICAMENTOS);
  match(T_COLON);
  match(T_LBRACKET);

  parse_Prescription_List();

  match(T_RBRACKET);
}

void parse_Prescription() {
  match(T_LBRACE);
  match(T_K_NOMBRE);
  match(T_COLON);
  match(T_STRING);
  match(T_COMMA);

  parse_Dose();

  match(T_COMMA);

  parse_Frequency();

  match(T_COMMA);

  parse_Duration();
  parse_Opt_Condition();

  match(T_RBRACE);
}

void parse_Dose() {
  match(T_K_DOSIS);
  match(T_COLON);
  match(T_LBRACE);
  match(T_K_CANTIDAD);
  match(T_COLON);
  match(T_NUMBER);
  match(T_COMMA);
  match(T_K_UNIDAD);
  match(T_COLON);

  parse_Unit_Dose();

  match(T_RBRACE);
}

void parse_Unit_Dose() {
  if (peek(0) == T_U_MG) {
    match(T_U_MG);
  } else if (peek(0) == T_U_ML) {
    match(T_U_ML);
  } else {
    match(T_U_MG);
  }
}

void parse_Frequency() {
  match(T_K_FRECUENCIA);
  match(T_COLON);
  match(T_LBRACE);
  match(T_K_INTERVALO);
  match(T_COLON);
  match(T_NUMBER);
  match(T_COMMA);
  match(T_K_UNIDAD);
  match(T_COLON);
  match(T_U_HORAS);
  match(T_RBRACE);
}

void parse_Duration() {
  match(T_K_DURACION);
  match(T_COLON);
  match(T_LBRACE);
  match(T_K_CANTIDAD);
  match(T_COLON);
  match(T_NUMBER);
  match(T_COMMA);
  match(T_K_UNIDAD);
  match(T_COLON);
  match(T_U_DIAS);
  match(T_RBRACE);
}

void parse_Opt_Condition() {
  if (peek(0) == T_COMMA && peek(1) == T_K_CONDICION) {
    match(T_COMMA);
    match(T_K_CONDICION);
    match(T_COLON);
    match(T_STRING);
  }
  // otherwise, do nothing
}

void parse_Prescription_List() {
  parse_Prescription();

  if (peek(0) == T_COMMA && peek(1) == T_LBRACE) {
    match(T_COMMA);
    parse_Prescription_List();
  }
}

void parse_Opt_Indications() {
  if (peek(0) == T_COMMA && peek(1) == T_K_INDICACIONES) {
    match(T_COMMA);
    match(T_K_INDICACIONES);
    match(T_COLON);
    match(T_LBRACKET);

    parse_String_List();

    match(T_RBRACKET);
  }
  // otherwise, do nothing
}

void parse_String_List() {
  match(T_STRING);

  if (peek(0) == T_COMMA && peek(1) == T_STRING) {
    match(T_COMMA);

    parse_String_List();
  }
}

int start_parsing(void) {
  parse_Recipe();

  return 0;
}
