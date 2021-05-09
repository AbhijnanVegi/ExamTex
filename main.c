#include <stdio.h>
#include <stdlib.h>
#include "vector/vec.h"
#include "Utils/cleanText.h"
#include "Utils/lineNumber.h"
#include "Utils/parsers.h"
#include "Utils/readFile.h"


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

int main(int argc, char** argv)
{
    if (argc!=5)//Verify if all the required arguments are passed
    {
        printf("Invalid usage of ExamTEX\nUsage : ExamTEX <question-bank> <sample-paper> <output-paper> <output-answers>\n");
        exit(0);
    }


    //allocate vectors for storing data
    vec_mul_mcq = allocate(NODE,20);
    vec_numerical = allocate(NODE,20);
    vec_single_C_mcq = allocate(NODE,20);
    vec_tf = allocate(NODE, 20);
    vec_oneword = allocate(NODE, 20);

    FILE* qb = fopen(argv[1],"r");//Open question bank
    if (qb == NULL)
    {
        printf("Error : The file \"%s\" does not exist\n",argv[1]);
        exit(1);
    }

    readQuestionBank(qb);//Read and store questions
    printf("Question bank read successfully\n");
    //Sort

    FILE* sp = fopen(argv[2],"r");//Open sample paper
    if (qb == NULL)
    {
        printf("Error : The file \"%s\" does not exist\n",argv[2]);
        exit(1);
    }

    FILE* op = fopen(argv[3],"w");//Open output files
    FILE* oa = fopen(argv[4],"w");
    readSamplePaper(sp,op,oa);//Read sample paper and print to output

    printf("Sample paper read successfully\n");
    printf("Output has been written succesfully\n");

    fclose(qb);//Close all files
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