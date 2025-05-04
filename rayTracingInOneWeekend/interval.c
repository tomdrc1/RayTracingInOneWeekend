#include "interval.h"

bool intervalSurrounds(const Interval* interval, const double x)
{
    return interval->min < x && x < interval->max;
}
