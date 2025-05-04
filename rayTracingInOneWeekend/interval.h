#pragma once

#include <stdbool.h>

typedef struct Interval
{
	double min;
	double max;
} Interval;


bool intervalSurrounds(const Interval* interval, const double x);