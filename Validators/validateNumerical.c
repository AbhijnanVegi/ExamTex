/*****************************************************
 * This file is incomplete and is only here to give  *
 * idea of how the parsers should be used            *
 * ***************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "../Utils/parsers.h"
#include "../Utils/lineNumber.h"

void validateNumerical(FILE *fp)
{
    char param[20];
    char value[100];
    int numberOfParametersRequired = 4;
    int parametersRead = 0;
    double ans;
    double difficulty;
    double score;
    while(parseArgument(fp,param,value))
    {
        if(strcmp(param,"text") == 0)
        {
            //Do nothing as no validation is required for text
            //Save in vector
            parametersRead++;
        }
        else if (strcmp(param,"ans") == 0)
        {
            if(sscanf(value,"%lf",&ans)!=1)
            {
                printf("Error on line number : %d, Answer must be decimal",lineNumber);
            }
            parametersRead++;
        }
        else if (strcmp(param,"difficulty") == 0)
        {
            if(sscanf(value,"%lf",&difficulty)!=1)
            {
                printf("Error on line number : %d, Difficulty must be decimal",lineNumber);
            }
            parametersRead++;
        }
        else if (strcmp(param,"score") == 0)
        { 
            if(sscanf(value,"%lf",&score)!=1)
            {
                printf("Error on line number : %d, Difficulty must be decimal",lineNumber);
            }
            parametersRead++;
        }
        else
        {
            printf("Unknown parameter '%s' on line number : %d",param,lineNumber);
        }
    }
    //save the question here
}