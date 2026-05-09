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

void parse_Recipe();
void parse_Body_Recipe();
void parse_Date();
void parse_Pacient();
void parse_Doctor();
void parse_ID();
void parse_Medicine();
void parse_Prescription();
void parse_Dose();
void parse_Unit_Dose();
void parse_Frequency();
void parse_Duration();
void parse_Opt_Condition();
void parse_Prescription_List();
void parse_Opt_Indications();
void parse_String_List();

#endif
