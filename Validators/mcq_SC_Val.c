#include <stdlib.h>

#include <string.h>

#include "mcq_SC_Val.h"
#include "../vector/vec.h"
#include "../Utils/parsers.h"
#include "../Utils/readFile.h"
#include "../Utils/cleanText.h"
#include "../Utils/lineNumber.h"

extern vector vec_single_C_mcq;
// vector vec_single_C_mcq;

void validateSingleCorrect_MCQ(FILE *fp, int id)
{
    // Declaring arrays to store parameters and values

    char *param; // Stores the value of LHS of the = sign
    char *value; // Stores the value of RHS of the = sign

    int parametersRead = 0;
    // int numberOfParametersRequired = 5;
    // Required Parameters...
    // 1) Text
    // 2) Ans
    // 3) Difficulty
    // 4) Score
    // 5) Options

    double score;
    double difficulty;

    char *anss, **opts;
    //anss = (char **)malloc(sizeof(char *) * 8);
    opts = (char **)malloc(sizeof(char *) * 9);

    char text_flag = 0, diff_flag = 0, score_flag = 0, opt_flag = 0, ans_flag = 0;

    int noOfOptions = 0, noOfAnswers = 0;

    parameterUnion newnode; // It is a temporary node to note the values
    newnode.nd.id = id;

    while (parseArgument(fp, &param, &value)) // It is a function defined in parser.h and it returns the LHS and RHS strings on '='
    {
        if (strcmp(param, "text") == 0)
        {
            //Do nothing as no validation is required for text
            if (!text_flag)
            {
                // Note that the parameter has been read
                text_flag = 1;
            }
            else //Parameter already read, raise duplicate error
            {
                // Print an Error message and exit
                printf("Error on line number : %d : Duplicate parameter \"text\"", lineNumber);
                exit(1);
            }
        }
        else if (strcmp(param, "difficulty") == 0)
        {
            if (!diff_flag)
            {
                if (sscanf(value, "%lf", &difficulty) != 1)
                {
                    printf("Error on line number : %d, Difficulty must be decimal", lineNumber);
                    exit(1);
                }
                // // Note that the parameter has been read
                diff_flag = 1;

                // // Read parameter
                // parametersRead++;
                // // Note that the parameter has been read
                // isParameterRead[Difficulty_Idx] = true;
            }
            else //Parameter already read, raise duplicate error
            {
                printf("Error on line number %d: Duplicate parameter \"difficulty\"", lineNumber);
                exit(1);
            }
        }
        else if (strcmp(param, "ans") == 0)
        {
            if (!ans_flag)
            {
                ans_flag = 1;
                anss = (char *)malloc(strlen(value) + 1);
                strcpy(anss, value);
                remove_spaces(&anss);
            }
            else //Parameter already read, raise duplicate error
            {
                printf("Error on line number : %d : Duplicate parameter \"ans\"", lineNumber);
                exit(1);
            }
        }

        else if (strcmp(param, "score") == 0)
        {
            if (!score_flag)
            {
                if (sscanf(value, "%lf", &score) != 1)
                {
                    printf("Error on line number : %d, Score must be decimal", lineNumber);
                    exit(1);
                }

                // Read parameter
                // parametersRead++;
                // Note that the parameter has been read
                score_flag = 1;
            }
            else //Parameter already read, raise duplicate error
            {
                printf("Error on line number : %d: Duplicate parameter \"score\"", lineNumber);
                exit(1);
            }
        }
        else if (strcmp(param, "opt") == 0)
        {
            if (!opt_flag)
            {
                int o = 0;
                int j = 0;
                opts[o] = (char *)malloc(sizeof(char) * strlen(value) + 1);
                for (int i = 0; i < strlen(value); i++)
                {
                    if (value[i] != ':')
                    {
                        opts[o][j] = value[i];
                        j++;
                    }
                    if (value[i] == ':')
                    {
                        opts[o][j] = '\0';
                        remove_spaces(&opts[o]);
                        o++;
                        if (o == 8)
                        {
                            printf("Error! More than 8 options initialised in line number : %d\n", lineNumber);
                            exit(1);
                        }
                        opts[o] = (char *)malloc(sizeof(char) * strlen(value) + 1);
                        j = 0;
                    }
                }
                // Read parameter
                // parametersRead++;
                // Note that the parameter has been read
                opt_flag = 1;

                opts[o][j] = '\0';
                remove_spaces(&opts[o]);
                noOfOptions = o + 1;
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
    //Print the MISSING Parameters...

    if (!opt_flag)
    {
        printf("Error! Not initialised options in line no : %d\n", lineNumber);
        exit(1);
    }
    if (!ans_flag)
    {
        printf("Error! Not initialised answer in line no : %d\n", lineNumber);
        exit(1);
    }
    if (!text_flag)
    {
        printf("Error! Not initialised question in line no : %d\n", lineNumber);
        exit(1);
    }
    if (!score_flag)
    {
        printf("Error! Not initialised score in line no : %d\n", lineNumber);
        exit(1);
    }
    if (!diff_flag)
    {
        printf("Error! Not initialised difficulty in line no : %d\n", lineNumber);
        exit(1);
    }

    newnode.nd.diff = difficulty;
    newnode.nd.score = score;

    char ans_check_flag = 0;

    for (int j = 0; j < noOfOptions; j++)
    {
        if (strcmp(opts[j], anss) == 0)
        {
            ans_check_flag = 1;
            break;
        }
    }
    if (ans_check_flag == 0)
    {
        printf("\"%s\" is present in the answer but not in the questions. Line number : %d\n", anss, lineNumber);
        exit(1);
    }

    push_back(&vec_single_C_mcq, newnode);
    for (int i = 0; i < noOfOptions; i++)
        free(opts[i]);
    free(anss);
    free(opts);
}