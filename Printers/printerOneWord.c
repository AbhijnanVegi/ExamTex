#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Utils/parsers.h"
#include "../Utils/lineNumber.h"
// Parameters: qPaper - Output for question paper, finAnswer - file to store answer
void printOneWord(FILE *fp, FILE* qPaper, FILE* finAnswer)
{
    char param[20];
    char value[100];
    char text[100];
    
    char ans[100];
    double score;
    
    while(parseArgument(fp,param,value))
    {
        if(strcmp(param,"text") == 0)
        {
            clean(value);
            strcpy(text, value); // Storing the "question"
        }
        else if (strcmp(param,"ans") == 0)
        {
            clean(value);
            strcpy(ans, value); // Storing the "answer"
            
        }
        else if (strcmp(param,"score") == 0)
        { 
            score = atof(value); // Stroring the "score"
            
        }        
    }
    fprintf(qPaper, "%s", text);
    fprintf(qPaper, "\t[score : %f]\n", score);
    fprintf(qPaper, "Answer: ____\n");
    fprintf(finAnswer, "%s", ans);
}