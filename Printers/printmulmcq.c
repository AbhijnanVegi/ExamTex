#include "../Validators/mulmcqs.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../vector/vec.h"
#include "../Utils/cleanText.h"
#include "../Utils/lineNumber.h"
#include "../Utils/parsers.h"
#include "../Utils/readFile.h"
#include "../Validators/mulmcqs.h"
extern int question_number;
void printMultiple_MCQs(FILE *qb, FILE *outputPaper, FILE *outputAnswer)
{
    // fseek(qb, offset, SEEK_SET);
    char *param, *value, *text;
    int count = 5;
    char text_flag = 0, diff_flag = 0, score_flag = 0, opt_flag = 0, ans_flag = 0;
    float diff, score;
    char **anss, **opts;
    anss = (char **)malloc(sizeof(char *) * 8);
    opts = (char **)malloc(sizeof(char *) * 8);
    int no_opt = 0, no_ans = 0;
    while (count--)
    {
        parseArgument(qb, &param, &value);
        //param = return_string(&vec_param);
        //value = return_string(&vec_value);
        if (strcmp(param, "text") == 0)
        {
            clean(value);
            text = (char *)malloc(sizeof(strlen(value)));
            strcpy(text, value);
        }
        else if (strcmp(param, "score") == 0)
        {
            score = atof(value);
        }
        else if (strcmp(param, "ans") == 0)
        {
            clean(value);
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
        else if (strcmp(param, "opt") == 0)
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
            opts[o][j] = '\0';
            remove_spaces(&opts[o]);
            no_opt = o + 1;
        }
    }

    fprintf(outputPaper, "Q%d) %s", question_number, text);
    fprintf(outputPaper, "\t[score : %0.2f]\n\n", score);

    for (int i = 0; i < no_opt; i++)
    {
        fprintf(outputPaper, "%c) %s \n", 65 + i, opts[i]);
    }
    fprintf(outputPaper,"\n");
    fprintf(outputAnswer, "Q%d) \n", question_number);
    for (int i = 0; i < no_ans; i++)
    {
        for (int j = 0; j < no_opt; j++)
        {
            if (strcmp(anss[i], opts[j]) == 0)
            {
                clean(anss[i]);
                fprintf(outputAnswer, " %c) %s\n", 65 + j, anss[i]);
            }
        }
    }
    fprintf(outputAnswer,"\n");
    question_number++;
    free(text);
    for (int i = 0; i < no_ans; i++)
        free(anss[i]);
    for (int i = 0; i < no_opt; i++)
        free(opts[i]);
    free(opts);
}