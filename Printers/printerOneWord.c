//UPDATED...
#include "../Validators/validateOneWord.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../vector/vec.h"
#include "../Utils/cleanText.h"
#include "../Utils/lineNumber.h"
#include "../Utils/parsers.h"
#include "../Utils/readFile.h"
extern int question_number;
// Parameters: qPaper - Output for question paper, finAnswer - file to store answer
void printOneWord(FILE *fp, FILE *qPaper, FILE *finAnswer)
{
    char *text;
    char *param;
    char *value;
    char text_flag = 0, diff_flag = 0, score_flag = 0, ans_flag = 0;
    float diff, score;
    char *anss;
    while (parseArgument(fp, &param, &value))
    {
        if (strcmp(param, "text") == 0)
        {
            clean(value);
            text = (char *)malloc(sizeof(strlen(value)));
            strcpy(text, value);
        }
        else if (strcmp(param, "ans") == 0)
        {
            clean(value);
            anss = (char *)malloc(sizeof(char) * strlen(value));
            strcpy(anss, value); // Storing the "answer"
            remove_spaces(&anss);
        }
        else if (strcmp(param, "score") == 0)
        {
            score = atof(value); // Stroring the "score"
        }
    }
    fprintf(qPaper, "Q%d) %s", question_number, text);
    fprintf(qPaper, "\t[score : %0.2f]\n", score);
    fprintf(qPaper, "Answer: _________\n\n");
    fprintf(finAnswer, "Q%d) %s\n\n", question_number, anss);
    question_number++;
}