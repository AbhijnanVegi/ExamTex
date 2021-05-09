#ifndef BSEARCH_AND_PRINTcall
#define BSEARCH_AND_PRINTcall

#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#include <stdbool.h>
#include "printNumerical.h"
////////////////need to add other print header files
#include "binary_search.h"
#include "merge_sort.h"
#include "../vector/vec.h"
#include "print_output.h"
#include "../Utils/parsers.h"
#include "../Utils/parsers.h"
#include "../Utils/cleanText.h"
#include "binary_search.h"

void select_rand_q(vector *vec, int ub, int lb, int num_q, char *type, FILE *fp);
void b_search(vector *vec, float diff_ub, float diff_lb, int num_q, char type[], FILE *fp);

#endifs