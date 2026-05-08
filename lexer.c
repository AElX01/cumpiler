#include "lexer.h"
#include <stdio.h>

//  allocator
extern void *mem_alloc(size_t size);

Tokens_Array *TOKENS = NULL;

void Tokens_Array_append(Token_Data *data) {
  if (data == NULL)
    return;

  if (TOKENS == NULL) {
    TOKENS = mem_alloc(sizeof(Tokens_Array));
    TOKENS->items = NULL;
    TOKENS->size = 0;
    TOKENS->capacity = 0;
  }

  if (TOKENS->items == NULL) {
    TOKENS->capacity = 256;
    TOKENS->size = 0;
    TOKENS->items = mem_alloc(TOKENS->capacity * sizeof(Token_Data));

  } else if (TOKENS->size >= TOKENS->capacity) {

    TOKENS->capacity <<= 1;

    Token_Data *temp =
        realloc(TOKENS->items, TOKENS->capacity * sizeof(Token_Data));

    if (temp == NULL) {
      perror("realloc failed");
      exit(EXIT_FAILURE);
    }

    TOKENS->items = temp;
  }

  TOKENS->items[TOKENS->size] = *data;
  TOKENS->size++;
}

const char *token_to_string(Token token) {
  switch (token) {
  case T_LBRACE:
    return "T_LBRACE";
  case T_RBRACE:
    return "T_RBRACE";
  case T_LBRACKET:
    return "T_LBRACKET";
  case T_RBRACKET:
    return "T_RBRACKET";
  case T_COLON:
    return "T_COLON";
  case T_COMMA:
    return "T_COMMA";
  case T_STRING:
    return "T_STRING";
  case T_NUMBER:
    return "T_NUMBER";
  case T_K_RECETA:
    return "T_K_RECETA";
  case T_K_FECHA:
    return "T_K_FECHA";
  case T_K_PACIENTE:
    return "T_K_PACIENTE";
  case T_K_MEDICO:
    return "T_K_MEDICO";
  case T_K_NOMBRE:
    return "T_K_NOMBRE";
  case T_K_EDAD:
    return "T_K_EDAD";
  case T_K_CEDULA:
    return "T_K_CEDULA";
  case T_K_MEDICAMENTOS:
    return "T_K_MEDICAMENTOS";
  case T_K_DOSIS:
    return "T_K_DOSIS";
  case T_K_FRECUENCIA:
    return "T_K_FRECUENCIA";
  case T_K_DURACION:
    return "T_K_DURACION";
  case T_K_CANTIDAD:
    return "T_K_CANTIDAD";
  case T_K_UNIDAD:
    return "T_K_UNIDAD";
  case T_K_INTERVALO:
    return "T_K_INTERVALO";
  case T_K_CONDICION:
    return "T_K_CONDICION";
  case T_K_INDICACIONES:
    return "T_K_INDICACIONES";
  case T_U_MG:
    return "T_U_MG";
  case T_U_ML:
    return "T_U_ML";
  case T_U_HORAS:
    return "T_U_HORAS";
  case T_U_DIAS:
    return "T_U_DIAS";
  case T_EOF:
    return "T_EOF";
  case T_ERROR:
    return "T_ERROR";
  default:
    return "UNKNOWN_TOKEN";
  }
}

void Tokens_Array_printf(void) {
  if (TOKENS == NULL)
    return;

  for (size_t i = 0; i < TOKENS->size; ++i) {
    printf("Token: %s\n"
           "Value: %s\n"
           "Line: %d\n\n",
           token_to_string(TOKENS->items[i].type), TOKENS->items[i].value,
           TOKENS->items[i].line);
  }
}

Tokens_Array *tokenize(char *data) {

  int current_line = 0;

  while (*data != '\0') {

    if (*data == '\n')
      current_line++;

    // {
    if (*data == '{') {

      char *value = mem_alloc(2);
      value[0] = '{';
      value[1] = '\0';

      Token_Data token = {
          .type = T_LBRACE,
          .value = value,
          .line = current_line,
      };

      Tokens_Array_append(&token);
      data++;
      continue;
    }

    // }
    if (*data == '}') {

      char *value = mem_alloc(2);
      value[0] = '}';
      value[1] = '\0';

      Token_Data token = {
          .type = T_RBRACE,
          .value = value,
          .line = current_line,
      };

      Tokens_Array_append(&token);
      data++;
      continue;
    }

    // [
    if (*data == '[') {

      char *value = mem_alloc(2);
      value[0] = '[';
      value[1] = '\0';

      Token_Data token = {
          .type = T_LBRACKET,
          .value = value,
          .line = current_line,
      };

      Tokens_Array_append(&token);
      data++;
      continue;
    }

    // ]
    if (*data == ']') {

      char *value = mem_alloc(2);
      value[0] = ']';
      value[1] = '\0';

      Token_Data token = {
          .type = T_RBRACKET,
          .value = value,
          .line = current_line,
      };

      Tokens_Array_append(&token);
      data++;
      continue;
    }

    // :
    if (*data == ':') {

      char *value = mem_alloc(2);
      value[0] = ':';
      value[1] = '\0';

      Token_Data token = {
          .type = T_COLON,
          .value = value,
          .line = current_line,
      };

      Tokens_Array_append(&token);
      data++;
      continue;
    }

    // ,
    if (*data == ',') {

      char *value = mem_alloc(2);
      value[0] = ',';
      value[1] = '\0';

      Token_Data token = {
          .type = T_COMMA,
          .value = value,
          .line = current_line,
      };

      Tokens_Array_append(&token);
      data++;
      continue;
    }

    // NUMBER
    if (isdigit(*data)) {

      char *start = data;
      size_t len = 0;

      while (isdigit(*data) || *data == '.') {
        data++;
        len++;
      }

      char *value = mem_alloc(len + 1);

      strncpy(value, start, len);
      value[len] = '\0';

      Token_Data token = {
          .type = T_NUMBER,
          .value = value,
          .line = current_line,
      };

      Tokens_Array_append(&token);

      continue;
    }

    // STRING
    if (*data == '"') {

      data++;

      char *start = data;
      size_t len = 0;

      while (*data != '"' && *data != '\0') {
        data++;
        len++;
      }

      char *value = mem_alloc(len + 1);

      strncpy(value, start, len);
      value[len] = '\0';

      printf("============================\n\n");

      printf("string: %s \nlen: %zu \n\n", value, len);

      printf("============================\n\n");

      Token type = T_STRING;

      // KEYWORD PROMOTION
      if (strcmp(value, "receta") == 0)
        type = T_K_RECETA;
      else if (strcmp(value, "fecha") == 0)
        type = T_K_FECHA;
      else if (strcmp(value, "paciente") == 0)
        type = T_K_PACIENTE;
      else if (strcmp(value, "medico") == 0)
        type = T_K_MEDICO;
      else if (strcmp(value, "nombre") == 0)
        type = T_K_NOMBRE;
      else if (strcmp(value, "edad") == 0)
        type = T_K_EDAD;
      else if (strcmp(value, "cedula") == 0)
        type = T_K_CEDULA;
      else if (strcmp(value, "medicamentos") == 0)
        type = T_K_MEDICAMENTOS;
      else if (strcmp(value, "dosis") == 0)
        type = T_K_DOSIS;
      else if (strcmp(value, "frecuencia") == 0)
        type = T_K_FRECUENCIA;
      else if (strcmp(value, "duracion") == 0)
        type = T_K_DURACION;
      else if (strcmp(value, "cantidad") == 0)
        type = T_K_CANTIDAD;
      else if (strcmp(value, "unidad") == 0)
        type = T_K_UNIDAD;
      else if (strcmp(value, "intervalo") == 0)
        type = T_K_INTERVALO;
      else if (strcmp(value, "condicion") == 0)
        type = T_K_CONDICION;
      else if (strcmp(value, "indicaciones") == 0)
        type = T_K_INDICACIONES;

      // UNITS
      else if (strcmp(value, "mg") == 0)
        type = T_U_MG;
      else if (strcmp(value, "ml") == 0)
        type = T_U_ML;
      else if (strcmp(value, "horas") == 0)
        type = T_U_HORAS;
      else if (strcmp(value, "dias") == 0)
        type = T_U_DIAS;

      // SPECIAL
      else
        type = T_ERROR;

      Token_Data token = {
          .type = type,
          .value = value,
          .line = current_line,
      };

      Tokens_Array_append(&token);

      data++;
      continue;
    }

    data++;
  }

  return TOKENS;
}
