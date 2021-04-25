// **************************************************************************
// **********************MADE BY:: PRATYUSH MOHANTY**************************
// **************************************************************************

#include "vecPDS.h"

#include "vecPFun.h"

// **************************************************************************
// **********************_____SETUP____**************************************
// **************************************************************************

int vector_setup(Vector *vector, capacityType capacity, elemSizeType element_size, QtypeType Qtype)
{
    vector = malloc(sizeof(Vector));
    if (vector == NULL)
    {
        return ERROR;
    }

    vector->size = 0;
    vector->Qtype = Qtype;
    vector->capacity = capacity;
    vector->element_size = element_size;
    vector->data = malloc(vector->capacity * element_size);

    return vector->data == NULL ? ERROR : SUCCESS;
}

int mastervector_setup(masterVector *mVector, capacityType capacity)
{
    mVector = malloc(sizeof(masterVector));
    if (mVector == NULL)
    {
        return ERROR;
    }

    mVector->size = 0;
    mVector->capacity = capacity;
    mVector->VPtr = malloc(mVector->capacity * sizeof(Vector));

    return mVector->VPtr == NULL ? ERROR : SUCCESS;
}

// **************************************************************************
// **********************_____DESTROY____************************************
// **************************************************************************

int vector_destroy(Vector *vector)
{
    if (vector == NULL)
    {
        return ERROR;
    }
    free(vector->data);

    vector->size = 0;
    vector->data = NULL;

    return SUCCESS;
}

int mastervector_destroy(masterVector *mvector)
{
    if (mvector == NULL)
    {
        return ERROR;
    }
    free(mvector->VPtr);

    mvector->size = 0;
    mvector->VPtr = NULL;

    return SUCCESS;
}

// **************************************************************************
// **********************____INSERTION____***********************************
// **************************************************************************

int vector_push_back(Vector *vector, elemDataType element)
{
    if (vector != NULL)
    {
        if (vector->size == vector->capacity)
        {
            grow_vector(vector);
        }
        vector->data[vector->size] = element;
        ++vector->size;

        return SUCCESS;
    }
    return ERROR;
}

int vector_push_front(Vector *vector, elemDataType element)
{
    if (vector != NULL)
    {
        if (vector->size == vector->capacity)
        {
            grow_vector(vector);
        }
        for (int i = (vector->size - 1); i >= 0; i--)
        {
            vector->data[i + 1] = vector->data[i];
        }
        vector->data[0] = element;
        ++vector->size;

        return SUCCESS;
    }
    return ERROR;
}

// **************************************************************************
// **********************____DELETION____************************************
// **************************************************************************

int vector_pop_front(Vector *vector)
{
    if (vector != NULL)
    {
        for (int i = 0; i < vector->size - 1; i++)
        {
            vector->data[i] = vector->data[i + 1];
        }
        --vector->size;

        if (vector->size == vector->capacity / 2)
        {
            shrink_vector(vector);
        }
        return SUCCESS;
    }
    return ERROR;
}

int vector_pop_back(Vector *vector)
{
    if (vector != NULL)
    {
        --vector->size;

        if (vector->size == vector->capacity / 2)
        {
            shrink_vector(vector);
        }
        return SUCCESS;
    }
    return ERROR;
}

// **************************************************************************
// **********************____GROW AND SHRINK____*****************************
// **************************************************************************

void grow_vector(Vector *vector)
{
    int initCap = vector->capacity;
    vector->capacity = vector->capacity * 2;

    Ptrto_ElemDataType newData = malloc(vector->capacity * sizeof(elemDataType));

    for (int i = 0; i < initCap; i++)
    {
        newData[i] = vector->data[i];
    }

    free(vector->data);
    vector->data = newData;
}

void shrink_vector(Vector *vector)
{
    int initCap = vector->capacity;
    vector->capacity = vector->capacity / 2;

    Ptrto_ElemDataType newData = malloc(vector->capacity * sizeof(elemDataType));

    for (int i = 0; i < initCap; i++)
    {
        newData[i] = vector->data[i];
    }

    free(vector->data);
    vector->data = newData;
    ;
}