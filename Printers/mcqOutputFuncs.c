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
void printSingleCorrect_MCQs(FILE *qb, FILE *outputPaper, FILE *outputAnswer)
{

    char *text;  // will store the question text
    char *param; // will store different parameters one vby one i.e. LHS of =
    char *value; // will store the valus of different parameters i.e. RHS of =

    // Use pointers....
    // char options[4][1000];   // will store 4 different options of the question...
    // char correctOption[100]; // will store the corrcet option for a particular question...

    float diff, score;
    char text_flag = 0, diff_flag = 0, score_flag = 0, opt_flag = 0, ans_flag = 0;

    char *anss, **opts;
    opts = (char **)malloc(sizeof(char *) * 8);
    int no_opt = 0, no_ans = 0;

    int count = 5;
    while (parseArgument(qb, &param, &value))
    {
        if (strcmp(param, "text") == 0)
        {
            clean(value);
            // Copy the text of the question to text array
            text = (char *)malloc(sizeof(char) * strlen(value) + 1);
            strcpy(text, value);
            remove_spaces(&text);
        }
        else if (strcmp(param, "score") == 0)
        {
            // store the max score(double)
            score = atof(value);
        }
        else if (strcmp(param, "ans") == 0)
        {
            clean(value);
            anss = (char *)malloc(strlen(value) + 1);
            strcpy(anss, value);
            remove_spaces(&anss);
        }
        else if (strcmp(param, "opt") == 0)
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
                    }
                    opts[o] = (char *)malloc(sizeof(char) * strlen(value) + 1);
                    j = 0;
                }
            }
            opts[o][j] = '\0';
            remove_spaces(&opts[o]);
            no_opt = o + 1;
        }
    }

    // Print the Question text in the output File...
    clean(text);
    fprintf(outputPaper, "Q%d) %s", question_number, text);
    // Print the Max Score for that Question after the text in the output File...
    fprintf(outputPaper, "\t[score : %0.2f]\n\n", score);
    for (int i = 0; i < no_opt; i++)
    {
        // Print the 4 different options stored in diff arrays 1 by 1 ...
        // Also print the option nos. e.g. A)... B)... C)... D)...
        clean(opts[i]);
        fprintf(outputPaper, " %c) %s \n", 65 + i, opts[i]);
    }
    fprintf(outputPaper, " \n");
    fprintf(outputAnswer, "Q%d)", question_number);
    for (int i = 0; i < no_opt; i++)
    {
        if (strcmp(anss, opts[i]) == 0)
        {
            clean(anss);
            fprintf(outputAnswer, " %c) %s\n", 65 + i, anss);
        }
    }
    question_number++;
    free(text);
    free(anss);
    for (int i = 0; i < no_opt; i++)
        free(opts[i]);
    free(opts);
}