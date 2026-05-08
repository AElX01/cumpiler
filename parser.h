#pragma once

#ifndef PARSER_H
#define PARSER_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"

int match(Token_Data *expected_type);
int start_parsing(void);

#endif
