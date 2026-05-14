// parser.c
#include "parser.h"
#include "lexer.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern void *mem_alloc(size_t size);

const char *get_current_token_value(void) {
  if (TOKENS->current_token < (int)TOKENS->size) {
    return TOKENS->items[TOKENS->current_token].value;
  }
  return "";
}

int get_current_token_int(void) { return atoi(get_current_token_value()); }

Token peek(size_t offset) {
  if ((size_t)TOKENS->current_token + offset < TOKENS->size) {
    return TOKENS->items[(size_t)TOKENS->current_token + offset].type;
  }
  return T_EOF;
}

void match(Token expected_type) {
  if (TOKENS == NULL || TOKENS->items == NULL) {
    printf("Parser Error: No tokens available\n");
    return;
  }
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

    TOKENS->current_token++;
  }
}

void validate_medicine_semantics(const char *name, const char *unit, int freq,
                                 int duration) {
  int valid = 0;

  if (strcmp(name, "Paracetamol") == 0) {
    valid = 1;
    if (strcmp(unit, "mg") != 0)
      printf("Semantic Error: 'Paracetamol' must be in 'mg'. Found: %s\n",
             unit);
    if (freq != 6 && freq != 8 && freq != 12)
      printf("Semantic Error: Invalid frequency (%d hrs) for Paracetamol.\n",
             freq);
    if (duration < 1 || duration > 5)
      printf("Semantic Warning: Unusual duration (%d days) for Paracetamol.\n",
             duration);
  } else if (strcmp(name, "Amoxicilina") == 0) {
    valid = 1;
    if (strcmp(unit, "mg") != 0)
      printf("Semantic Error: 'Amoxicilina' must be in 'mg'. Found: %s\n",
             unit);
    if (freq != 8 && freq != 12)
      printf("Semantic Error: Invalid frequency (%d hrs) for Amoxicilina.\n",
             freq);
    if (duration < 5 || duration > 10)
      printf("Semantic Warning: Unusual duration (%d days) for Amoxicilina.\n",
             duration);
  } else if (strcmp(name, "Ibuprofeno") == 0) {
    valid = 1;
    if (strcmp(unit, "mg") != 0) {
      printf("Semantic Error: 'Ibuprofeno' must be in 'mg'. Found: %s\n", unit);
    }
    if (freq != 6 && freq != 8)
      printf("Semantic Error: Invalid frequency (%d hrs) for Ibuprofeno.\n",
             freq);
    if (duration < 1 || duration > 7)
      printf("Semantic Warning: Unusual duration (%d days) for Ibuprofeno.\n",
             duration);
  } else if (strcmp(name, "Loratadina") == 0) {
    valid = 1;
    if (strcmp(unit, "mg") != 0) {
      printf("Semantic Error: 'Loratadina' must be in 'mg'. Found: %s\n", unit);
    }
    if (freq != 24)
      printf("Semantic Error: Invalid frequency (%d hrs) for Loratadina.\n",
             freq);
    if (duration < 1 || duration > 14)
      printf("Semantic Warning: Unusual duration (%d days) for Loratadina.\n",
             duration);
  }

  if (!valid) {
    printf("Semantic Error: The medication '%s' is not on the list.\n", name);
  }
}

void parse_Recipe(void) {
  match(T_LBRACE);
  match(T_K_RECETA);
  match(T_COLON);
  parse_Body_Recipe();
  match(T_RBRACE);
}

void parse_Body_Recipe(void) {
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

void parse_Date(void) {
  match(T_K_FECHA);
  match(T_COLON);
  match(T_V_DATE);
}

void parse_Pacient(void) {
  match(T_K_PACIENTE);
  match(T_COLON);
  match(T_LBRACE);
  match(T_K_NOMBRE);
  match(T_COLON);
  match(T_STRING);
  match(T_COMMA);
  match(T_K_EDAD);
  match(T_COLON);

  // SEMANTIC VALIDATION: Verify the age is a positive number
  int age = get_current_token_int();
  if (age <= 0) {
    printf(
        "Semantic Error: 'edad' (age) must be a positive number. Found: %d\n",
        age);
  }

  match(T_NUMBER);
  match(T_RBRACE);
}

void parse_Doctor(void) {
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

void parse_ID(void) { match(T_V_ID); }

void parse_Medicine(void) {
  match(T_K_MEDICAMENTOS);
  match(T_COLON);
  match(T_LBRACKET);
  parse_Prescription_List();
  match(T_RBRACKET);
}

static char current_med_unit[10];
static int current_med_freq;
static int current_med_duration;

void parse_Prescription(void) {
  match(T_LBRACE);
  match(T_K_NOMBRE);
  match(T_COLON);

  char med_name[100];
  strncpy(med_name, get_current_token_value(), sizeof(med_name));
  match(T_STRING);
  match(T_COMMA);
  parse_Dose();
  match(T_COMMA);
  parse_Frequency();
  match(T_COMMA);
  parse_Duration();
  parse_Opt_Condition();
  match(T_RBRACE);

  validate_medicine_semantics(med_name, current_med_unit, current_med_freq,
                              current_med_duration);
}

void parse_Dose(void) {
  match(T_K_DOSIS);
  match(T_COLON);
  match(T_LBRACE);
  match(T_K_CANTIDAD);
  match(T_COLON);
  match(T_NUMBER);
  match(T_COMMA);
  match(T_K_UNIDAD);
  match(T_COLON);
  strncpy(current_med_unit, get_current_token_value(),
          sizeof(current_med_unit));
  parse_Unit_Dose();
  match(T_RBRACE);
}

void parse_Unit_Dose(void) {
  if (peek(0) == T_U_MG) {
    match(T_U_MG);
  } else if (peek(0) == T_U_ML) {
    match(T_U_ML);
  } else {
    match(T_U_MG);
  }
}

void parse_Frequency(void) {
  match(T_K_FRECUENCIA);
  match(T_COLON);
  match(T_LBRACE);
  match(T_K_INTERVALO);
  match(T_COLON);
  current_med_freq = get_current_token_int();
  match(T_NUMBER);
  match(T_COMMA);
  match(T_K_UNIDAD);
  match(T_COLON);
  match(T_U_HORAS);
  match(T_RBRACE);
}

void parse_Duration(void) {
  match(T_K_DURACION);
  match(T_COLON);
  match(T_LBRACE);
  match(T_K_CANTIDAD);
  match(T_COLON);
  current_med_duration = get_current_token_int();
  match(T_NUMBER);
  match(T_COMMA);
  match(T_K_UNIDAD);
  match(T_COLON);
  match(T_U_DIAS);
  match(T_RBRACE);
}

void parse_Opt_Condition(void) {
  if (peek(0) == T_COMMA && peek(1) == T_K_CONDICION) {
    match(T_COMMA);
    match(T_K_CONDICION);
    match(T_COLON);
    match(T_STRING);
  }
}

void parse_Prescription_List(void) {
  parse_Prescription();

  if (peek(0) == T_COMMA && peek(1) == T_LBRACE) {
    match(T_COMMA);
    parse_Prescription_List();
  }
}

void parse_Opt_Indications(void) {
  if (peek(0) == T_COMMA && peek(1) == T_K_INDICACIONES) {
    match(T_COMMA);
    match(T_K_INDICACIONES);
    match(T_COLON);
    match(T_LBRACKET);
    parse_String_List();
    match(T_RBRACKET);
  }
}

void parse_String_List(void) {
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
