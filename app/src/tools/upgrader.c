#include <lufrak.h>

static const char* banner[] = {
    " _   _                           _           ",
    "| | | |_ __   __ _ _ __ __ _  __| | ___ _ __ ",
    "| | | | '_ \\ / _` | '__/ _` |/ _` |/ _ \\ '__|",
    "| |_| | |_) | (_| | | | (_| | (_| |  __/ |   ",
    " \\___/| .__/ \\__, |_|  \\__,_|\\__,_|\\___|_|   ",
    "      |_|    |___/                           "
};

static Command command = { 0 };
static int result = PROCESSING;
TOOL_MESSAGES()

TOOL_FUNC(Draw)
{
    char msgRunning[] = "Running upgrader. Please wait |";
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
    result = (RunCommand(&command)) ? SUCCESS : FAILURE;

    return NULL;
}

DEFINE_TOOL(Upgrader)
{
    command.command = "winget";
    command.args = "upgrade --all";

    RunTool(&Run, &Draw);
    PrintMessage(banner, 6, (result == SUCCESS) ? msgSuccess : msgFailure);

    getch();

	return;
}