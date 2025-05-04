#pragma once

#include <stdlib.h>
#include <time.h>

void randomInit()
{
	srand(time(NULL));
}

double randomDouble()
{
	return (double)rand() / (RAND_MAX + 1.0);
}