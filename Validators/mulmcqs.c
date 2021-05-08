#include "mulmcqs.h"
#include "../vector/vec.h"
#include "../Utils/cleanText.h"
#include "../Utils/lineNumber.h"
#include "../Utils/parsers.h"
#include "../Utils/readFile.h"
extern vector vec_mul_mcq = allocate(NODE, 20);
void mul_mcq_validator(FILE *fp, int id)
{
    vector v_param = allocate(STRING, 20);
    vector v_value = allocate(STRING, 20);
    char *param, value;
    int count = 4;
    char text_flag = 0, diff_flag = 0, score_flag = 0, opt_flag = 0, ans_flag = 0;
    float diff, score;
    int line_number;
    char **anss, opts;
    anss = (char **)malloc(sizeof(char *) * 8);
    opts = (char **)malloc(sizeof(char *) * 8);
    parameterUnion u;
    u.nd.diff = diff;
    u.nd.id = id;
    int no_ans = 0, no_opt;
    while (count--)
    {
        parseArgument(fp, &v_param, &v_value);
        param = return_string(&v_param);
        value = return_string(&v_value);
        if (strcmp(param, "text"))
        {
            if (!text_flag)
            {
            }
            else
            {
                printf("Error! Text initialised twice in line no : %d \n", lineNumber);
                exit(1);
            }
        }
        if (strcmp(param, "difficulty"))
        {
            if (!diff_flag)
            {

                if (sscanf(value, "%f", &diff) != 1)
                {
                    printf("Error on line number : %d, Answer must be decimal", lineNumber);
                    exit(1);
                }
            }
            else
            {
                printf("Error! Difficulty initialised twice in line no : %d \n", linenumber);
                exit(1);
            }
        }
        if (strcmp(param, "ans"))
        {
            if (!diff_flag)
            {
                for (int i = 0; i < strlen(value); i++)
                {
                    if (value[i] == ':')
                        no_ans++;
                }
                int answers[no_ans];
                for (int i = 0; i < no_ans; i++)
                {
                    if (sscanf(value, "%d", &answers[i]) != 1)
                    {
                        printf("Error on line number : %d, Answer must be decimal", lineNumber);
                        exit(1);
                    }
                }
            }
            else
            {
                printf("Error! Answer initialised twice in line no : %d \n", line_number);
                exit(1);
            }
        }
        if (strcmp(param, "opt") == 0)
        {
            if (!opt_flag)
            {

                for (int i = 0; i < strlen(value); i++)
                {
                    if (value[i] == ':')
                        no_opt++;
                }
                if (no_opt > 8)
                {
                    printf("Error! more than 8 options used in line number %d \n", line_number);
                    exit(1);
                }
                int opt;
                for (int i = 0; i < no_ans; i++)
                {
                    if (sscanf(value, "%d", &answers[i]) != 1)
                    {
                        printf("Error on line number : %d, Option must be decimal", lineNumber);
                        exit(1);
                    }
                    if (answers[i] > 8)
                    {
                        printf("Error! Answer value more than 8 in line number : %d\n", line_number);
                        exit(1);
                    }
                }
            }
            else
            {
                printf("Error! Option initialised twice in line no : %d \n", line_number);
                exit(1);
            }
        }
        else if (strcmp(param, "score") == 0)
        {
            if (!opt_flag)
            {
                if (sscanf(value, "%lf", &score) != 1)
                {
                    printf("Error on line number : %d, Difficulty must be decimal", lineNumber);
                }
            }
            else
            {
                printf("Error! Score initialised twice in line no : %d \n", line_number);
                exit(1);
            }
        }
        else
        {
            printf("Unknown parameter '%s' on line number : %d", param, lineNumber);
        }
    }

    u.nd.score = score;
    push_back(&vec_mul_mcq, u);
}
