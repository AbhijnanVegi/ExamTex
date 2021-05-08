#include <stdio.h>

#include <stdlib.h>

#include <stdbool.h>

#include "mcq_SC_Val.h"
#include "../vector/vec.h"
#include "../Utils/parsers.h"
#include "../Utils/readFile.h"
#include "../Utils/cleanText.h"
#include "../Utils/lineNumber.h"

void validateSingleCorrect_MCQ(FILE *fp);
{
    // Declaring arrays to store parameters and values

    char param[20];  // Stores the value of LHS of the = sign
    char value[100]; // Stores the value of RHS of the = sign

    int parametersRead = 0;
    int numberOfParametersRequired = 5;
    // Required Parameters...
    // 1) Text
    // 2) Ans
    // 3) Difficulty
    // 4) Score
    // 5) Options

    double score;
    double difficulty;

    enum parameters
    {
        Text_Idx,
        Ans_Idx,
        Difficulty_Idx,
        Score_Idx,
        Options_Idx,
    };

    char ans[100] = {0};

    bool isParameterRead[5];
    for (int i = 0; i < 5; i++)
    {
        isParameterRead[i] = false;
    }

    int noOfOptions = 0;

    vector V;
    V = allocate(NODE, 20);
    parameterUnion newnode; // It is a temporary node to note the values

    fseek(fp, pos, SEEK_SET);

    while (parseArgument(fp, param, value)) // It is a function defined in parser.h and it returns the LHS and RHS strings on '='

    {
        if (parametersRead == 0)
        {
            newnode.nd.id = ftell(fp);
        }
        if (strcmp(param, "text") == 0)
        {
            //Do nothing as no validation is required for text
            if (isParameterRead[Text_Idx] == false)
            {
                // Read parameter
                parametersRead++;
                // Note that the parameter has been read
                isParameterRead[Text_Idx] = true;
            }
            else //Parameter already read, raise duplicate error
            {
                // Print an Error message and exit
                printf("Error on line number : %d : Duplicate parameter \"text\"", lineNumber);
                exit(1);
            }
        }
        else if (strcmp(param, "ans") == 0)
        {
            if (isParameterRead[Ans_Idx] == false)
            {
                // if (sscanf(value, "%[^\n]s", ans) != 1)
                // {
                //     printf("Error on line number : %d", lineNumber);
                // }
                // Read parameter
                parametersRead++;
                // Note that the parameter has been read
                isParameterRead[Ans_Idx] = true;
            }
            else //Parameter already read, raise duplicate error
            {
                printf("Error on line number : %d : Duplicate parameter \"ans\"", lineNumber);
                exit(1);
            }
        }
        else if (strcmp(param, "difficulty") == 0)
        {
            if (isParameterRead[Difficulty_Idx] == false)
            {
                if (sscanf(value, "%lf", &difficulty) != 1)
                {
                    printf("Error on line number : %d, Difficulty must be decimal", lineNumber);
                }
                Newnode.nd.diff = difficulty;

                // Read parameter
                parametersRead++;
                // Note that the parameter has been read
                isParameterRead[Difficulty_Idx] = true;
            }
            else //Parameter already read, raise duplicate error
            {
                printf("Error on line number %d: Duplicate parameter \"difficulty\"", lineNumber);
                exit(1);
            }
        }
        else if (strcmp(param, "score") == 0)
        {
            if (isParameterRead[Score_Idx] == false)
            {
                if (sscanf(value, "%lf", &score) != 1)
                {
                    printf("Error on line number : %d, Score must be decimal", lineNumber);
                }
                Newnode.nd.score = score;

                // Read parameter
                parametersRead++;
                // Note that the parameter has been read
                isParameterRead[Score_Idx] = true;
            }
            else //Parameter already read, raise duplicate error
            {
                printf("Error on line number : %d: Duplicate parameter \"score\"", lineNumber);
                exit(1);
            }
        }
        else if (strcmp(param, "opt") == 0)
        {
            if (isParameterRead[Options_Idx] == false)
            {
                for (int i = 0; i < strlen(value); i++)
                {
                    if (value[i] == ':')
                    {
                        ++noOfOptions;
                    }
                }
                // no. Of Options = no. Of ':' + 1
                noOfOptions = noOfOptions + 1;

                if (noOfOptions > 4)
                {
                    printf("Error! more than 4 options used in line number %d \n", line_number);
                    exit(1);
                }
                // Read parameter
                parametersRead++;
                // Note that the parameter has been read
                isParameterRead[Options_Idx] = true;
            }
            else //Parameter already read, raise duplicate error
            {
                printf("Error on line number : %d: Duplicate parameter \"opt\"", lineNumber);
                exit(1);
            }
        }
        else
        {
            printf("Unknown parameter '%s' on line number : %d", param, lineNumber);
            exit(1);
        }
    }
    if (numberOfParametersRequired != parameterRead)
    {
        printf("Parameters are Missing!\n");
        printf("Error on line number : %d: Missing parameters : ", lineNumber);

        //Print the MISSING Parameters...
        if (!isParameterRead[TEXT])
            printf("\"text\" ");
        if (!isParameterRead[ANS])
            printf("\"ans\" ");
        if (!isParameterRead[DIFFICULTY])
            printf("\"diffuculty\" ");
        if (!isParameterRead[SCORE])
            printf("\"score\" ");
        if (!isParameterRead[OPTIONS])
            printf("\"options\" ");
    }
    else
    {
        // only if all the correct set of parametres have been entered push it into vector V
        push_back(&V, newnode);
        parametersRead = 0;
    }
}