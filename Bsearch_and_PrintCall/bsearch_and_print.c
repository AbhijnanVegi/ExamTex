///////////////////The function names are not correct for calling of print functions...need to change after evryone commits one final time
#include <stdio.h>
#include <stdlib.h>
////#include "vec1.h" //// contains vectors written by Shreyansh
#include <time.h>
#include <stdbool.h>
#include "printNumerical.h"
#include "binary_search.h"
#include "merge_sort.h"
#include "../vector/vec.h"
#include "print_output.h"
#include "../Utils/parsers.h"
#include "../Utils/parsers.h"
#include "../Utils/cleanText.h"
#include "binary_search.h"

void select_rand_q(vector *vec, int ub, int lb, int num_q, char *type, FILE *fp) ////This function selects random questions from question bank file and read them
{

    int m = 0;
    int index = 0;
    FILE *outputQP;
    FILE *outputANS;
    //char* array_type ;

    //array_type = (char*)malloc(strlen(type)*sizeof(char));

    ////// I am not sure about y v need this..but writing it just in case
    enum type
    {
        numerical,
        mcq,
        mul_mcq,
        truefalse,
        singleword,
    };

    bool flag[5];

    flag[numerical] = false;

    flag[mcq] = false;

    flag[mul_mcq] = false;

    flag[truefalse] = false;

    flag[singleword] = false;

    if (strcmp(type, "numerical") == 0) /////They have been divided accordingly so that we can call the neccessary input files
    {
        srand(time(0));
        for (int i = 0; i < num_q; i++)
        {
            m = rand() % (ub - lb);

            index = vec->u.nodeElems[lb + m].id;
            fseek(fp, index, SEEK_SET);
            printNumerical(fp, outputQP, outputANS);
        }

        flag[numerical] = true;
    }
    if (strcmp(type, "mcq") == 0)
    {
        srand(time(0));
        for (int i = 0; i < num_q; i++)
        {
            m = rand() % (ub - lb);
            fseek(fp, index, SEEK_SET);
            index = vec->u.nodeElems[lb + m].id;
            printmcq(fp, outputQP, outputANS); 
        }
    }
    if (strcmp(type, "mul_mcq") == 0)
    {
        srand(time(0));
        for (int i = 0; i < num_q; i++)
        {
            m = rand() % (ub - lb);
            fseek(fp, index, SEEK_SET);
            index = vec->u.nodeElems[lb + m].id;
            printmulmcq(fp, outputQP, outputANS);///////////Need to change the names of functions
        }
    }
    if (strcmp(type, "truefalse") == 0)
    {
        srand(time(0));
        for (int i = 0; i < num_q; i++)
        {
            m = rand() % (ub - lb);
            fseek(fp, index, SEEK_SET);
            index = vec->u.nodeElems[lb + m].id;
            printTF(fp, outputQP, outputANS);
        }
    }
    if (strcmp(type, "singleword") == 0)
    {
        srand(time(0));
        for (int i = 0; i < num_q; i++)
        {
            m = rand() % (ub - lb);
            fseek(fp, index, SEEK_SET);
            index = vec->u.nodeElems[lb + m].id;
            printsingleword(fp, outputQP, outputANS);//////////////////////////
        }
    }
}

void b_search(vector *vec, float diff_ub, float diff_lb, int num_q, char type[], FILE *fp)
{

    int pos_ub = 0;
    int pos_lb = 0;
    pos_ub = binary_ub_search(vec, diff_ub) - 1;
    pos_lb = binary_lb_search(vec, diff_lb) + 1;

    if (vec->u.nodeElems[pos_lb - 1].diff == diff_lb)
    {
        pos_lb = pos_lb - 1;
    }
    //printf("ub : %d\n", pos_ub);
    //printf("lb : %d\n", pos_lb);

    select_rand_q(vec, pos_ub, pos_lb, num_q, type, fp);
}
