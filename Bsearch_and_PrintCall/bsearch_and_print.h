#ifndef __BSEARCH_AND_PRINTCALL_H_
#define __BSEARCH_AND_PRINTcall_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "../vector/vec.h"


void select_rand_q(vector *vec, int ub, int lb, int num_q, char *type, FILE *fp, FILE* op, FILE* oa);
void b_search(vector *vec, float diff_ub, float diff_lb, int num_q, char type[], FILE *fp, FILE* op,FILE* oa);

#endif