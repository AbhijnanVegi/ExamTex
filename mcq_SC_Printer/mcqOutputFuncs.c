#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include "../Utils/parsers.h"
#include "../Utils/cleanText.h"

void printSingleCorrect_MCQs(FILE *qb, FILE *outputPaper, FILE *outputAnswer)
{
    double score;

    char *param; // will store different parameters one vby one i.e. LHS of =
    char *value; // will store the valus of different parameters i.e. RHS of =

    char text[100];          // will store the question text
    char options[4][1000];   // will store 4 different options of the question...
    char correctOption[100]; // will store the corrcet option for a particular question...

    char *p;
    parseType(qb, &p);

    int n = 6;
    while (n--)
    {
        parseArgument(qb, &param, &value);
        if (strcmp(param, "text") == 0)
        {
            clean(value);
            // Copy the text of the question to text array
            strcpy(text, value);
        }
        else if (strcmp(param, "score") == 0)
        {
            // store the max score(double)
            score = atof(value);
        }
        else if (strcmp(param, "ans") == 0)
        {
            clean(value);
            // Store the correctOption in the correctOption array
            strcpy(correctOption, value);
        }
        else if (strcmp(param, "opt") == 0)
        {
            // Firstly separe the different options present int the char value[] array
            // and then 1 by 1 store them in 4 different char arrays...
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
                    options[o][j] = '\0';
                    ++i;
                    ++o;
                }
                if (value[i] == '\0')
                {
                    options[o][j] = value[i];
                }
            }
        }
    }

    // Print the Question text in the output File...
    fprintf(outputPaper, "Q)\t%s\n", text);
    // Print the Max Score for that Question after the text in the output File...
    fprintf(outputPaper, "\t[score : %f]\n\n", score);

    for (int i = 0; i < 4; i++)
    {
        // Print the 4 different options stored in diff arrays 1 by 1 ...
        // Also print the option nos. e.g. A)... B)... C)... D)...
        fprintf(outputPaper, " %c) %s \n", 65 + i, options[i]);
    }
    for (int i = 0; i < 4; i++)
    {
        // Compare each option with the correctAnswer Option...
        if (strcmp(correctOption, options[i]) == 0)
        {
            // If a particular Option is correct print it on tghe Output Answer file...
            // along with the option number
            // And if no option is matching donot print anything...
            fprintf(outputAnswer, " %c) %s\n\n", 65 + i, correctOption);
            break;
        }
    }
}