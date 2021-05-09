#include <string.h>

#include <stdlib.h>

#include <stdio.h>

#include "../vector/vec.h"
#include "../Utils/cleanText.h"
#include "../Utils/lineNumber.h"
#include "../Utils/parsers.h"
#include "../Utils/readFile.h"
#include "../Validators/mulmcqs.h"

void printSingleCorrect_MCQs(FILE *qb, FILE *outputPaper, FILE *outputAnswer)
{

    char *text;  // will store the question text
    char *param; // will store different parameters one vby one i.e. LHS of =
    char *value; // will store the valus of different parameters i.e. RHS of =

    // Use pointers....
    // char options[4][1000];   // will store 4 different options of the question...
    // char correctOption[100]; // will store the corrcet option for a particular question...

    // Difficulty rep by diff, Max Score for a particular Que by score..
    // Using float instead of doule...
    float diff, score;

    // Initialize all flags to 0...
    char text_flag = 0, diff_flag = 0, score_flag = 0, opt_flag = 0, ans_flag = 0;

    // Pointers for correctAnswer and Options...
    char **anss, **opts;
    anss = (char **)malloc(sizeof(char *) * 8);
    opts = (char **)malloc(sizeof(char *) * 8);

    // for counting the nno. of options and correctAnswers...
    int no_opt = 0, no_ans = 0;

    int count = 5;
    while (count--)
    {
        // brings int eh value and the parameter...
        parseArgument(qb, &param, &value);

        // If the parameter is text...
        if (strcmp(param, "text") == 0)
        {
            clean(value);
            // Copy the text of the question to text array
            text = (char *)malloc(sizeof(strlen(value)));
            strcpy(text, value);
        }
        // If the parameter is score...
        else if (strcmp(param, "score") == 0)
        {
            // store the max score(double)
            score = atof(value);
        }
        // If the parameter is ans...
        else if (strcmp(param, "ans") == 0)
        {
            clean(value);
            // Store the correctOption in the correctOption array

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
            no_ans = o + 1;
        }
        else if (strcmp(param, "opt") == 0)
        {
            // Firstly separe the different options present int the char value[] array
            // and then 1 by 1 store them in 4 different char arrays...
            // int i = 0;
            // int o = 0;
            // while (value[i] != '\0')
            // {
            //     int j = 0;
            //     while (value[i] != ':' && value[i] != '\0')
            //     {
            //         options[o][j] = value[i];
            //         ++j;
            //         ++i;
            //     }
            //     if (value[i] == ':')
            //     {
            //         options[o][j] = '\0';
            //         ++i;
            //         ++o;
            //     }
            //     if (value[i] == '\0')
            //     {
            //         options[o][j] = value[i];
            //     }
            // }
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

    // Print the Question text in the output File...
    fprintf(outputPaper, "Q)\t%s\n", text);
    // Print the Max Score for that Question after the text in the output File...
    fprintf(outputPaper, "\t[score : %0.2f]\n\n", score);

    for (int i = 0; i < no_opt; i++)
    {
        // Print the 4 different options stored in diff arrays 1 by 1 ...
        // Also print the option nos. e.g. A)... B)... C)... D)...
        fprintf(outputPaper, " %c) %s \n", 65 + i, opts[i]);
    }
    for (int i = 0; i < no_ans; i++)
    {
        // Compare each option with the correctAnswer Option...
        // if (strcmp(correctOption, options[i]) == 0)
        // {
        //     // If a particular Option is correct print it on tghe Output Answer file...
        //     // along with the option number
        //     // And if no option is matching donot print anything...
        //     fprintf(outputAnswer, " %c) %s\n\n", 65 + i, correctOption);
        //     break;
        // }
        fprintf(outputAnswer, "%c) %s\n", 65 + i, anss[i]);
    }

    // Releasing memory to avoid memory leak...
    for (int i = 0; i < no_opt; i++)
        free(opts[i]);
    free(opts);
    free(text);
    free(anss);
}