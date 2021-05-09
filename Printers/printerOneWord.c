#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include "../Utils/parsers.h"

#include "../Utils/lineNumber.h"

// Parameters: qPaper - Output for question paper, finAnswer - file to store answer
void printOneWord(FILE *fp, FILE* qPaper, FILE* finAnswer)
{
    char **param;
    char **value;
    char *text;
    
    char *ans;
    double score;
    
    while(parseArgument(fp,param,value))
    {
        if(strcmp(*param,"text") == 0)
        {
            clean(*value);
            text = *value;// Storing the "question"
            free(*param);
            free(*value);
        }
        else if (strcmp(*param,"ans") == 0)
        {
            clean(*value);
            ans = *value; // Storing the "answer"
            free(*param);
            
        }
        else if (strcmp(param,"score") == 0)
        { 
            score = atof(*value); // Stroring the "score"
            free(*param);
            free(*value);
        }        
    }
    // Output questions in proper format to question paper
    fprintf(qPaper, "%s", *text);
    fprintf(qPaper, "\t[score : %0.1f]\n", score);
    fprintf(qPaper, "Answer: ____\n");
    // Output answers to answer key
    fprintf(finAnswer, "%s", *ans);

    free(text);
    free(ans);
}