// parser.h
/**
 * @file parser.h
 * @brief Top-down recursive descent parser and semantic analyzer.
 *
 * @details
 * This module is responsible for verifying that the stream of tokens conforms
 * to the structural rules of the language grammar. It implements a top-down,
 * recursive descent parsing strategy.
 *
 * Grammar Rules Supported:
 * - parse_Recipe -> T_LBRACE T_K_RECETA T_COLON parse_Body_Recipe T_RBRACE
 * - parse_Body_Recipe -> T_LBRACE parse_Date T_COMMA parse_Pacient T_COMMA
 * parse_Doctor T_COMMA parse_Medicine parse_Opt_Indications T_RBRACE
 * - parse_Date -> T_K_FECHA T_COLON T_V_DATE
 * - parse_Pacient -> T_K_PACIENTE T_COLON T_LBRACE T_K_NOMBRE T_COLON T_STRING
 * T_COMMA T_K_EDAD T_COLON T_NUMBER T_RBRACE
 * - parse_Doctor -> T_K_MEDICO T_COLON T_LBRACE T_K_NOMBRE T_COLON T_STRING T_COMMA
 * T_K_CEDULA T_COLON parse_ID T_RBRACE
 * - parse_ID -> T_V_ID
 * - parse_Medicine -> T_K_MEDICAMENTOS T_COLON T_LBRACKET parse_Prescription_List T_RBRACKET
 * - parse_Prescription_List -> parse_Prescription | parse_Prescription T_COMMA parse_Prescription_List
 * - parse_Prescription -> T_LBRACE T_K_NOMBRE T_COLON T_STRING T_COMMA parse_Dose
 * T_COMMA parse_Frequency T_COMMA parse_Duration parse_Opt_Condition T_RBRACE
 * - parse_Dose -> T_K_DOSIS T_COLON T_LBRACE T_K_CANTIDAD T_COLON T_NUMBER T_COMMA
 * T_K_UNIDAD T_COLON parse_Unit_Dose T_RBRACE
 * - parse_Unit_Dose -> T_U_MG | T_U_ML
 * - parse_Frequency -> T_K_FRECUENCIA T_COLON T_LBRACE T_K_INTERVALO T_COLON
 * T_NUMBER T_COMMA T_K_UNIDAD T_COLON T_U_HORAS T_RBRACE
 * - parse_Duration -> T_K_DURACION T_COLON T_LBRACE T_K_CANTIDAD T_COLON T_NUMBER
 * T_COMMA T_K_UNIDAD T_COLON T_U_DIAS T_RBRACE
 * - parse_Opt_Condition -> T_COMMA T_K_CONDICION T_COLON T_STRING | ε
 * - parse_Opt_Indications -> T_COMMA T_K_INDICACIONES T_COLON T_LBRACKET parse_String_List T_RBRACKET | ε
 * - parse_String_List -> T_STRING | T_STRING T_COMMA parse_String_List
 */

#pragma once

#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include <stddef.h>

/**
 * @brief Advances the PDA read-head if the expected terminal symbol matches the current token.
 * @details Emits a precise syntax error to standard output if the structural expectation fails.
 *
 * @param expected_type The expected terminal symbol enum.
 */
void match(Token expected_type);

/**
 * @brief Initializes and kicks off the parsing process starting from the root non-terminal.
 *
 * @return Returns 0 upon a successfully parsed ast/evaluation tree.
 */
int start_parsing(void);

/**
 * @brief Evaluates the root 'Recipe' non-terminal.
 */
void parse_Recipe(void);

/**
 * @brief Evaluates the internal structure 'Body_Recipe' containing prescription metadata.
 */
void parse_Body_Recipe(void);

/**
 * @brief Evaluates the 'Date' block, enforcing specific Regex-verified token expectations.
 */
void parse_Date(void);

/**
 * @brief Evaluates the 'Pacient' object containing identifying string and age attributes.
 */
void parse_Pacient(void);

/**
 * @brief Evaluates the 'Doctor' object structural layout.
 */
void parse_Doctor(void);

/**
 * @brief Validates the presence of the identity identifier (ID).
 */
void parse_ID(void);

/**
 * @brief Evaluates the container for the medication listings.
 */
void parse_Medicine(void);

/**
 * @brief Evaluates a single, distinct 'Prescription' rule, triggering semantic validation logic.
 */
void parse_Prescription(void);

/**
 * @brief Evaluates the required dosage sub-component for a given medication.
 */
void parse_Dose(void);

/**
 * @brief Determines if the prescribed unit adheres to valid mg or ml tokens.
 */
void parse_Unit_Dose(void);

/**
 * @brief Evaluates the frequency of intake sub-structure.
 */
void parse_Frequency(void);

/**
 * @brief Evaluates the strict duration limit attributes of a prescription.
 */
void parse_Duration(void);

/**
 * @brief Evaluates an optional condition sub-string (epsilon production fallback).
 */
void parse_Opt_Condition(void);

/**
 * @brief Recursively maps contiguous prescription blocks until sequence termination.
 */
void parse_Prescription_List(void);

/**
 * @brief Evaluates optional external indications array (epsilon production fallback).
 */
void parse_Opt_Indications(void);

/**
 * @brief Recursively processes a sequence of standard string values within list boundaries.
 */
void parse_String_List(void);

#endif
