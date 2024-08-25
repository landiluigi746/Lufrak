#ifndef LUFRAK_INTERNAL_H__
#define LUFRAK_INTERNAL_H__

#include "Utility.h"

#define WIN32_LEAN_AND_MEAN
#if defined(_WIN32)
#define WIN32
#endif
#if defined(_WIN64)
#define WIN64
#define _AMD64_
#undef _X86_
#else
#undef _AMD64_
#define _X86_
#endif

#include <minwindef.h>
#include <sysinfoapi.h>

typedef enum
{
	FAILURE = -1,
	PROCESSING = 0,
	SUCCESS = 1
} ExecutionStatus;

typedef enum
{
	CMD_COMMAND = 1,
	WINGET_PACKAGE
} LufrakCommandType;

typedef struct
{
	LufrakCommandType type;
	const char* displayName;

	union
	{
		struct
		{
			const char* wingetID;
			bool selected;
		};

		struct
		{
			char* command;
			char* args;
		};
	};
} LufrakCommand;

typedef struct
{
	SYSTEM_INFO sysInfo;
	MEMORYSTATUSEX memInfo;
	char processorName[49];
	const char* processorArchitecture;
} SystemInformation;

typedef LPTHREAD_START_ROUTINE LufrakToolRunFuncPtr;
typedef void (*LufrakToolDrawFuncPtr)(void);

void LufrakInternalInit(void);
void LufrakInternalClose(void);

bool RunLufrakCommand(const LufrakCommand* command);
bool RunLufrakCommands(const LufrakCommand* commands, size_t numCommands);

void RunLufrakTool(LufrakToolRunFuncPtr runFunc, LufrakToolDrawFuncPtr drawFunc);

#define TOOL_FUNC(name) static DWORD WINAPI name(LPVOID lpData)
#define TOOL_RUN_FUNC() TOOL_FUNC(Run)
#define TOOL_DRAW_FUNC() static void Draw(void)
#define RUN_TOOL() RunLufrakTool(&Run, &Draw)

SystemInformation GetSystemInformation(void);

#endif // !LUFRAK_INTERNAL_H__
