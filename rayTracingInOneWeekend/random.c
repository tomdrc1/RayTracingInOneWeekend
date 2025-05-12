#include "random.h"

void randomInit()
{
	srand(time(NULL));
}

double randomDouble()
{
	return (double)rand() / (RAND_MAX + 1.0);
}

double randomDoubleConfined(const double min, const double max)
{
	return min + (max - min) * randomDouble();
}
