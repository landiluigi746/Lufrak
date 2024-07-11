#include <utils.h>

void DieIf(bool test)
{
    if(test)
    {
        endwin();
        exit(EXIT_FAILURE);
    }
}

void* SafeMalloc(size_t size)
{
    void* ptr = malloc(size);
    DieIf(ptr == NULL);
    return ptr;
}

void Wait(clock_t milliseconds)
{
    clock_t start = clock();
    while(clock() - start < milliseconds);
    return;
}

void ClearScreen(void)
{
    clear();
    box(stdscr, 0, 0);
    refresh();

    return;
}

void DrawBanner(const char* banner[], int numLines)
{
    int i;

    ClearScreen();

    mvhline(10, 1, 0, COLS - 2);

    for(i = 0; i < numLines; i++)
        mvprintw(2 + i, COLS / 2 - strlen(banner[i]) / 2, banner[i]);

    refresh();
    
    return;
}

void PrintMessage(const char* banner[], int numLines, const char* message)
{
    DrawBanner(banner, numLines);
    mvprintw(LINES / 2 + 5, COLS / 2 - strlen(message) / 2, message);
    refresh();

    return;
}