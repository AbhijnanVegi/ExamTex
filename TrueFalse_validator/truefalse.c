
////// I am not using flush function anywhere , I need to include it

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "parsers.h"
#include "lineNumber.h"
#include "vec1.h"

enum parameters
{
    TEXT,
    OPT,
    ANS,
    DIFFICULTY,
    SCORE
};

void validateTrueFalse(FILE *fp, int pos)
{
    char **param; /// To store the LHS side of '='
    char **value; //// To store the RHS side of '='
    int numberOfParametersRequired = 5;
    int parametersRead = 0; //// It keeps track of the number of parameters that have been temporarily stored in newnode before pushing it into Vec
    char ans[20] = {0};     //// To check if the answer is valid
    double difficulty;      //// To check if the parameter difficulty has been encounterd
    double score;           //////To check if the parameter score has been encounterd
    int n = 0;              /////Not really required need to fix before sub
    //int i = 0;

    /*enum parametres
    {
        IS_TEXT,IS_ANS,IS_DIFF,IS_SCORE,_IS_OPT,
    };*/

    bool flag[5]; //Array to store if aprticular parameter has been read
    flag[TEXT] = false;
    flag[OPT] = false;
    flag[ANS] = false;
    flag[DIFFICULTY] = false;
    flag[SCORE] = false;

    char opt[20] = {0};
    //bool flag[5] = {false};

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

        if (strcmp(*param, "text") == 0)
        {
            //Do nothing as no validation is required for text
            //Save in vector
            if (flag[TEXT] == false)
            {
                flag[TEXT] = true; /// Just makes a note that parametre text has been read
                parametersRead++;
            }
            else
            {
                printf("Error on line number : %d : Duplicate parameter \"text\"", lineNumber);
                //free(*param);
                //free(*value);
                exit(1);
            }
            free(*param);
            free(*value);
        }

        if (strcmp(*param, "opt") == 0)
        {
            if (!flag[OPT])
            {
                if (sscanf(*value, "%s", opt) != 1 || strcmp(opt, "true/false") != 0)
                {
                    printf("Error on the line number : %d, opt must be of the form true/false ", lineNumber);
                }
                flag[OPT] = true;
                parametersRead++;
            }

            else
            {
                printf("Error on line number : %d : Duplicate parameter \"ans\"", lineNumber);
                exit(1);
            }
            free(*param);
            free(*value);
        }

        else if (strcmp(*param, "ans") == 0)
        {
            if (!flag[ANS])
            {
                if (sscanf(*value, "%s", ans) != 1 || ((strcmp(ans, "true") != 0) && (strcmp(ans, "false") != 0)))
                {
                    /// flags an error either if no answer has been entered or the entered ans is neither true nor false
                    printf("Error on line number : %d, Answer must be true or false", lineNumber);
                }
                flag[ANS] = true;
                parametersRead++;
            }
            else
            {
                printf("Error on line number : %d : Duplicate parameter \"ans\"", lineNumber);
                exit(1);
            }
            free(*param);
            free(*value);
        }

        else if (strcmp(*param, "difficulty") == 0)
        {
            if (!flag[DIFFICULTY])
            {
                if ((sscanf(*value, "%lf", &difficulty) != 1))
                {
                    printf("Error on line number : %d, Difficulty must be decimal", lineNumber);
                }
                flag[DIFFICULTY] = true;
                newnode.nd.diff = difficulty;
                parametersRead++;
            }
            else
            {
                printf("Error on line number : %d : Duplicate parameter \"ans\"", lineNumber);
                exit(1);
            }

            free(*param);
            free(*value);
        }
        else if (strcmp(*param, "score") == 0)
        {
            if (!flag[SCORE])
            {
                if ((sscanf(value, "%lf", &score) != 1))
                {
                    printf("Error on line number : %d, Difficulty must be decimal", lineNumber);
                }
                flag[SCORE] = true;
                newnode.nd.score = score;
                parametersRead++;
            }
            else
            {
                printf("Error on line number : %d : Duplicate parameter \"ans\"", lineNumber);
                exit(1);
            }

            free(*param);
            free(*value);
        }
        else
        {
            printf("Unknown parameter '%s' on line number : %d", param, lineNumber);
        }

        /// parametersRead == numberOfParametersRequired /// can be actually completely avoided
        if (parametersRead == numberOfParametersRequired)
        {
            /// only if all the correct set of parametres have been entered push it into vec
            push_back(&vec, newnode);
            parametersRead = 0;
        }
        else
        {
            printf("Error on line number : %d: Missing parameters : ", lineNumber); //print all missing parameters
            if (!flag[TEXT])
                printf("\"text\" ");
            if (!flag[OPT])
                printf("\"opt\" ");
            if (!flag[ANS])
                printf("\"ans\" ");
            if (!flag[DIFFICULTY])
                printf("\"diffuculty\" ");
            if (!flag[SCORE])
                printf("\"score\" ");
            free(*param);
            free(*value);
            exit(1);
        }
    }
    //save the question here
}
