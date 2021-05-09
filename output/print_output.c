
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "vec1.h"
#include "truefalse.h"
#include "parsers.h"
#include "lineNumber.h"

void print_op(FILE *qb, FILE *outputPaper, FILE *outputAnswer)
{
    char **param;
    char **value;
    char *text;
    double score;
    double ans;
    while (parseArgument(qb, param, value))
    {
        if (strcmp(*param, "text") == 0)
        {
            clean(*value);
            text = *value;
            //strcpy(text, value);
            free(*param);
        }
        else if (strcmp(*param, "score") == 0)
        {
            score = atof(*value);
            free(*param);
            free(*value);
        }
        else if (strcmp(*param, "ans") == 0)
        {
            ans = atof(*value);
            free(*param);
            free(*value);
        }
    }
    fprintf(outputPaper, "%s", text);
    fprintf(outputPaper, "\t[score : %0.1f]\n", score);

    fprintf(outputPaper, "True\n");
    fprintf(outputPaper, "False\n");
    fprintf(outputAnswer, "%0.2f", ans);
}

void go_to_pointer(FILE *qb, int n, FILE *outputPaper, FILE *outputAnswer)
{

    ////////////Not sure but ig we need to add fopen function over here
    fseek(qb, n, SEEK_SET);
    char *type;
    char **param;
    char **value;
    int pos = 0;
    while (parseType(qb, type))
    {
        if (strcmp(*value, "truefalse") == 0)
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
