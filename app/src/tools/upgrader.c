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

static void* Draw(void* arg)
{
    char msgRunning[] = "Running upgrader. Please wait |";
    size_t msgLen = strlen(msgRunning);

    char chars[] = "|/-|-\\";
    size_t charsLen = strlen(chars);
    
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

static void* Run(void* arg)
{
    result = (RunCommand(&command)) ? SUCCESS : FAILURE;

    return NULL;
}

DEFINE_TOOL(Upgrader)
{
    command.command = "winget";
    command.args = "upgrade --all";

    pthread_t runThread;
    pthread_t drawThread;

    pthread_create(&runThread, NULL, &Run, NULL);
    pthread_create(&drawThread, NULL, &Draw, NULL);

    pthread_join(runThread, NULL);
    pthread_join(drawThread, NULL);

    PrintMessage(banner, 6, (result == SUCCESS) ? msgSuccess : msgFailure);

    getch();

	return;
}