
////// I am not using flush function anywhere , I need to include it


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "parsers.h"
#include "lineNumber.h"
#include "vec1.h"

int check_if_complete(bool flag[5]) /////// This function checks if all the required parametres have been entered
{
    int count = 0;
    for (int i = 0; i < 5; i++)
    {
        if (flag[i] == true)
        {
            count++;
            flag[i] == false;
        }
    }

    return count;
}

void validateTrueFalse(FILE *fp, int pos)
{
    char param[20];  /// To store the LHS side of '='
    char value[100]; //// To store the RHS side of '='
    int numberOfParametersRequired = 5;
    int parametersRead = 0; //// It keeps track of the number of parameters that have been temporarily stored in newnode before pushing it into Vec
    char ans[7] = {0};      //// To check if the answer is valid
    double difficulty;      //// To check if the parameter difficulty has been encounterd
    double score;           //////To check if the parameter score has been encounterd
    int n = 0;              /////Not really required need to fix before sub
    //int i = 0;
    char opt[7]={0};
    bool flag[5] = {false};

    vector vec;

    parameterUnion newnode; //// It is a temporary node to note the values

    vec = allocate(NODE, 20); /////// n is given by parser function

    //fp = fopen("trufalse.txt", "r");

    fseek(fp, pos, SEEK_SET); /// not sure whether it is pos or -1L

    while (parseArgument(fp, param, value)) /// It is a function defined in parser.h and it returns the LHS and RHS strings on '='
    {
        if (parametersRead == 0)
        {
            //fseek(fp, -1L , SEEK_CUR); //  not sure wheter I should include it , need to confirm if Abhignans func already sets it
            newnode.nd.id = ftell(fp);
        }

        if (strcmp(param, "text") == 0)
        {
            //Do nothing as no validation is required for text
            //Save in vector
            parametersRead++;
            flag[0] = true; /// Just makes a note that parametre text has been read
        }
        
        if(strcmp(param, "opt") == 0)
        {
            if (sscanf(value, "%s", opt) != 1 || strcmp(ans, "true/false") != 0)
            {
               printf("Error on the line number : %d, opt must be of the form true/false ",lineNumber);
            }
            flag[1] = true;
            parametersRead++;

        }

        else if (strcmp(param, "ans") == 0)
        {

            if (sscanf(value, "%s", ans) != 1 || ((strcmp(ans, "true") != 0) && (strcmp(ans, "false") != 0)))
            {
                /// flags an error either if no answer has been entered or the entered ans is neither true nor false
                printf("Error on line number : %d, Answer must be true or false", lineNumber);
            }
            flag[2] = true;
            parametersRead++;
        }
        else if (strcmp(param, "difficulty") == 0)
        {
            if (sscanf(value, "%lf", &difficulty) != 1)
            {
                printf("Error on line number : %d, Difficulty must be decimal", lineNumber);
            }

            flag[3] = true;
            newnode.nd.diff = difficulty;
            parametersRead++;
        }
        else if (strcmp(param, "score") == 0)
        {
            if (sscanf(value, "%lf", &score) != 1)
            {
                printf("Error on line number : %d, Difficulty must be decimal", lineNumber);
            }
            flag[4] = true;
            newnode.nd.score = score;
            parametersRead++;
        }
        else
        {
            printf("Unknown parameter '%s' on line number : %d", param, lineNumber);
        }


        /// parametersRead == numberOfParametersRequired /// can be actually completely avoided
        if (parametersRead == numberOfParametersRequired && check_if_complete(flag) == 5)
        {  
            /// only if all the correct set of parametres have been entered push it into vec
            push_back(&vec, newnode);
            parametersRead = 0;
        }
        else
        {
            printf("parameters are missing ");
        }
    }
    //save the question here
}
