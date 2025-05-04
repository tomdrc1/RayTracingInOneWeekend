#pragma once

#include <stdlib.h>
#include <time.h>

inline void randomInit()
{
	srand(time(NULL));
}

inline double randomDouble()
{
	return (double)rand() / (RAND_MAX + 1.0);
}