#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../Utils/parsers.h"
#include "../Utils/lineNumber.h"
#include "../vector/vec.h"

extern vector vec_numerical;

void validateNumerical(FILE *fp, int id)
{
    char *param;//To store pointer to char array
    char *value;
    int numberOfParametersRequired = 4;
    int parametersRead = 0;//Number of parameters read
    parameterUnion u;
    enum parameters
    {
        TEXT,
        ANS,
        DIFFICULTY,
        SCORE
    };
    bool isParameterRead[4];//Array to store if aprticular parameter has been read
    isParameterRead[TEXT] = false;
    isParameterRead[ANS] = false;
    isParameterRead[DIFFICULTY] = false;
    isParameterRead[SCORE] = false;
    double ans;//floats to store ans, diff, score
    double difficulty;
    double score;
    while (parseArgument(fp, &param, &value))
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
            else//Parameter already read, raise duplicate error
            {
                printf("Error on line number : %d : Duplicate parameter \"text\"", lineNumber);
                free(param);
                free(value);
                exit(1);
            }
            free(param);
            free(value);
        }
        else if (strcmp(param, "ans") == 0)
        {
            if (!isParameterRead[ANS])
            {
                if (sscanf(value, "%lf", &ans) != 1)
                {
                    printf("Error on line number %d: Answer must be decimal", lineNumber);
                    free(param);
                    free(value);
                    exit(1);
                }
                isParameterRead[ANS] = true;
                parametersRead++;
            }
            else
            {
                printf("Error on line number : %d : Duplicate parameter \"ans\"", lineNumber);
                free(param);
                free(value);
                exit(1);
            }
            free(param);
            free(value);
        }
        else if (strcmp(param, "difficulty") == 0)
        {
            if (!isParameterRead[DIFFICULTY])
            {
                if (sscanf(value, "%lf", &difficulty) != 1)
                {
                    printf("Error on line number : %d : Difficulty must be decimal", lineNumber);
                    free(param);
                    free(value);
                    exit(1);
                }
                isParameterRead[DIFFICULTY] = true;
                parametersRead++;
            }
            else
            {
                printf("Error on line number %d: Duplicate parameter \"difficulty\"", lineNumber);
                free(param);
                free(value);
                exit(1);
            }
            free(param);
            free(value);
        }
        else if (strcmp(param, "score") == 0)
        {
            if (!isParameterRead[SCORE])
            {
                if (sscanf(value, "%lf", &score) != 1)
                {
                    printf("Error on line number : %d, Score must be decimal", lineNumber);
                    free(param);
                    free(value);
                    exit(1);
                }
                isParameterRead[SCORE] = 1;
                parametersRead++;
            }
            else
            {
                printf("Error on line number : %d: Duplicate parameter \"score\"",lineNumber);
                free(param);
                free(value);
                exit(1);
            }
            free(param);
            free(value);
        }
        else
        {
            printf("Unknown parameter '%s' on line number : %d", param, lineNumber);
            free(param);
            free(value);
            exit(1);
        }
    }
    if (parametersRead!=numberOfParametersRequired) //Less than required parameters
    {
        printf("Error on line number : %d: Missing parameters : ",lineNumber);//print all missing parameters
        if (!isParameterRead[TEXT])printf("\"text\" ");
        if (!isParameterRead[ANS])printf("\"ans\" ");
        if (!isParameterRead[DIFFICULTY])printf("\"diffuculty\" ");
        if (!isParameterRead[SCORE])printf("\"score\" ");
        free(param);
        free(value);
        exit(1);
    }
    //save the question here
    u.nd.id = id;
    u.nd.diff = difficulty;
    u.nd.score = score;
    push_back(&vec_numerical,u);
}
