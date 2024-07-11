#include <utils.h>

int main(void)
{
    SetAttributes(SELECTED);
    PrintAt(2, 2, "Ciao %d", 2);
    SetAttributes(NORMAL);
    PrintAt(4, 4, "Ciao %d", 3);

    getchar();

    return 0;
}