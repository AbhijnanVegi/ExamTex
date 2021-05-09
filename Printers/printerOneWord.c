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

// Parameters: qPaper - Output for question paper, finAnswer - Output for store answer
void printOneWord(FILE *fp, FILE *qPaper, FILE *finAnswer)
{
    char *text;
    // stroring type of "param" and "value" associated with it
    char *param;
    char *value;

    float diff, score;
    char *answer;
    while (parseArgument(fp, &param, &value))
    {
        if (strcmp(param, "text") == 0)
        {
            clean(value);
            text = (char *)malloc(sizeof(strlen(value)));
            strcpy(text, value); // Storing the "question"
        }
        else if (strcmp(param, "ans") == 0)
        {
            clean(value);
            answer = (char *)malloc(sizeof(char) * strlen(value));
            strcpy(answer, value); // Storing the "answer"
            // Removes spaces from answer
            remove_spaces(&answer);
        }
        else if (strcmp(param, "score") == 0)
        {
            score = atof(value); // Stroring the "score"
        }
    }
    // Output to question paper in proper format
    fprintf(qPaper, "Q) %s", text);
    fprintf(qPaper, "\t[score : %0.2f]\n", score);
    fprintf(qPaper, "Answer: _________\n");
    // Output answer to answers key
    fprintf(finAnswer, "Correct Ans : %s", answer);
}