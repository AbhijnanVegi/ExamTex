#include <stdio.h>
#include <stdlib.h>
#include "vector/vec.h"
#include "Utils/cleanText.h"
#include "Utils/lineNumber.h"
#include "Utils/parsers.h"
#include "Utils/readFile.h"
#include "sort/merge_sort.h"
#include "Printers/mcqOutputHeader.h"

extern vector vec_mul_mcq;
extern vector vec_numerical;
extern vector vec_single_C_mcq;
extern vector vec_tf;
extern vector vec_oneword;

vector vec_mul_mcq;
vector vec_numerical;
vector vec_single_C_mcq;
vector vec_tf;
vector vec_oneword;

extern int question_number;
int question_number;
int main(int argc, char **argv)
{
    if (argc != 5) //Verify if all the required arguments are passed
    {
        printf("Invalid usage of ExamTEX\nUsage : ExamTEX <question-bank> <sample-paper> <output-paper> <output-answers>\n");
        exit(0);
    }

    //allocate vectors for storing data
    vec_mul_mcq = allocate(NODE, 20);
    vec_numerical = allocate(NODE, 20);
    vec_single_C_mcq = allocate(NODE, 20);
    vec_tf = allocate(NODE, 20);
    vec_oneword = allocate(NODE, 20);
    question_number = 1;

    FILE *qb = fopen(argv[1], "r"); //Open question bank
    if (qb == NULL)
    {
        printf("Error : The file \"%s\" does not exist\n", argv[1]);
        exit(1);
    }

    readQuestionBank(qb); //Read and store questions
    printf("Question bank read successfully!\n");
    //Sort
    mergeSort(&vec_mul_mcq, 0, size(&vec_mul_mcq) - 1);
    mergeSort(&vec_numerical, 0, size(&vec_numerical) - 1);
    mergeSort(&vec_single_C_mcq, 0, size(&vec_single_C_mcq) - 1);
    mergeSort(&vec_tf, 0, size(&vec_tf) - 1);
    mergeSort(&vec_oneword, 0, size(&vec_oneword) - 1);

    FILE *sp = fopen(argv[2], "r"); //Open sample paper
    if (sp == NULL)
    {
        printf("Error : The file \"%s\" does not exist\n", argv[2]);
        exit(1);
    }

    FILE *op = fopen(argv[3], "w"); //Open output files
    FILE *oa = fopen(argv[4], "w");
    readSamplePaper(qb, sp, op, oa); //Read sample paper and print to output
    // fseek(qb,vec_single_C_mcq.u.nodeElems[0].id,SEEK_SET);
    // printSingleCorrect_MCQs(qb,op,oa);
    printf("Sample paper read successfully!\n");
    printf("Output has been written succesfully!\n");

    fclose(qb); //Close all files
    fclose(sp);
    fclose(op);
    fclose(oa);

    //delete vectors
    deletevector(&vec_mul_mcq);
    deletevector(&vec_numerical);
    deletevector(&vec_single_C_mcq);
    deletevector(&vec_tf);
    deletevector(&vec_oneword);

    return 0;
}