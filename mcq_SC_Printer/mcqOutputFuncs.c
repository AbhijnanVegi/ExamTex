#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include "../Utils/parsers.h"
#include "../Utils/cleanText.h"

void printSingleCorrect_MCQs(FILE *qb, FILE *outputPaper, FILE *outputAnswer)
{
    double score;

    char text[100];
    char param[20];
    char value[100];
    char options[4][100];
    char correctOption[20];

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
            clean(value);
            strcpy(correctOption, value);
        }
        else if (strcmp(param, "opt") == 0)
        {
            int i = 0;
            int o = 0;
            while (value[i] != '\0')
            {
                int j = 0;
                while (value[i] != ':' && value[i] != '\0')
                {
                    options[o][j] = value[i];
                    ++j;
                    ++i;
                }
                if (value[i] == ':')
                {
                    ++i;
                    ++o;
                }
            }
        }
    }

    fprintf(outputPaper, "%s[^\n]", text);
    fprintf(outputPaper, "\t[score : %f]\n\n", score);

    for (int i = 0; i < 4; i++)
    {
        fprintf(outputPaper, " %c) %s[^\n]\n", 65 + i, options[i]);
    }
    for (int i = 0; i < 4; i++)
    {
        if (strcmp(correctOption, options[i]) == 0)
        {
            fprintf(outputAnswer, " %c) %s[^\n]\n\n", 65 + i, correctOption);
            break;
        }
    }
}