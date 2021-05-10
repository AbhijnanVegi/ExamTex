
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../vector/vec.h"
#include "../Utils/cleanText.h"
#include "../Utils/parsers.h"
#include "../Utils/lineNumber.h"
extern int question_number;
void printTF(FILE *qb, FILE *outputPaper, FILE *outputAnswer)
{
    char *param;
    char *value;
    char *text;
    double score;
    int ans;
    while (parseArgument(qb, &param, &value))
    {
        if (strcmp(param, "text") == 0)
        {
            clean(value);
            text = value;
            //strcpy(text, value);
            free(param);
        }
        else if (strcmp(param, "score") == 0)
        {
            score = atof(value);
            free(param);
            free(value);
        }
        else if (strcmp(param, "ans") == 0)
        {
            if (strcmp(value, "true") == 0)
                ans = 1;
            else
                ans = 0;
            free(param);
            free(value);
        }
    }
    fprintf(outputPaper, "Q%d) %s", question_number, text);
    fprintf(outputPaper, "\t[score : %0.1f]\n", score);

    fprintf(outputPaper, " True\n");
    fprintf(outputPaper, " False\n\n");
    if (ans)
    {
        fprintf(outputAnswer, "Q%d) TRUE\n", question_number);
    }
    else
    {
        fprintf(outputAnswer, "Q%d) FALSE\n", question_number);
    }
}

