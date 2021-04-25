// **************************************************************************
// **********************MADE BY:: PRATYUSH MOHANTY**************************
// **************************************************************************

#ifndef _H__VECTORDS__H_

#define _H__VECTORDS__H_

// **************************************************************************
// **********************_____HEADER FILES____*******************************
// **************************************************************************

#include <stdio.h>

#include <stdlib.h>

#include <assert.h>

#include <stdbool.h>

// **************************************************************************

#define ERROR -1

#define SUCCESS 0

// **************************************************************************

#define scoreType int

#define tokenType long int

#define difficultyType double

// **************************************************************************

#define sizeType int

#define QtypeType int

#define capacityType int

#define elemSizeType int

#define elemType long int

#define Ptrto_ElemDataType elemDataType *

#define Ptrto_vector Vector *

// **************************************************************************
// *******************_____DATA STRUCTURES____*******************************
// **************************************************************************

typedef struct elemDataType
{
    scoreType score;

    difficultyType difficulty;

    tokenType tokenNo;

} elemDataType;

typedef struct Vector
{
    sizeType size;

    capacityType capacity;

    elemSizeType element_size;

    QtypeType Qtype;

    Ptrto_ElemDataType data;

} Vector;

typedef struct masterVector
{
    sizeType size;

    capacityType capacity;

    Ptrto_vector VPtr;

} masterVector;

#endif