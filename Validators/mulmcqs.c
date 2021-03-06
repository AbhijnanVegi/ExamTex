#include "mulmcqs.h"
#include <string.h>
#include <stdlib.h>
#include "../vector/vec.h"
#include "../Utils/cleanText.h"
#include "../Utils/lineNumber.h"
#include "../Utils/parsers.h"
#include "../Utils/readFile.h"
extern vector vec_mul_mcq;

void mul_mcq_validator(FILE *fp, int id)
{
    char *param, *value;//Initialise pointers for return values
    int count = 5;
    char text_flag = 0, diff_flag = 0, score_flag = 0, opt_flag = 0, ans_flag = 0;//Initialse all flags to false
    float diff, score;
    char **anss, **opts;
    anss = (char **)malloc(sizeof(char *) * 8);
    opts = (char **)malloc(sizeof(char *) * 8);
    int no_opt = 0, no_ans = 0;
    parameterUnion u;
    u.nd.id = id;//Store id of the question
    while (parseArgument(fp, &param, &value))//Call parseArgument() until all parameters are read
    {
        if (strcmp(param, "text") == 0) //Verify validity of input
        {
            if (!text_flag)
            {
                text_flag = 1;
            }
            else //Duplicate parameter
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
            if (!ans_flag) //Split options to verify later
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
                remove_spaces(&anss[o]);
                no_ans = o + 1;
            }
            else
            {
                printf("Error! Answer initialised twice in line no : %d \n", lineNumber);
                exit(1);
            }
        }
        else if (strcmp(param, "opt") == 0)
        {
            if (!opt_flag) //SPlit options for verification
            {
                opt_flag = 1;
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
                opts[o][j] = '\0';
                remove_spaces(&opts[o]);
                no_opt = o + 1;
            }
            else
            {
                printf("Error! Option initialised twice in line no : %d \n", lineNumber);
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
            printf("Unknown parameter '%s' on line number : %d", param, lineNumber);
            exit(1);
        }
    }
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

    char ans_check_flag[no_ans]; //verify validity of ans and opt
    for (int i = 0; i < no_ans; i++)
        ans_check_flag[i] = 0;
    for (int i = 0; i < no_ans; i++)
    {
        for (int j = 0; j < no_opt; j++)
        {
            if (strcmp(opts[j], anss[i]) == 0)
            {
                ans_check_flag[i] = 1;
                break;
            }
        }
    }
    for (int i = 0; i < no_ans; i++)
    {
        if (ans_check_flag[i] == 0)
        {
            printf("Error! \" %s \" is part of answer but not part of options. Line number : %d\n", anss[i], lineNumber);
        }
    }
    u.nd.diff = diff;
    u.nd.score = score;
    push_back(&vec_mul_mcq, u);//Save question
    for (int i = 0; i < no_ans; i++)//Free all pointers
        free(anss[i]);
    for (int i = 0; i < no_opt; i++)
        free(opts[i]);
    free(anss);
    free(opts);
    
}
