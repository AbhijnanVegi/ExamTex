#ifndef TrueFalse
#define TrueFlase

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "vec1.h"

int check_if_complete(bool flag[4]);
void validateTrueFalse(FILE *fp);
void go_to_pointer(FILE* fp, int n, FILE* outputPaper , FILE* outputAnswer);
void printTF(vector* v);

#endif
