// **************************************************************************
// **********************MADE BY:: PRATYUSH MOHANTY**************************
// **************************************************************************

#ifndef _H__VECTORSORT__H_

#define _H__VECTORSORT_H_

#include "vecPDS.h"

// **************************************************************************
// *************************_____FUNCTIONS____*******************************
// **************************************************************************

int partition(Ptrto_ElemDataType data, int fIndex, int lIndex);

void quickSort(Ptrto_ElemDataType data[], int fIndex, int lIndex);

void sortVector(Ptrto_vector PtrV);

#endif