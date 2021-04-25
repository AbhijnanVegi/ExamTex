#include "vec.h"
#include <stdlib.h>
#include <stdio.h>
const vector VEC_UNDEFINED = {0, NULL};

vector allocate(unsigned int dim)
{
    vector ret;
    ret.dim = 2 * dim;
    ret.last = 0;
    ret.elems = (elementType *)malloc(dim * 2 * sizeof(elementType));
    return ret;
}
vector constructDefautVector(unsigned int dim, elementType val)
{
    vector ret = allocate(dim);
    for (int i = 0; i < dim; i++)
    {
        ret.elems[i] = val;
    }
    ret.last = dim;
    return ret;
}

vector constructEmptyVector(unsigned int dim)
{
    return constructDefautVector(dim, 0.0f);
}
vector NEWVector(int dim, ...)
{
    vector ret = allocate(dim);
    va_list list;
    va_start(list, dim);
    for (int i = 0; i < dim; i++)
        ret.elems[i] = va_arg(list, elementType);
    va_end(list);
    ret.last = dim;
    return ret;
}

void print(vector v)
{
    printf("[ ");
    for (int i = 0; i < v.last; i++)
    {
        printf("%0.2f", v.elems[i]);
        if (i < v.last - 1)
            printf(", ");
        else
            printf(" ");
    }
    printf("]\n");
}
void push_back(vector *v, elementType val)
{
    if (v->dim - v->last <= 1)
        v = reallocate(v, v->dim + 10);
    v->elems[v->last++] = val;
}
vector *reallocate(vector *v, int x)
{
    elementType *temp = v->elems;
    v->elems = (elementType *)realloc(v->elems, x * sizeof(elementType));
    v->dim = x;
    return v;
}
void pop_back(vector *v)
{
    v->last--;
}
elementType back(vector v)
{
    return v.elems[v.last - 1];
}
elementType front(vector v)
{
    return v.elems[0];
}
void addElems(vector *v, int numElemes, ...)
{
    if (v->dim <= v->last + numElemes)
        reallocate(v, v->last + numElemes + 5);
    va_list list;
    va_start(list, numElemes);
    for (int i = 0; i < numElemes; i++)
        v->elems[v->last + i] = va_arg(list, elementType);
    v->last += numElemes;
    va_end(list);
}
unsigned int size(vector *v)
{
    return v->last;
}