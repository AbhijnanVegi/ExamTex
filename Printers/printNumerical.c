#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Utils/parsers.h"
#include "../Utils/cleanText.h"

void printNumerical(FILE* qb,FILE* outputPaper, FILE* outputAnswer)
{
    char param[20];
    char value[100];
    char text[100];
    double score;
    double ans;
    while (parseArgument(qb,param,value))//Get all parameter values and store them
    {
        if (strcmp(param,"text") == 0)
        {
            clean(value);
            strcpy(text,value);
        }
        else if (strcmp(param,"score") == 0)
        {
            score = atof(value);
        }
        else if (strcmp(param,"answer") == 0)
        {
            ans = atof(value);
        }
    }
    fprintf(outputPaper,"%s",text);//Print questions to question paper
    fprintf(outputPaper,"\t[score : %0.1f]\n",score);
    fprintf(outputPaper,"Answer : ____\n");
    fprintf(outputAnswer,"%0.2f",ans);//Print answer to answer key
}