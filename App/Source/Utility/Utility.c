#include "Utility.h"

void* SafeMalloc(size_t size)
{
	void* ptr = malloc(size);
	assert(ptr != NULL && "Error while allocating memory!\n");
	return ptr;
}