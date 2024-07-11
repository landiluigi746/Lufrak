#ifndef LUFRAK_H
#define LUFRAK_H

#include <Windows.h>
#include <pthread.h>

typedef struct
{
    LPCSTR command;
    LPCSTR args; 
} Command;

#endif // !LUFRAK_H