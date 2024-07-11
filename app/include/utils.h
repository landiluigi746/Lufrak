#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <windows.h>

#define NORMAL (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)
#define HOVER (BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_INTENSITY)
#define SELECTED (0x7 | 0x30)

void PrintAt(SHORT x, SHORT y, const char* fmt, ...);
void SetAttributes(WORD attributes);
COORD GetConsoleSize(void);

#endif // !UTILS_H