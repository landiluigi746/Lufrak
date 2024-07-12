#include <lufrak.h>

#define START_Y LINES / 2 + 3

static const char* banner[] = {
    " ____            _                   ___        __                            _   _             ",
    "/ ___| _   _ ___| |_ ___ _ __ ___   |_ _|_ __  / _| ___  _ __ _ __ ___   __ _| |_(_) ___  _ __  ",
    "\\___ \\| | | / __| __/ _ \\ '_ ` _ \\   | || '_ \\| |_ / _ \\| '__| '_ ` _ \\ / _` | __| |/ _ \\| '_ \\ ",
    " ___) | |_| \\__ \\ ||  __/ | | | | |  | || | | |  _| (_) | |  | | | | | | (_| | |_| | (_) | | | |",
    "|____/ \\__, |___/\\__\\___|_| |_| |_| |___|_| |_|_|  \\___/|_|  |_| |_| |_|\\__,_|\\__|_|\\___/|_| |_|",
    "       |___/                                                                                    "
};

static SystemInformation sysInfo = { 0 };

static const char* texts[] = {
    "Processor",
    "Architecture",
    "Logical Processors",
    "Total RAM"
};

static const size_t numTexts = sizeof(texts) / sizeof(char*);

DEFINE_TOOL(SystemInfo)
{
    int i;
    GetSystemInformation(&sysInfo);
    
    DrawBanner(banner, 6);
    for(i = 0; i < numTexts; i++)
        mvprintw(START_Y + i, COLS / 2 - 40, texts[i]);
    
    mvprintw(START_Y, COLS / 2 + 10, sysInfo.processorName);
    mvprintw(START_Y + 1, COLS / 2 + 10, sysInfo.processorArchitecture);
    mvprintw(START_Y + 2, COLS / 2 + 10, "%lu", sysInfo.wSysInfo.dwNumberOfProcessors);
    mvprintw(START_Y + 3, COLS / 2 + 10, "%.2lf GB", (double)sysInfo.wMemInfo.ullTotalPhys / (1024 * 1024 * 1024));

    free(sysInfo.processorName);

    getch();

    return;
}