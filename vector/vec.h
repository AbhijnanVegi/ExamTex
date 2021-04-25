/**************************************************************************************
--------------------------------Vector Library-----------------------------------------
Made by - Shreyansh 
Functions include basic operations for dynamic arrays
                                                                  
***************************************************************************************/

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!NOTE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Please use double instead of float as due to some c shenanigans having to do with passing variable
// argument as parameter

#ifndef __VEC_H
#define __VEC_H
#include <stdarg.h>
#define elementType double



#define NUMARGS(...) (sizeof((elementType[]){0.0f, ##__VA_ARGS__}) / sizeof(elementType) - 1)
#define newVector(...) NEWVector(NUMARGS(__VA_ARGS__), ##__VA_ARGS__)
//#define add(vector *v, ...) addElems(v, NUMARGS(__VA_ARGS__), ##__VA_ARGS__)
typedef struct
{
    unsigned int dim, last;
    elementType *elems;
} vector;
extern const vector VEC_UNDEFINED;

vector NEWVector(int numArgs, ...); //makes new vector helper function for newVector

vector allocate(unsigned int dim); //allocates memory for new vector

vector constructDefautVector(unsigned int dim, elementType val); // makes a vector with all elems
//intialised to a particular value

vector constructEmptyVector(unsigned int dim); //insitialises a vector with all zeros

void print(vector v); // prints the vector

void push_back(vector *v, elementType val); // pushes  an element in the end

elementType back(vector v); // returns the element in the endif

elementType front(vector v); //returns the element in the front

vector *reallocate(vector *v, int x); //reallocates memory from

void pop_back(vector *v); //pops the last element

void addElems(vector *v, int numElemes, ...); //add arbitary number of elements in the endif

unsigned int size(vector *v); // returns number of elements in the vector

#endif


