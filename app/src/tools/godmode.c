#include <lufrak.h>

static const char* banner[] = {
    "  ____           _   __   __           _  	  ",
    " / ___| ___   __| | |  \\/  | ___   __| | ___ ",
    "| |  _ / _ \\ / _` | | |\\/| |/ _ \\ / _` |/ _ \"",
    "| |_| | (_) | (_| | | |  | | (_) | (_| | __ /",
    " \\____|\\___/ \\__,_| |_|  |_|\\___/ \\__,_|\\___|",
};

static const Command command = { "cmd.exe", "/c mkdir \"C:\\GodMode.{ED7BA470-8E54-465E-825C-99712043E01C}\"" };
static int result = PROCESSING;
TOOL_MESSAGES()

TOOL_FUNC(Draw)
{
    char msgRunning[] = "Unlocking god mode. Please wait |";
    size_t len = sizeof(msgRunning) - 1;
    
    char chars[] = "|/-|-\\";
    size_t charsLen = sizeof(chars) - 1;
    
    int i = 0;

    while (result == PROCESSING)
    {
        (i < charsLen - 1) ? (i++) : (i = 0);

        msgRunning[len - 1] = chars[i];
        PrintMessage(banner, 5, msgRunning);

        Wait(500);
    }

    return NULL;
}

TOOL_FUNC(Run)
{
    result = (RunCommand(&command)) ? SUCCESS : FAILURE;

    return NULL;
}

DEFINE_TOOL(GodMode)
{
    RunTool(&Run, &Draw);
    PrintMessage(banner, 5, (result == SUCCESS) ? msgSuccess : msgFailure);

    getch();

    return;
}