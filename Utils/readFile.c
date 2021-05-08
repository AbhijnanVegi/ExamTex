#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "readFile.h"
#include "lineNumber.h"
#include "parsers.h"
#include "../vector/vec.h"
int lineNumber = 0;

/*void readQuestionBank(FILE *qb)
{
    char *type;
    vector v_type = allocate(STRING, 20);
    vector v_parameter = allocate(STRING, 20);
    char *param;
    char *value;
    vector v_value = allocate(STRING, 100);
    while (parseType(qb, &v_type))
    {
        type = return_string(&v_type);
        if (strcmp(type, "question") != 0)
        {
            printf("Expected block of type 'question' at line number : %d in question bank file", lineNumber);
            exit(1);
        }
        else
        {
            if (!parseArgument(qb, &v_parameter, &v_value) || strcmp(v_parameter.u.string, "type") != 0)
            {
                printf("Expected type of question at line number : %d in question bank file", lineNumber);
                exit(1);
            }
            else if (strcmp(v_value.u.string, "singlecorrect") == 0)
            {
                //
            }
            else
            {
                printf("Invalid type of question at line number : %d in question bank file", lineNumber);
                exit(1);
            }
        }
    }
}
*/