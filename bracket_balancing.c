/**************************************************************************************
--------------------------------Vector Library-----------------------------------------
Made by - Sumanth
implementation of bracket balancing using vectors                                                                  
***************************************************************************************/
#include "vec.h"
#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include <stdlib.h>

int IsLeft(char ch)
{
    if (ch == '(')
        return 1;
    else if (ch == '{')
        return 2;
    else if (ch == '[')
        return 3;
    else if (ch == '<')
        return 4;
    else
        return 0;
}

int IsRight(char ch)
{
    if (ch == ')')
        return 1;
    else if (ch == '}')
        return 2;
    else if (ch == ']')
        return 3;
    else if (ch == '>')
        return 4;
    else
        return 0;
}


int main(){

    FILE *fp = fopen("name.txt", "r");
    char ch;
    int fileSize;
    int left_idx, right_idx;

    int lineno = 1, colno = 0;

    // vector init
    vector vec;
    vec = NEWVector(0);

    fseek(fp, 0L, SEEK_END);
    fileSize = ftell(fp);
    rewind(fp);

    while (!feof(fp))
    {
        ch = getc(fp);
        if (ch == '\n')
        {
            lineno++;
            colno = 0;
        }
        colno++;
        if (IsLeft(ch))
            // Push(S, ch, lineno, colno);
            push_back(vec, ch, lineno, colno);
        else
        {
            right_idx = IsRight(ch);
            if (right_idx)
            {
                if (IsEmpty(S)) // .
                    printf("ERROR! lineno-%d colno-%d\n", lineno, colno);
                else
                {
                    // left_idx = IsLeft(Top(S).ch);
                    left_idx = IsLeft(back(vec).ch);
                    if (right_idx != left_idx)
                        printf("ERROR! lineno-%d colno-%d\n", lineno, colno);

                    // Pop(S);
                    pop_back(vec);
                }
            }
        }
    }
    while (!IsEmpty(S)) // .
    {
        printf("ERROR!lineno-%d colno-%d\n", Top(S).line, Top(S).col);
        // Pop(S);
        pop_back(vec);
    }


    
    return 0;
}