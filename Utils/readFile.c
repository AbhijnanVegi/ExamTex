#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "readFile.h"
#include "lineNumber.h"
#include "parsers.h"

int lineNumber = 0;

void readQuestionBank(FILE* qb)
{
    char type[10];
    char param[20];
    char value[100];
    while(parseType(qb,type))
    {
        if(strcmp(type,"question") != 0)
        {
            printf("Expected block of type 'question' at line number : %d in question bank file",lineNumber);
            exit(1);
        }
        else
        {
            if(!parseArgument(qb,param,value) || strcmp(param,"type")!=0)
            {
                printf("Expected type of question at line number : %d in question bank file",lineNumber);
                exit(1);
            }
            else if (strcmp(value,"numerical") == 0)
            {
                //call function
            }
            else
            {
                printf("Invalid type of question at line number : %d in question bank file",lineNumber);
                exit(1);
            }
        }
    }
}