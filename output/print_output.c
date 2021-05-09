
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


