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

// This function removes the spaces from the text so that the correct option maches with the one given in options...
void remove_spaces(char **c)
{
    int len = strlen(*c);
    char *x = (char *)malloc(sizeof(char) * len);
    int i = 0;
    for (i = 0; i < len; i++)
    {
        if ((*c)[i] == ' ' || (*c)[i] == '\n')
            continue;
        break;
    }
    int j = 0;
    for (j = len - 1; j >= 0; j--)
    {
        if ((*c)[j] == ' ' || (*c)[j] == '\n')
        {
            (*c)[j] = '\0';
        }
        else
            break;
    }
    strcpy(x, &((*c)[i]));
    strcpy(*c, x);
    *c = (char *)realloc(*c, strlen(x));
    free(x);
}

// This is the actual validor function for validating the SINGLE CORRECT MCQ Questions...

void validateSingleCorrect_MCQ(FILE *fp, int id)
{
    // Declaring arrays to store parameters and values

    char *param; // Stores the value of LHS of the = sign
    char *value; // Stores the value of RHS of the = sign

    int parametersRead = 0;
    int numberOfParametersRequired = 5;
    // Required Parameters...
    // 1) Text
    // 2) Ans
    // 3) Difficulty
    // 4) Score
    // 5) Options

    // for temporarily storing the Max Score and difficulty for a particular question...
    double score;
    double difficulty;

    // Poiters used for storing correctOptions and Options for a Question...
    char **anss, **opts;
    anss = (char **)malloc(sizeof(char *) * 8);
    opts = (char **)malloc(sizeof(char *) * 8);

    // Initialising all flags to 0...
    char text_flag = 0, diff_flag = 0, score_flag = 0, opt_flag = 0, ans_flag = 0;

    // will keep a track of noOf Options and noOf correctAnwers provided by the user...
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
                int o = 0;
                int j = 0;
                anss[o] = (char *)malloc(sizeof(char) * strlen(value));
                for (int i = 0; i < strlen(value); i++)
                {
                    if (value[i] != ':')
                    {
                        anss[o][j] = value[i];
                        j++;
                    }
                    if (value[i] == ':')
                    {
                        anss[o][j] = '\0';
                        remove_spaces(&anss[o]);
                        o++;
                        anss[o] = (char *)malloc(sizeof(char) * strlen(value));
                        j = 0;
                    }
                }
                anss[o][j] = '\0';
                remove_spaces(&opts[o]);
                noOfAnswers = o + 1;
                // As the correct no. of answers for single corrcect mcq = 1...
                if (noOfAnswers > 1)
                {
                    printf("Error on line number : %d : More than 1 options correct for Single Correct MCQ question which is not possible.", lineNumber);
                    exit(1);
                }
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
                opts[o] = (char *)malloc(sizeof(char) * strlen(value));
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
                        opts[o] = (char *)malloc(sizeof(char) * strlen(value));
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
        }
    }
    //Print the MISSING Parameters...
    // And the respective ERROR messages...
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

    // Store the difficulty, score and id...
    newnode.nd.diff = difficulty;
    newnode.nd.score = score;

    // Already checked above that the no. of correct Options for single Corrcet MCQ = 1..
    // In such a case an error message is printed ...
    // So no need to change this code...

    char ans_check_flag[noOfAnswers];

    for (int i = 0; i < noOfAnswers; i++)
        ans_check_flag[i] = 0;
    for (int i = 0; i < noOfAnswers; i++)
    {
        for (int j = 0; j < noOfOptions; j++)
        {
            if (strcmp(opts[j], anss[i]) == 0)
            {
                ans_check_flag[i] = 1;
                break;
            }
        }
    }
    for (int i = 0; i < noOfAnswers; i++)
    {
        if (ans_check_flag[i] == 0)
        {
            printf("Error! \" %s \" is part of answer but not part of options. Line number : %d\n", anss[i], lineNumber);
        }
    }

    // Storing in the main vector by using push_back() function...
    push_back(&vec_single_C_mcq, newnode);

    // Releasing the memory dynamically allocated to avoid memory leak...
    for (int i = 0; i < noOfAnswers; i++)
        free(anss[i]);
    for (int i = 0; i < noOfOptions; i++)
        free(opts[i]);
    free(anss);
    free(opts);
}