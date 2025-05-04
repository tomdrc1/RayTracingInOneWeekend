#include "interval.h"

bool intervalSurrounds(const Interval* interval, const double x)
{
    return interval->min < x && x < interval->max;
}

double intervalClamp(const Interval* interval, const double x)
{
    if (x < interval->min)
    {
        return interval->min;
    }
    else if (x > interval->max)
    {
        return interval->max
    }

    return x;
}
