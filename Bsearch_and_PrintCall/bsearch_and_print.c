#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "../vector/vec.h"
#include "../Binarysearch/binary_search.h"
#include "../Printers/mcqOutputHeader.h"
#include "../Printers/printmulmcq.h"
#include "../Printers/printNumerical.h"
#include "../Printers/printTF.h"
#include "../Printers/printerOneWord.h"
#include "../Utils/lineNumber.h"
extern vector vec_mul_mcq;
extern vector vec_numerical;
extern vector vec_single_C_mcq;
extern vector vec_tf;
extern vector vec_oneword;
extern int lineNumber;
extern vector vec_mul_mcq_bool;
extern vector vec_numerical_bool;
extern vector vec_single_C_mcq_bool;
extern vector vec_tf_bool;
extern vector vec_oneword_bool;
void select_rand_q(int ub, int lb, int num_q, char *type, FILE *qb, FILE *op, FILE *oa) ////This function selects random questions from question bank file and read them
{

    int m = 0;
    int index = 0;
    FILE *outputQP = op;
    FILE *outputANS = oa;

    if (strcmp(type, "numerical") == 0) /////They have been divided accordingly so that we can call the neccessary input files
    {
        srand(time(0));
        for (int i = 0; i < num_q; i++)
        {
            m = (rand() % (ub - lb + 1));
            int x;
            int j = 0;
            for (; j < ub - lb + 1; j++)
            {
                x = (m + j) % (ub - lb + 1);
                if (vec_numerical_bool.u.string[x + lb] == '\0')
                    break;
            }
            if (j < ub - lb + 1)
            {
                //m =1;
                index = vec_numerical.u.nodeElems[lb + x].id;
                vec_numerical_bool.u.string[x + lb] = 1;
                fseek(qb, index, SEEK_SET);
                printNumerical(qb, outputQP, outputANS);
            }
            else
            {
                printf("Error! Not that many questoins of the rquired type \" %s \".\n", type);
                exit(1);
            }
        }
    }
    if (strcmp(type, "mcq") == 0)
    {
        srand(time(0));
        for (int i = 0; i < num_q; i++)
        {
            m = (rand() % (ub - lb + 1));
            int x;
            int j = 0;
            for (; j < ub - lb + 1; j++)
            {
                x = (m + j) % (ub - lb + 1);
                if (vec_single_C_mcq_bool.u.string[x + lb] == '\0')
                    break;
            }
            if (j < ub - lb + 1)
            {
                //m =1;
                index = vec_single_C_mcq.u.nodeElems[lb + x].id;
                vec_single_C_mcq_bool.u.string[x + lb] = 1;
                fseek(qb, index, SEEK_SET);
                printSingleCorrect_MCQs(qb, outputQP, outputANS);
            }
            else
            {
                printf("Error! Not that many questoins of the rquired type \" %s \".\n", type);
                exit(1);
            }

            // m = rand() % (ub - lb + 1);
            // index = vec_single_C_mcq.u.nodeElems[lb + m].id;
            // fseek(qb, index, SEEK_SET);

            // printSingleCorrect_MCQs(qb, outputQP, outputANS);
        }
    }
    if (strcmp(type, "mul_mcq") == 0)
    {
        srand(time(0));
        for (int i = 0; i < num_q; i++)
        {
            m = (rand() % (ub - lb + 1));
            int x;
            int j = 0;
            for (; j < ub - lb + 1; j++)
            {
                x = (m + j) % (ub - lb + 1);
                if (vec_mul_mcq_bool.u.string[x + lb] == '\0')
                    break;
            }
            if (j < ub - lb + 1)
            {
                //m =1;
                index = vec_mul_mcq.u.nodeElems[lb + x].id;
                vec_mul_mcq_bool.u.string[x + lb] = 1;
                fseek(qb, index, SEEK_SET);
                printMultiple_MCQs(qb, outputQP, outputANS);
            }
            else
            {
                printf("Error! Not that many questoins of the rquired type.\n");
                exit(1);
            }
        }
    }
    if (strcmp(type, "truefalse") == 0)
    {
        srand(time(0));
        for (int i = 0; i < num_q; i++)
        {
            m = (rand() % (ub - lb + 1));
            int x;
            int j = 0;
            for (; j < ub - lb + 1; j++)
            {
                x = (m + j) % (ub - lb + 1);
                if (vec_tf_bool.u.string[x + lb] == '\0')
                    break;
            }
            if (j < ub - lb + 1)
            {
                //m =1;
                index = vec_tf.u.nodeElems[lb + x].id;
                vec_tf_bool.u.string[x + lb] = 1;
                fseek(qb, index, SEEK_SET);
                printTF(qb, outputQP, outputANS);
            }
            else
            {
                printf("Error! Not that many questoins of the rquired type \" %s \".\n", type);
                exit(1);
            }
        }
    }
    if (strcmp(type, "oneword") == 0)
    {
        srand(time(0));
        for (int i = 0; i < num_q; i++)
        {
            m = (rand() % (ub - lb + 1));
            int x;
            int j = 0;
            for (; j < ub - lb + 1; j++)
            {
                x = (m + j) % (ub - lb + 1);
                if (vec_oneword_bool.u.string[x + lb] == '\0')
                    break;
            }
            if (j < ub - lb + 1)
            {
                //m =1;
                index = vec_oneword.u.nodeElems[lb + x].id;
                vec_oneword_bool.u.string[x + lb] = 1;
                fseek(qb, index, SEEK_SET);
                printOneWord(qb, outputQP, outputANS);
            }
            else
            {
                printf("Error! Not that many questoins of the rquired type \" %s \".\n", type);
                exit(1);
            }
            // m = rand() % (ub - lb + 1);
            // index = vec_oneword.u.nodeElems[lb + m].id;
            // fseek(qb, index, SEEK_SET);

            // printOneWord(qb, outputQP, outputANS); //////////////////////////
        }
    }
}

void b_search(vector *vec, float diff_ub, float diff_lb, int num_q, char type[], FILE *fp, FILE *op, FILE *oa)
{

    int pos_ub = 0;
    int pos_lb = 0;
    pos_ub = binary_ub_search(vec, diff_ub);
    pos_lb = binary_lb_search(vec, diff_lb);

    if (pos_ub >= 0 && pos_lb <= size(vec) - 1 && pos_lb <= pos_ub)
    {
        if (pos_ub - pos_lb + 1 < num_q)
        {
            printf("Error! Not that many questions of that type in the question bank file.\nLine number : %d\n", lineNumber);
            exit(1);
        }

        select_rand_q(pos_ub, pos_lb, num_q, type, fp, op, oa);
    }
    else
    {
        printf("Invalid bounds for difficulty\n");
        exit(1);
    }
}