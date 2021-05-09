#include <stdio.h>

#include <stdlib.h>

#include <stdbool.h>

#include "../Utils/parsers.h"

#include "../Utils/lineNumber.h"

void validateOneWord(FILE *fp, int id)
{
    char *param;
    char *value;
        
    int numberOfParametersRequired = 4;
    int parametersRead = 0;
    // Parameters Needed
    //      =>text
    //      =>ans
    //      =>difficulty
    //      =>score
    bool isParameterRead[4]; // Array to store the presence of parameters

    enum parameters
    {
        TEXT,
        ANS,
        DIFFICULTY,
        SCORE
    };

    int z = 4;
    while(z--){
        isParameterRead[z] = false;
    }

    double difficulty;
    double score;
    
    while(parseArgument(fp,&param,&value))
    {
        if(strcmp(param,"text") == 0)
        {
            // Type checking not needed for question
            if(!isParameterRead[TEXT])
            {
                isParameterRead[TEXT] = true;
                parametersRead++;
            }
            // Since parameter already read, raising duplicate error
            else{
                printf("Error on line number : %d : Duplicate parameter \"text\"", lineNumber);
                free(param);
                free(value);
                exit(1);                
            }
            free(param);
            free(value);
        }
        else if (strcmp(param,"ans") == 0)
        {
            // Same here, type checking not needed since it can be any type in single or group of words
            if(!isParameterRead[ANS])
            {
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
        }
        else if (strcmp(param,"difficulty") == 0)
        {
            // Difficulty can be in double, checking if it is the same in input
            if(!isParameterRead[DIFFICULTY])
            {
                if(sscanf(value,"%lf",&difficulty)!=1)
                {
                    printf("Error on line number : %d, Difficulty must be decimal",lineNumber);
                    free(param);
                    free(value);
                    exit(1);
                }
                isParameterRead[DIFFICULTY] = true;
                parametersRead++;
            }
            else{
                printf("Error on line number %d: Duplicate parameter \"difficulty\"", lineNumber);
                free(param);
                free(value);
                exit(1);
            }
            free(param);
            free(value);
            
        }
        else if (strcmp(param,"score") == 0)
        {
            //  Score can be awarded only in decimals according to agreed format
            if(!isParameterRead[SCORE])
            {
                if(sscanf(value,"%lf",&score)!=1)
                {
                    printf("Error on line number : %d, Difficulty must be decimal",lineNumber);
                    free(param);
                    free(value);
                    exit(1);
                }
                isParameterRead[SCORE] = true;
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
            // Checking if any other paramter is found other than above specified
            printf("Unknown parameter '%s' on line number : %d",param,lineNumber);
            free(param);
            free(value);
            exit(1);
        }
    }
    if(parametersRead!=numberOfParametersRequired)
    {
        printf("Error on line number : %d: Missing parameters : ",lineNumber);//print all missing parameters
        if (!isParameterRead[TEXT])
            printf("\"text\" ");
        if (!isParameterRead[ANS])
            printf("\"ans\" ");
        if (!isParameterRead[DIFFICULTY])
            printf("\"diffuculty\" ");
        if (!isParameterRead[SCORE])
            printf("\"score\" ");
        free(param);
        free(value);
        exit(1);
    }
}