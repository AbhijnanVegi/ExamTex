#include "readFile.h"
#include "lineNumber.h"
#include "parsers.h"
#include <stdio.h>
#include <stdbool.h>

int lineNumber = 0;

void readQuestionBank(FILE* qb)
{
    char c;
    flag inQuestion = false;
    while((c=fgetc(qb))!=EOF)
    {
        if (c == '<')
        {
            char type[10];//to store whether the type of block is question or sample
            parseType(qb,type);
            if (strcmp(type,"question")!=0)
            {
                printf("Invalid block on line : %d in question bank file",lineNumber);
                exit(1);
            }
            //validate arguments
            //Register question
        }
        else if (c == '\n') lineNumber++;
    }
}