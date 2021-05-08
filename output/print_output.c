
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "vec1.h"
#include "truefalse.h"
#include "parsers.h"
#include "lineNumber.h"

void print_op(FILE *qb, FILE *outputPaper, FILE *outputAnswer)
{
    char param[20];
    char value[100];
    char text[100];
    double score;
    double ans;
    while (parseArgument(qb, param, value))
    {
        if (strcmp(param, "text") == 0)
        {
            clean(value);
            strcpy(text, value);
        }
        else if (strcmp(param, "score") == 0)
        {
            score = atof(value);
        }
        else if (strcmp(param, "ans") == 0)
        {
            ans = atof(value);
        }
    }
    fprintf(outputPaper, "%s", text);
    fprintf(outputPaper, "\t[score : %f]\n", score);

    fprintf(outputPaper, "True\n");
    fprintf(outputPaper, "False\n");
    fprintf(outputAnswer, "%f", ans);
}

void go_to_pointer(FILE *qb, int n, FILE *outputPaper, FILE *outputAnswer)
{
    fseek(qb, n, SEEK_SET);
    char type[10];
    char param[20];
    char value[100];
    int pos = 0;
    while (parseType(qb, type))
    {
        if (strcmp(value, "truefalse") == 0)
        {
            print_op(qb, outputPaper, outputAnswer);
        }
    }
}

void printTF(vector *v)
{
    FILE *TF_qb;
    FILE *outputPaper;
    FILE *outputAnswer;
    int n = 0;
    for (int i = 0; i < v->last; i++)
    {
        n = v->u.nodeElems[i].id;
        go_to_pointer(TF_qb, n, outputPaper, outputAnswer);
    }
}
