/*****************************************************
 * This file is incomplete and is only here to give  *
 * idea of how the parsers should be used            *
 * ***************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../Utils/parsers.h"
#include "../Utils/lineNumber.h"

void validateNumerical(FILE *fp)
{
    char param[20];
    char value[100];
    int numberOfParametersRequired = 4;
    int parametersRead = 0;
    enum parameters
    {
        TEXT,
        ANS,
        DIFFICULTY,
        SCORE
    };
    bool isParameterRead[4];
    isParameterRead[TEXT] = false;
    isParameterRead[ANS] = false;
    isParameterRead[DIFFICULTY] = false;
    isParameterRead[SCORE] = false;
    double ans;
    double difficulty;
    double score;
    while (parseArgument(fp, param, value))
    {
        if (strcmp(param, "text") == 0)
        {
            //Do nothing as no validation is required for text
            //Save in vector
            if (!isParameterRead[TEXT])
            {
                isParameterRead[TEXT] = true;
                parametersRead++;
            }
            else
            {
                printf("Error on line number : %d : Duplicate parameter \"text\"", lineNumber);
                exit(1);
            }
        }
        else if (strcmp(param, "ans") == 0)
        {
            if (!isParameterRead[ANS])
            {
                if (sscanf(value, "%lf", &ans) != 1)
                {
                    printf("Error on line number %d: Answer must be decimal", lineNumber);
                    exit(1);
                }
                isParameterRead[ANS] = true;
                parametersRead++;
            }
            else
            {
                printf("Error on line number : %d : Duplicate parameter \"ans\"", lineNumber);
                exit(1);
            }
        }
        else if (strcmp(param, "difficulty") == 0)
        {
            if (!isParameterRead[DIFFICULTY])
            {
                if (sscanf(value, "%lf", &difficulty) != 1)
                {
                    printf("Error on line number : %d : Difficulty must be decimal", lineNumber);
                    exit(1);
                }
                isParameterRead[DIFFICULTY] = true;
                parametersRead++;
            }
            else
            {
                printf("Error on line number %d: Duplicate parameter \"difficulty\"", lineNumber);
                exit(1);
            }
        }
        else if (strcmp(param, "score") == 0)
        {
            if (!isParameterRead[SCORE])
            {
                if (sscanf(value, "%lf", &score) != 1)
                {
                    printf("Error on line number : %d, Score must be decimal", lineNumber);
                    exit(1);
                }
                parametersRead++;
            }
            else
            {
                printf("Error on line number : %d: Duplicate parameter \"score\"",lineNumber);
                exit(1);
            }
        }
        else
        {
            printf("Unknown parameter '%s' on line number : %d", param, lineNumber);
            exit(1);
        }
    }
    if (parametersRead!=numberOfParametersRequired)
    {
        printf("Error on line number : %d: Missing parameters : ",lineNumber);
        if (!isParameterRead[TEXT])printf("\"text\" ");
        if (!isParameterRead[ANS])printf("\"ans\" ");
        if (!isParameterRead[DIFFICULTY])printf("\"diffuculty\" ");
        if (!isParameterRead[SCORE])printf("\"score\" ");
    }
    //save the question here
}