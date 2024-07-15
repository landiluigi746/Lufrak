#include <lufrak.h>

static const char* banner[] = {
    " ____             _                                  _   ____                       _ _         ",
    "| __ )  __ _  ___| | ___   _ _ __     __ _ _ __   __| | / ___|  ___  ___ _   _ _ __(_) |_ _   _ ",
    "|  _ \\ / _` |/ __| |/ / | | | '_ \\   / _` | '_ \\ / _` | \\___ \\ / _ \\/ __| | | | '__| | __| | | |",
    "| |_) | (_| | (__| <  | |_| | |_) | | (_| | | | | (_| |  ___) |  __/ (__| |_| | |  | | |_| |_| |",
    "|____/ \\__,_|\\___|_|\\_\\\\__,_| .__/   \\__,_|_| |_|\\__,_| |____/ \\___|\\___|\\__,_|_|  |_|\\__|\\__, |",
    "                            |_|                                                           |___/ "
};

static const Command commands[] = {
    { "wmic.exe", "/Namespace:\\\\root\\default Path SystemRestore Call CreateRestorePoint \"Lufrak\", 100, 7" },
    { "C:\\Program Files\\Windows Defender\\MpCmdRun.exe", "-Scan -ScanType 1" },
    { "C:\\Program Files\\Windows Defender\\MpCmdRun.exe", "-Scan -ScanType 2" }
};

static const char* texts[] = {
    "Create a Windows Restore Point",
    "Run a rapid virus scan",
    "Run a complete virus scan"
};

static const size_t numCommands = min(sizeof(commands) / sizeof(Command), sizeof(texts) / sizeof(char*));

static const char* menuCommands = "Use up/down arrow keys to move through the menu. Press enter to select or m to return to menu";

static int selected = 0;
static int result = PROCESSING;
TOOL_MESSAGES()

static bool GetSelection(void)
{
    attr_t hoveredAttr = A_BOLD | COLOR_PAIR(1);

    int key = 0;
    int i;

    do {
        DrawBanner(banner, 6);

        for (i = 0; i < numCommands; i++)
        {
            if (i == selected)
                attron(hoveredAttr);

            mvprintw(LINES / 2 + i, COLS / 2 - strlen(texts[i]) / 2, texts[i]);
            attroff(hoveredAttr);
        }

        attron(hoveredAttr);
        mvprintw(LINES - 3, COLS / 2 - strlen(menuCommands) / 2, menuCommands);
        attroff(hoveredAttr);

        key = tolower(getch());

        switch (key)
        {
            case KEY_UP:    (selected == 0) ? selected = numCommands - 1 : --selected;   break;
            case KEY_DOWN:  (selected == numCommands - 1) ? selected = 0 : ++selected;   break;
            case 'm':       return false;
        }
    } while (key != '\n');

    return true;
}

TOOL_FUNC(Draw)
{
    char msgRunning[] = "Running the selected option. Please wait |";
    size_t msgLen = sizeof(msgRunning) - 1;

    char chars[] = "|/-|-\\";
    size_t charsLen = sizeof(chars) - 1;
    
    int i = 0;

    while (result == PROCESSING)
    {
        (i < charsLen - 1) ? (i++) : (i = 0);

        msgRunning[msgLen - 1] = chars[i];
        PrintMessage(banner, 6, msgRunning);

        Wait(500);
    }

    return NULL;
}

TOOL_FUNC(Run)
{
    result = RunCommand(&commands[selected]) ? SUCCESS : FAILURE;

    return NULL;
}

DEFINE_TOOL(BackupAndSecurity)
{
    if(GetSelection())
    {
        RunTool(&Run, &Draw);
        PrintMessage(banner, 6, (result == SUCCESS) ? msgSuccess : msgFailure);

        getch();
    }

    return;
}