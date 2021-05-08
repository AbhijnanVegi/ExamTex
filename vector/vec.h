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

#define NODE 0
#define CHARSTACK 1
#define STRING 2
typedef struct
{
    char ch;
    int lineno;
    int colno;
} charStack;

typedef struct
{
    float diff;
    int id; // line no
    float score;
} node; 


typedef union
{
    node *nodeElems;
    charStack *stackElems;
    char *string;
} vectorUnion;
typedef union
{
    charStack cs;
    node nd;
} parameterUnion;

typedef struct
{
    unsigned int dim, last, elementType;
    vectorUnion u;
} vector;

vector allocate(int elementType, unsigned int dim); //allocates memory for new vector

void push_back(vector *v, parameterUnion val); // pushes  an element in the end

parameterUnion back(vector v); // returns the element in the endif

parameterUnion front(vector v); //returns the element in the front

vector *reallocate(vector *v, int x); //reallocates memory from

void pop_back(vector *v); //pops the last element

unsigned int size(vector *v); // returns number of elements in the vector
                              
void add_string(vector *str, char c);

void cpy_string(vector *s, char* c);
char *return_string(vector *str);
void deletevector(vector * v);
#endif
