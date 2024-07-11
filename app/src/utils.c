#include <utils.h>

#define GET_CONSOLE() HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE)

void PrintAt(SHORT x, SHORT y, const char* fmt, ...)
{
    GET_CONSOLE();

    va_list args;

    SetConsoleCursorPosition(console, (COORD){x, y});

    va_start(args, fmt);
    vprintf_s(fmt, args);
    va_end(args);

    return;
}

void SetAttributes(WORD attributes)
{
    GET_CONSOLE();

    SetConsoleTextAttribute(console, attributes);
    return;
}

COORD GetConsoleSize()
{
    GET_CONSOLE();
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo = {0};

    return (GetConsoleScreenBufferInfo(console, &consoleInfo)) ? consoleInfo.dwSize : (COORD){0};
}