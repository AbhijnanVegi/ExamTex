#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Utils/parsers.h"
#include "../Utils/cleanText.h"
extern int question_number;
void printNumerical(FILE *qb, FILE *outputPaper, FILE *outputAnswer)
{
    char *param;
    char *value;
    char *text;
    double score;
    double ans;
    while (parseArgument(qb, &param, &value)) //Get all parameter values and store them
    {
        if (strcmp(param, "text") == 0)
        {
            clean(value);
            text = value;
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
            ans = atof(value);
            free(param);
            free(value);
        }
    }
    fprintf(outputPaper, "Q%d) %s", question_number, text); //Print questions to question paper
    fprintf(outputPaper, "\t[score : %0.1f]\n", score);
    fprintf(outputPaper, "Answer : ____\n\n");
    fprintf(outputAnswer, "Q%d) %0.2f", question_number, ans); //Print answer to answer key
    question_number++;
    fprintf(outputAnswer, "\n");
    free(text);
}
