// utils.h
/**
 * @file utils.h
 * @brief Common utility functions for regular expression matching.
 */

#pragma once

#ifndef UTILS_H_
#define UTILS_H_

/**
 * @brief Validates a string against a specific regex pattern.
 *
 * @details This acts as a wrapper around the thirdparty tiny-regex-c library.
 * It strictly determines if the sequence structurally matches complex tokens
 * such as standardized ID formulations and specific date formats, returning a
 * simple boolean abstraction for the lexer.
 *
 * @param string The null-terminated input string to be evaluated.
 * @param pattern The regex pattern used to validate the string structure.
 * @return Returns 1 (true) if a match is found, or 0 (false) if it is disjoint.
 */
int match_regex(const char *string, const char *pattern);

#endif // !UTILS_H_
