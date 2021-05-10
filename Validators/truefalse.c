
////// I am not using flush function anywhere , I need to include it

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "../vector/vec.h"
#include "../Utils/cleanText.h"
#include "../Utils/lineNumber.h"
#include "../Utils/parsers.h"
#include "../Utils/readFile.h"
extern vector vec_tf;
enum parameters
{
    TEXT,
    OPT,
    ANS,
    DIFFICULTY,
    SCORE
};

void validateTrueFalse(FILE *fp, int pos)
{
    char *param, *value;
    int count = 5;
    char text_flag = 0, diff_flag = 0, score_flag = 0, opt_flag = 0, ans_flag = 0;
    float diff, score;
    char **anss, **opts;
    anss = (char **)malloc(sizeof(char *) * 8);
    opts = (char **)malloc(sizeof(char *) * 8);
    int no_opt = 0, no_ans = 0;
    parameterUnion u;
    u.nd.id = pos;
    while (parseArgument(fp, &param, &value))
    {
        if (strcmp(param, "text") == 0)
        {
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
        else if (strcmp(param, "difficulty") == 0)
        {
            if (!diff_flag)
            {
                diff_flag = 1;
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
        else if (strcmp(param, "ans") == 0)
        {
            if (!ans_flag)
            {
                ans_flag = 1;
                if (strcmp(value, "true") != 0 && strcmp(value, "false") != 0)
                {
                    printf("Error! Answer can only be \"true\" or \"false\". Line Number : %d\n ", lineNumber);
                }
            }
            else
            {
                printf("Error! Answer initialised twice in line no : %d \n", lineNumber);
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
            printf("Unknown parameter '%s' on line number : %d", param, lineNumber);
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
    push_back(&vec_tf, u);
    for (int i = 0; i < no_ans; i++)
        free(anss[i]);
    for (int i = 0; i < no_opt; i++)
        free(opts[i]);
    free(anss);
    free(opts);
}
