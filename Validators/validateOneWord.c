#include "validateOneWord.h"

#include <string.h>
#include <stdlib.h>

#include "../vector/vec.h"
#include "../Utils/cleanText.h"
#include "../Utils/lineNumber.h"
#include "../Utils/parsers.h"
#include "../Utils/readFile.h"

extern vector vec_one_word;

void validateOneWord(FILE *fp, int id)
{
    char *param; // To store the type of parameter
    char *value; // To store the value associated with parameter.

    int count = 4;
    int parametersRead = 0;

    // Flags to check any repetitive params
    bool text_flag = false, diff_flag = false, score_flag = false, ans_flag = false;
    float diff, score;
    
    parameterUnion u;
    u.nd.id = id;

    while (parseArgument(fp, &param, &value))
    {
        // parseArgument(fp, &param, &value);
        if (strcmp(param, "text") == 0)
        {
            // Type checking not needed for question
            if (!text_flag)
            {
                text_flag = true;
            }
            else // checking for duplicate appearances of parameters
            {
                printf("Error! Text initialised twice in line no : %d \n", lineNumber);
                exit(1);
            }
        }
        else if (strcmp(param, "ans") == 0) // Validation for ans param
        {
            // Same here, type checking not needed since it can be any type in single or group of words
            if (!ans_flag)
            {
                ans_flag = true;
            }
            else
            {
                printf("Error! Answer initialised twice in line no : %d \n", lineNumber);
                exit(1);
            }
        }
        else if (strcmp(param, "difficulty") == 0) // Validation for difficulty param
        {
            // Difficulty can be in double, checking if it is the same in input
            if (!diff_flag)
            {
                diff_flag = true;
                if (sscanf(value, "%f", &diff) != 1)
                {
                    printf("Error on line number : %d, Answer must be decimal", lineNumber);
                    exit(1);
                }
            }
            else
            {
                printf("Error! Difficulty initialised twice in line no : %d \n", lineNumber);
                exit(1);
            }
        }
        else if (strcmp(param, "score") == 0) // Validation for score param
        {
            if (!score_flag)
            {
                score_flag = true;
                if (sscanf(value, "%f", &score) != 1)
                {
                    printf("Error on line number : %d, Difficulty must be decimal", lineNumber);
                }
            }
            else
            {
                printf("Error! Score initialised twice in line no : %d \n", lineNumber);
                exit(1);
            }
        }
        else
        {
            // Checking if any other paramter is found other than above specified
            printf("Unknown parameter '%s' on line number : %d", param, lineNumber);
            exit(1);
        }
    }
    // Checking if any of the params didn't appear even once
    // Output those as errors
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
    // Storing these useful params
    u.nd.diff = diff;
    u.nd.score = score;
    push_back(&vec_one_word, u);
}
