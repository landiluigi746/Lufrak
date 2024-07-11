#ifndef LUFRAK_H
#define LUFRAK_H

#include <utils.h>
#include <shellapi.h>
#include <pthread.h>

#define STR_SIZE 256

typedef struct
{
    char* command;
    char* args;
} Command;

typedef struct
{
	char* displayName;
    char* wingetID;
} Package;

#define DEFINE_TOOL(name) void name(void)
#define GET_TOOL(name) &name

#define PROCESSING 0
#define SUCCESS 1
#define FAILURE -1

#define TOOL_MESSAGES() \
	static const char msgSuccess[] = "Done! Press any key to return to menu."; \
	static const char msgFailure[] = "Fail! An error has occurred! Press any key to return to menu.";

typedef void (*Tool)(void);

extern size_t endMenuIdx;

void InitApp(void);
bool RunCommand(const Command* command);
bool RunCommands(const Command* commands, size_t numCommands);
bool InstallPackage(const Package* package);

int Menu(void);

DEFINE_TOOL(Upgrader);
DEFINE_TOOL(Installer);

#endif // !LUFRAK_H