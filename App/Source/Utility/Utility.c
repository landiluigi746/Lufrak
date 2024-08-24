#include "Utility.h"

int _Assert(bool exprTest, const char* exprStr, const char* msg, const char* file, unsigned line)
{
	if (!exprTest)
	{
		fprintf_s(stderr, "Assertion failed: %s\nError message: %s\nFile: %s\nLine:%u\n", exprStr, (msg != NULL) ? msg : "", file, line);
		abort();
	}

	return 1;
}

void* SafeMalloc(size_t size)
{
	void* ptr = malloc(size);
	ASSERT(ptr != NULL, "Error while allocating memory!");
	return ptr;
}