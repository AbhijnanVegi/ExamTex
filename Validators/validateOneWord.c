#include "validateOneWord.h"
#include <string.h>
#include <stdlib.h>
#include "../vector/vec.h"
#include "../Utils/cleanText.h"
#include "../Utils/lineNumber.h"
#include "../Utils/parsers.h"
#include "../Utils/readFile.h"

extern vector vec_oneword;

void validateOneWord(FILE *fp, int id)
{
    char *param;
    char *value;

    int count = 4;
    int parametersRead = 0;
    // Parameters Needed
    //      =>text
    //      =>ans
    //      =>difficulty
    //      =>score
    char text_flag = 0, diff_flag = 0, score_flag = 0, ans_flag = 0;
    float diff, score;
    // Not sure of this...
    char **anss;
    // bcz since it is 1 Word so only 1 string will be stored..
    anss = (char **)malloc(sizeof(char *) * 1);

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
                text_flag = 1;
            }
            else
            {
                printf("Error! Text initialised twice in line no : %d \n", lineNumber);
                exit(1);
            }
        }
        else if (strcmp(param, "ans") == 0)
        {
            // Same here, type checking not needed since it can be any type in single or group of words
            if (!ans_flag)
            {
                ans_flag = 1;
            }
            else
            {
                printf("Error! Answer initialised twice in line no : %d \n", lineNumber);
                exit(1);
            }
        }
        else if (strcmp(param, "difficulty") == 0)
        {
            // Difficulty can be in double, checking if it is the same in input
            if (!diff_flag)
            {
                diff_flag = 1;
                if (sscanf(value, "%f", &diff) != 1)
                {
                    printf("Error on line number : %d, Difficulty must be decimal", lineNumber);
                    exit(1);
                }
            }
            else
            {
                printf("Error! Difficulty initialised twice in line no : %d \n", lineNumber);
                exit(1);
            }
        }
        else if (strcmp(param, "score") == 0)
        {
            if (!score_flag)
            {
                score_flag = 1;
                if (sscanf(value, "%f", &score) != 1)
                {
                    printf("Error on line number : %d, Score must be decimal", lineNumber);
                    exit(1);
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
    u.nd.diff = diff;
    u.nd.score = score;
    push_back(&vec_oneword, u);
}
