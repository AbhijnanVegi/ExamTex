#ifndef __READ_FILE_H_
#define __READ_FILE_H_
#include <stdio.h>
#include <stdbool.h>

typedef bool flag;

void readQuestionBank(FILE* qb);
void readSamplePaper(FILE*qb, FILE *sp, FILE * op, FILE* oa);

#endif