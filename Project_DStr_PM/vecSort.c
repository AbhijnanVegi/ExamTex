// **************************************************************************
// **********************MADE BY:: PRATYUSH MOHANTY**************************
// **************************************************************************

#include "vecSort.h"

int partition(Ptrto_ElemDataType data, int fIndex, int lIndex)
{
    int left = fIndex;
    int right = lIndex;

    int pivotIndex = fIndex;
    int pivotItem = data[pivotIndex].difficulty;

    while (left < right)
    {
        while (pivotItem < data[right].difficulty && left < right)
        {
            right--;
        }
        if (right == left)
        {
            break;
        }

        elemDataType temp1 = data[pivotIndex];
        data[pivotIndex] = data[right];
        data[right] = temp1;

        pivotIndex = right;
        pivotItem = data[pivotIndex].difficulty;

        while (pivotItem >= data[left].difficulty && left < right)
        {
            left++;
        }
        if (right == left)
        {
            break;
        }

        elemDataType temp2 = data[pivotIndex];
        data[pivotIndex] = data[left];
        data[left] = temp2;

        pivotIndex = left;
        pivotItem = data[pivotIndex].difficulty;
    }
    return pivotIndex;
}
void quickSort(Ptrto_ElemDataType data[], int fIndex, int lIndex)
{
    if (fIndex < lIndex)
    {
        int partIndx = partition(data, fIndex, lIndex);

        quickSort(data, fIndex, partIndx - 1);
        quickSort(data, partIndx + 1, lIndex);
    }
}
void sortVector(Ptrto_vector PtrV)
{
    quickSort(PtrV->data, 0, PtrV->size - 1);
}