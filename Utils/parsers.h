/****************************************************
 * -----------------PARSERS-------------------------*
 * Made by Abhijnan Vegi                            *
 * Contains functions to parse the ExamTEX language *
 * *************************************************/



#ifndef __PARSERS_H_
#define __PARSERS_H_
#include <stdio.h>
#include <stdbool.h>
#include "../vector/vec.h"
typedef bool flag;

int isSyntax(char c);
int parseType(FILE *fp, char **des);
int parseArgument(FILE *fp, char **parameter, char **value);
void raiseSyntaxError(char c);
#endif