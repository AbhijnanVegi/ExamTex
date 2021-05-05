#include "vec.h"
#include <stdlib.h>
#include <stdio.h>

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