#pragma once

#ifndef PARSER_H
#define PARSER_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"

void match(Token expected_type);
int start_parsing(void);

void parse_Recipe(void);
void parse_Body_Recipe(void);
void parse_Date(void);
void parse_Pacient(void);
void parse_Doctor(void);
void parse_ID(void);
void parse_Medicine(void);
void parse_Prescription(void);
void parse_Dose(void);
void parse_Unit_Dose(void);
void parse_Frequency(void);
void parse_Duration(void);
void parse_Opt_Condition(void);
void parse_Prescription_List(void);
void parse_Opt_Indications(void);
void parse_String_List(void);

#endif
