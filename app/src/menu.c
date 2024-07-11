#include <lufrak.h>

static const char* banner[] = {
    " _            __           _    ",
    "| |          / _|         | |   ",
    "| |    _   _| |_ _ __ __ _| | __",
    "| |   | | | |  _| '__/ _` | |/ /",
    "| |___| |_| | | | | | (_| |   < ",
    "|______\\__,_|_| |_|  \\__,_|_|\\_\\",
};

static const char* menuTexts[] = {
    "Upgrader",
    "Installer",
    "Optimizer",
    "Backup and Security",
    "Display system information",
    "Unlock God Mode",
    "Exit"
};

static const char* commands = "Use up/down arrow keys to move through the menu. Press enter to select";
static const size_t numMenuTexts = sizeof(menuTexts) / sizeof(char*);

size_t endMenuIdx = numMenuTexts - 1;

int Menu(void)
{
    int hovered = 0;
    int i;
    int key;

    attr_t hoveredAttr = A_BOLD | COLOR_PAIR(HOVER);

    do {
        DrawBanner(banner, 6);

        for (i = 0; i < numMenuTexts; i++)
        {
            if (i == hovered)
                attron(hoveredAttr);

            mvprintw(LINES / 2 - 3 + i * 2, COLS / 2 - strlen(menuTexts[i]) / 2, menuTexts[i]);
            attroff(hoveredAttr);
        }

        attron(hoveredAttr);
        mvprintw(LINES - 3, COLS / 2 - strlen(commands) / 2, commands);
        attroff(hoveredAttr);

        key = tolower(getch());

        switch(key)
        {
            case KEY_UP:     (hovered == 0) ? hovered = numMenuTexts - 1 : --hovered; break;
            case KEY_DOWN:   (hovered == numMenuTexts - 1) ? hovered = 0 : ++hovered; break;
        }
    } while (key != '\n');

    return hovered;
}