//////////This can be used for sorting of difficulties stored in vectors
///////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include "vec1.h" //// contains vectors written by Shreyansh

void merge(vector *vec, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    vector L;
    vector R;

    L = allocate(NODE, n1);
    R = allocate(NODE, n2);

    for (i = 0; i < n1; i++)
    {
        L.u.nodeElems[i] = vec->u.nodeElems[l + i];
    }
    for (j = 0; j < n2; j++)
    {
        R.u.nodeElems[j] = vec->u.nodeElems[m + 1 + j];
    }

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L.u.nodeElems[i].diff <= R.u.nodeElems[j].diff)
        {
            vec->u.nodeElems[k].diff = L.u.nodeElems[i].diff;
            vec->u.nodeElems[k].id = L.u.nodeElems[i].id;
            vec->u.nodeElems[k].score = L.u.nodeElems[i].score;
            i++;
        }
        else
        {
            vec->u.nodeElems[k].diff = R.u.nodeElems[j].diff;
            vec->u.nodeElems[k].id = R.u.nodeElems[j].id;
            vec->u.nodeElems[k].score = R.u.nodeElems[j].score;
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        vec->u.nodeElems[k].diff = L.u.nodeElems[i].diff;
        vec->u.nodeElems[k].id = L.u.nodeElems[i].id;
        vec->u.nodeElems[k].score = L.u.nodeElems[i].score;

        i++;
        k++;
    }

    while (j < n2)
    {
        vec->u.nodeElems[k].diff = R.u.nodeElems[j].diff;
        vec->u.nodeElems[k].id = R.u.nodeElems[j].id;
        vec->u.nodeElems[k].score = R.u.nodeElems[j].score;
        j++;
        k++;
    }
}

void mergeSort(vector *vec, int l, int r)
{
    if (l < r)
    {

        int m = l + (r - l) / 2;

        mergeSort(vec, l, m);
        mergeSort(vec, m + 1, r);

        merge(vec, l, m, r);
    }
}

/*int main()
{

    vector V;
    float n = 0, m = 0, p = 0;

    V = allocate(NODE, 5);

    for (int i = 0; i < 5; i++)
    {
        parameterUnion dummy;
        scanf("%f %f %f", &n, &m, &p);
        dummy.nd.diff = n;
        dummy.nd.score = m;
        dummy.nd.id = p;
        push_back(&V, dummy);
    }

    mergeSort(&V, 0, 4);

    for (int i = 0; i < 5; i++)
    {

        float n1 = V.u.nodeElems[i].diff;
        float m1 = V.u.nodeElems[i].score;
        float p1 = V.u.nodeElems[i].id;

        printf("%f %f %f\n", n1, m1, p1);
    }
}*/
