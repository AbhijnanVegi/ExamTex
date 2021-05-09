#include <stdio.h>
#include <stdlib.h>
#include "binary_search.h"
#include "vec1.h"

int binary_ub_search(vector *v, double upper_limit) //// This code returns the position of the largest element smaller than the upper bound
{
    int lb = 0;
    int ub = v->last - 1;
    int mid;
    double position = v->last - 1;

    while (lb <= ub)
    {
        mid = (lb + ub) / 2;

        if (upper_limit < v->u.nodeElems[mid].diff)
        {
            position = mid;
            ub = mid - 1;
        }
        else
        {
            lb = mid + 1;
        }
    }

    return position;
}

int binary_lb_search(vector *v, double lower_limit) /// This func gives the position of smallest elemnt greater than the lower bound
{
    int lb = 0;
    int ub = v->last - 1;
    int mid;
    double position = v->last - 1;

    while (lb <= ub)
    {
        mid = (lb + ub) / 2;

        if (lower_limit >= v->u.nodeElems[mid].diff)
        {

            lb = mid + 1;
        }
        else
        {
            ub = mid - 1;
            position = ub;
        }
    }

    return position;
}
