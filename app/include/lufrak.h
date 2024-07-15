#ifndef LUFRAK_H
#define LUFRAK_H

#include <utils.h>
#include <intrin.h>
#include <Psapi.h>
#include <Shellapi.h>
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
    bool selected;
} Package;

typedef struct
{
    SYSTEM_INFO wSysInfo;
    MEMORYSTATUSEX wMemInfo;
    char* processorName;
    char* processorArchitecture;
} SystemInformation;

#define DEFINE_TOOL(name) void name(void)
#define GET_TOOL(name) &name

#define PROCESSING 0
#define SUCCESS 1
#define FAILURE -1

#define TOOL_MESSAGES() \
	static const char msgSuccess[] = "Done! Press any key to return to menu."; \
	static const char msgFailure[] = "Fail! An error has occurred! Press any key to return to menu.";

#define TOOL_FUNC(name) static void* name(void* arg)

typedef void (*Tool)(void);
typedef void* (*ToolFuncPtr)(void*);

extern size_t endMenuIdx;

void InitApp(void);
void RunTool(ToolFuncPtr runFunc, ToolFuncPtr drawFunc);
bool RunCommand(const Command* command);
bool RunCommands(const Command* commands, size_t numCommands);
bool InstallPackage(const Package* package);
void GetSystemInformation(SystemInformation* sysInfo);

int Menu(void);

DEFINE_TOOL(Upgrader);
DEFINE_TOOL(Installer);
DEFINE_TOOL(Optimizer);
DEFINE_TOOL(BackupAndSecurity);
DEFINE_TOOL(SystemInfo);
DEFINE_TOOL(GodMode);

#endif // !LUFRAK_H