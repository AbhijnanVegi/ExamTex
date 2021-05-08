#include "vec.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
vector allocate(int elementType, unsigned int dim)
{
    vector ret;
    ret.elementType = elementType;
    ret.dim = dim;
    ret.last = 0;
    if (elementType == CHARSTACK)
    {
        ret.u.stackElems = (charStack *)malloc(dim * sizeof(charStack));
    }
    else if (elementType == NODE)
    {
        ret.u.nodeElems = (node *)malloc(dim * sizeof(node));
    }
    else if (elementType == STRING)
    {
        ret.u.string = (char *)malloc(dim * sizeof(char));
    }
    return ret;
}

void push_back(vector *v, parameterUnion val)
{
    if (v->dim - v->last <= 1)
        v = reallocate(v, v->dim + 10);
    if (v->elementType == CHARSTACK)
    {
        v->u.stackElems[v->last++] = val.cs;
    }
    else if (v->elementType == NODE)
    {

        v->u.nodeElems[v->last++] = val.nd;
    }
}
vector *reallocate(vector *v, int x)
{
    if (v->elementType == CHARSTACK)
    {
        // charStack *temp = v->u.stackElems;
        v->u.stackElems = (charStack *)realloc(v->u.stackElems, x * sizeof(charStack));
        v->dim = x;
        return v;
    }
    else if (v->elementType == NODE)
    {
        v->u.nodeElems = (node *)realloc(v->u.nodeElems, x * sizeof(node));
        v->dim = x;
        return v;
    }
    else if (v->elementType == STRING)
    {
        v->u.string = (char *)realloc(v->u.string, x);
        v->dim = x;
        return v;
    }
}
void pop_back(vector *v)
{
    v->last--;
}
parameterUnion back(vector v)
{
    parameterUnion temp;
    if (v.elementType == CHARSTACK)
    {
        temp.cs = v.u.stackElems[v.last - 1];
        return temp;
    }
    else if (v.elementType == NODE)
    {
        temp.nd = v.u.nodeElems[v.last - 1];
        return temp;
    }
}
parameterUnion front(vector v)
{
    parameterUnion temp;
    if (v.elementType == CHARSTACK)
    {
        temp.cs = v.u.stackElems[0];
        return temp;
    }
    else if (v.elementType == NODE)
    {
        temp.nd = v.u.nodeElems[0];
        return temp;
    }
}

unsigned int size(vector *v)
{
    return v->last;
}

void add_string(vector *v, char c)
{
    if (v->elementType == STRING)
    {
        if (v->dim <= v->last + 2 + 1)
            v = reallocate(v, v->dim + 2 + 1);
        v->u.string[v->last++] = c;
    }
}

void cpy_string(vector *v, char *c)
{
    if (v->elementType == STRING)
    {
        if (v->dim <= strlen(c) + 1)
            v = reallocate(v, strlen(c) + 10);
        strcpy(&v->u.string[0], c);
        v->last += strlen(c);
    }
}
char *return_string(vector *str)
{
    if (str->elementType == STRING)
        return &str->u.string[0];
}
void deletevector(vector *v)
{
    if (v->elementType == CHARSTACK)
    {
        free(v->u.stackElems);
    }
    else if (v->elementType == NODE)
    {
        free(v->u.nodeElems);
    }
    else if (v->elementType == STRING)
    {
        free(v->u.string);
    }
}
