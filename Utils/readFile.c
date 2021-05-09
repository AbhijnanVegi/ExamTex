#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "readFile.h"
#include "lineNumber.h"
#include "parsers.h"
#include "../vector/vec.h"
#include "../Validators/validateNumerical.h"
#include "../Validators/mulmcqs.h"
int lineNumber;

void readQuestionBank(FILE *qb)
{
    char *type;
    char *param;
    char *value;
    lineNumber = 1;
    while (parseType(qb, &type))
    {
        if (strcmp(type, "question") != 0)
        {
            printf("Expected block of type 'question' at line number : %d in question bank file", lineNumber);
            exit(1);
        }
        else
        {
            if (!parseArgument(qb, &param, &value) || strcmp(param, "type") != 0)
            {
                printf("Expected type of question at line number : %d in question bank file", lineNumber);
                exit(1);
            }
            else if (strcmp(value, "singlecorrect") == 0)
            {
                int id = ftell(qb);
                mul_mcq_validator(qb, id);
                free(param);
                free(value);
                free(type);
            }
            else if (strcmp(value, "numerical") == 0)
            {
                int id = ftell(qb);
                validateNumerical(qb, id);
            }
            else if (strcmp(value, "") == 0)
            {
            }
            else if (strcmp(value, "") == 0)
            {
            }
            else if (strcmp(value, "") == 0)
            {
            }
            else
            {
                printf("Invalid type of question at line number : %d in question bank file", lineNumber);
                exit(1);
            }
        }
    }
}

void readSamplePaper(FILE *sp, FILE *op, FILE *oa)
{
    char *param;
    char *value;
    char *type;
    lineNumber = 1;
    enum parameters
    {
        TYPE,
        DIFFUB,
        DIFFLB,
        NUM
    };
    int numberOfParametersRequired = 4;
    int parametersRead;
    bool isParameterRead[4];

    char *qtype;
    double diffub, difflb;
    double num;
    while (parseType(sp, &type))
    {
        parametersRead = 0;
        isParameterRead[TYPE] = false;
        isParameterRead[DIFFUB] = false;
        isParameterRead[DIFFLB] = false;
        isParameterRead[NUM] = false;
        if (strcmp(type, "sample") != 0)
        {
            printf("Expected block of type 'sample' at line number : %d in sample paper file", lineNumber);
            exit(1);
        }
        else
        {
            while (parseArgument(sp, &param, &value))
            {
                if (strcmp(param, "type") == 0)
                {
                    if (strcmp(value, "numerical") == 0) //fill it with other types
                    {
                        qtype = value;
                        isParameterRead[TYPE] = true;
                        parametersRead++;
                        free(param);
                    }
                    else if (strcmp(qtype, "singlecorrect") == 0)
                    {
                    }
                    else if (strcmp(qtype, "") == 0)
                    {
                    }
                    else if (strcmp(qtype, "") == 0)
                    {
                    }
                    else if (strcmp(qtype, "") == 0)
                    {
                    }
                    else
                    {
                        printf("Error : Unknown question type at line number : %d", lineNumber);
                        free(param);
                        free(value);
                        exit(1);
                    }
                }
                else if (strcmp(param, "diffub") == 0)
                {
                    if (sscanf(value, "%lf", &diffub) != 1)
                    {
                        printf("Error on line number : %d : Upper bound on difficulty must be a float", lineNumber);
                        free(param);
                        free(value);
                    }
                    isParameterRead[DIFFUB] = true;
                    parametersRead++;
                }
                else if (strcmp(param, "difflb") == 0)
                {
                    if (sscanf(value, "%lf", &difflb) != 1)
                    {
                        printf("Error on line number : %d : Lower bound on difficulty must be a float", lineNumber);
                        free(param);
                        free(value);
                    }
                    isParameterRead[DIFFLB] = true;
                    parametersRead++;
                }
                else if (strcmp(param, "num") == 0)
                {
                    if (sscanf(value, "%d", &num) != 1)
                    {
                        printf("Error on line number : %d : number of questions must be an integer", lineNumber);
                        free(param);
                        free(value);
                    }
                    isParameterRead[NUM] = true;
                    parametersRead++;
                }
                else
                {
                    printf("Unknown parameter '%s' on line number in question paper : %d", param, lineNumber);
                    free(param);
                    free(value);
                    exit(1);
                }
            }
            if (parametersRead != numberOfParametersRequired) //Less than required parameters
            {
                printf("Error on line number : %d: Missing parameters : ", lineNumber); //print all missing parameters
                if (!isParameterRead[TYPE])
                    printf("\"type\" ");
                if (!isParameterRead[DIFFUB])
                    printf("\"diffub\" ");
                if (!isParameterRead[DIFFLB])
                    printf("\"difflb\" ");
                if (!isParameterRead[NUM])
                    printf("\"num\" ");
                free(param);
                free(value);
                exit(1);
            }
            //Deal with finding and printing questions
            //bsearch(type,difflb,diffub,num);
            if (strcmp(qtype, "numerical") == 0)
            {
                //call
            }
            else if (strcmp(qtype, "singlecorrect") == 0)
            {
            }
            else if (strcmp(qtype, "") == 0)
            {
            }
            else if (strcmp(qtype, "") == 0)
            {
            }
            else if (strcmp(qtype, "") == 0)
            {
            }
        }
    }
}