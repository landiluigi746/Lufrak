#ifndef UTILS_H
#define UTILS_H

#include <Windows.h>
#include <curses.h>
#include <time.h>

#define HOVER 1
#define SELECTED 2

void DieIf(bool test);
void* SafeMalloc(size_t size);
void Wait(clock_t milliseconds);
void ClearScreen();
void DrawBanner(const char* banner[], int numLines);
void PrintMessage(const char* banner[], int numLines, const char* message);

#endif // !UTILS_H