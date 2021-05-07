#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Utils/parsers.h"
#include "../Utils/lineNumber.h"

void validateOneWord(FILE *fp)
{
    char param[20];
    char value[100];
    // char text[100];
    
    int numberOfParametersRequired = 4;
    int parametersRead = 0;
    // char ans[100];
    
    double difficulty;
    double score;
    
    while(parseArgument(fp,param,value))
    {
        if(strcmp(param,"text") == 0)
        {
            // Type checking not needed for question
            parametersRead++;
        }
        
        else if (strcmp(param,"ans") == 0)
        {
            // Same here, type checking not needed since it can be any type in single or group of words
            
            parametersRead++;
        }
        else if (strcmp(param,"difficulty") == 0)
        {
            // Difficulty can be in double, checking if it is the same in input
            if(sscanf(value,"%lf",&difficulty)!=1)
            {
                printf("Error on line number : %d, Difficulty must be decimal",lineNumber);
            }
            parametersRead++;
        }
        else if (strcmp(param,"score") == 0)
        {
            //  Score can be awarded only in decimals according to agreed format
            
            if(sscanf(value,"%lf",&score)!=1)
            {
                printf("Error on line number : %d, Difficulty must be decimal",lineNumber);
            }
            parametersRead++;
        }
        else
        {
            // Checking if any other paramter is found other than above specified
            printf("Unknown parameter '%s' on line number : %d",param,lineNumber);
        }
        
    }
}