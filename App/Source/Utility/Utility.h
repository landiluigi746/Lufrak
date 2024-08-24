#ifndef LUFRAK_UTILS_H__
#define LUFRAK_UTILS_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int _Assert(bool exprTest, const char* exprStr, const char* msg, const char* file, unsigned line);
void* SafeMalloc(size_t size);

#define ASSERT(expr, msg) (_Assert(expr, #expr, msg, __FILE__, __LINE__))

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

#endif // !LUFRAK_UTILS_H__
