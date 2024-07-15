#include <lufrak.h>

static const char* banner[] = {
	"  ___        _   _           _               ",
	" / _ \\ _ __ | |_(_)_ __ ___ (_)_________ __  ",
	"| | | | '_ \\| __| | '_ ` _ \\| |_  / _ \\ '__| ",
	"| |_| | |_) | |_| | | | | | | |/ /  __/ |    ",
	" \\___/| .__/ \\__|_|_| |_| |_|_/___\\___|_|    ",
	"	    |_|                                     "
};

static const Command commands[] = {
    { "ipconfig", "/flushdns" },
    { "cleanmgr", "/sagerun:1" },
    { "rmdir", "/s /q \"%LocalAppData%\\Google\\Chrome\\User Data\\Default\\Cache\"" },
    { "net", "stop wuauserv" },
    { "rmdir", "/s /q %windir%\\SoftwareDistribution" },
    { "net", "start wuauserv" }
};

static const char* warning = "Run the optimizer with no other programs open. Press 'm' to return to the menu or any other key to continue.";

static const size_t numCommands = sizeof(commands) / sizeof(Command);
static int result = PROCESSING;
TOOL_MESSAGES()

TOOL_FUNC(Draw)
{
    char msgRunning[] = "Running optimizer. Please wait |";
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
    result = (RunCommands(commands, numCommands)) ? SUCCESS : FAILURE;

    return NULL;
}

DEFINE_TOOL(Optimizer)
{
    PrintMessage(banner, 6, warning);
    
    if(tolower(getch()) == 'm')
        return;

    RunTool(&Run, &Draw);
    PrintMessage(banner, 6, (result == SUCCESS) ? msgSuccess : msgFailure);

    getch();

    return;
}