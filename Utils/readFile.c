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
#include "../Validators/truefalse.h"
#include "../Validators/validateOneWord.h"
#include "../Validators/mcq_SC_Val.h"
#include "../Bsearch_and_PrintCall/bsearch_and_print.h"

extern vector vec_mul_mcq;
extern vector vec_numerical;
extern vector vec_single_C_mcq;
extern vector vec_tf;
extern vector vec_oneword;

int lineNumber;
bool editLineNumber;

void readQuestionBank(FILE *qb)
{
    char *type;
    char *param;
    char *value;
    lineNumber = 1;
    editLineNumber = true;
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
            else if (strcmp(value, "mcq") == 0)
            {
                int id = ftell(qb);
                validateSingleCorrect_MCQ(qb, id);
                free(param);
                free(value);
                free(type);
            }
            else if (strcmp(value, "numerical") == 0)
            {
                int id = ftell(qb);
                validateNumerical(qb, id);
                free(param);
                free(value);
                free(type);
            }
            else if (strcmp(value, "truefalse") == 0)
            {
                int id = ftell(qb);
                validateTrueFalse(qb,id);
                free(param);
                free(value);
                free(type);
            }
            else if (strcmp(value, "oneword") == 0)
            {
                int id = ftell(qb);
                validateOneWord(qb, id);
                free(param);
                free(value);
                free(type);
            }
            else if (strcmp(value, "mul_mcq") == 0)
            {
                int id = ftell(qb);
                mul_mcq_validator(qb,id);
                free(param);
                free(value);
                free(type);
            }
            else
            {
                printf("Invalid type of question at line number : %d in question bank file", lineNumber);
                exit(1);
            }
        }
    }
}

void readSamplePaper(FILE* qb, FILE *sp, FILE *op, FILE *oa)
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
    int num;
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
                    else if (strcmp(value, "mcq") == 0)
                    {
                        qtype = value;
                        isParameterRead[TYPE] = true;
                        parametersRead++;
                        free(param);
                    }
                    else if (strcmp(value, "oneword") == 0)
                    {
                        qtype = value;
                        isParameterRead[TYPE] = true;
                        parametersRead++;
                        free(param);
                    }
                    else if (strcmp(value, "truefalse") == 0)
                    {
                        qtype = value;
                        isParameterRead[TYPE] = true;
                        parametersRead++;
                        free(param);
                    }
                    else if (strcmp(value, "mul_mcq") == 0)
                    {
                        qtype = value;
                        isParameterRead[TYPE] = true;
                        parametersRead++;
                        free(param);
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
            editLineNumber = false;
            if (strcmp(qtype, "numerical") == 0)
            {
                b_search(&vec_numerical,diffub,difflb,num,qtype,qb,op,oa);
            }
            else if (strcmp(qtype, "mcq") == 0)
            {
                b_search(&vec_single_C_mcq,diffub,difflb,num,qtype,qb,op,oa);
            }
            else if (strcmp(qtype, "truefalse") == 0)
            {
                b_search(&vec_tf,diffub,difflb,num,qtype,qb,op,oa);
            }
            else if (strcmp(qtype, "oneword") == 0)
            {
                b_search(&vec_oneword,diffub,difflb,num,qtype,qb,op,oa);
            }
            else if (strcmp(qtype, "mul_mcq") == 0)
            {
                b_search(&vec_mul_mcq,diffub,difflb,num,qtype,qb,op,oa);
            }
            editLineNumber = true;
        }
    }
}