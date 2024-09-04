#include "LufrakInternal.h"

#include <intrin.h>
#include <Objbase.h>
#include <Shellapi.h>

#define INTERNAL_BUF_SIZE 256

void LufrakInternalInit(void)
{	
	ASSERT(SUCCEEDED(CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE)), "Error while initializing COM library");

	return;
}

void LufrakInternalClose(void)
{
	CoUninitialize();

	return;
}

static bool RunCmdCommand(const LufrakCommand* cmd)
{
	ASSERT(cmd != NULL, "Null pointer caught by RunCmdCommand()");
	ASSERT(cmd->type == CMD_COMMAND, "Non cmd command caught by RunCmdCommand()");
	ASSERT(cmd->command != NULL && cmd->args != NULL, "No command/args provided to cmd passed by RunCmdCommand()");

	SHELLEXECUTEINFOA sei = { 0 };
	char args[INTERNAL_BUF_SIZE] = { 0 };

	sprintf_s(args, INTERNAL_BUF_SIZE, "/c %s %s", cmd->command, cmd->args);

	sei.cbSize = sizeof(sei);
	sei.fMask = SEE_MASK_NOCLOSEPROCESS;
	sei.lpVerb = "runas";
	sei.lpFile = "cmd.exe";
	sei.lpParameters = args;
	sei.nShow = SW_SHOW;

	if (ShellExecuteExA(&sei))
	{
		WaitForSingleObject(sei.hProcess, INFINITE);
		CloseHandle(sei.hProcess);
		return true;
	}
	else
		return false;
}

static bool InstallPackage(const LufrakCommand* package)
{
	ASSERT(package != NULL, "Null pointer caught by InstallPackage()");
	ASSERT(package->type == WINGET_PACKAGE, "Non winget package caught by InstallPackage()");

	LufrakCommand command = { 0 };

	command.type = CMD_COMMAND;
	command.command = "winget";
	command.args = SafeMalloc(sizeof(char) * INTERNAL_BUF_SIZE);

	sprintf_s(command.args, INTERNAL_BUF_SIZE, "install -e --id %s", package->wingetID);

	bool result = RunCmdCommand(&command);

	free(command.args);

	return result;
}

bool RunLufrakCommand(const LufrakCommand* command)
{
	ASSERT(command != NULL, "Null pointer caught by RunLufrakCommand()");

	bool result = false;

	switch (command->type)
	{
	case CMD_COMMAND: result = RunCmdCommand(command); break;
	case WINGET_PACKAGE: result = InstallPackage(command); break;
	default: break;
	}

	return result;
}

bool RunLufrakCommands(const LufrakCommand* commands, size_t numCommands)
{
	ASSERT(commands != NULL, "Null pointer caught by RunLufrakCommands()");

	size_t i, result = 0;

	for (i = 0; i < numCommands; ++i)
		result += (size_t)RunLufrakCommand((commands + i));

	return (result == numCommands);
}

void RunLufrakTool(LufrakToolRunFuncPtr runFunc, LufrakToolDrawFuncPtr drawFunc)
{
	ASSERT(runFunc != NULL && drawFunc != NULL, "Null function pointer caught by RunLufrakTool()");

	HANDLE runThread = NULL;
	DWORD runThreadID = 0;

	runThread = CreateThread(NULL, 0, runFunc, NULL, 0, &runThreadID);

	ASSERT(runThread != NULL, "Couldn't create a new thread in RunLufrakTool()");

	drawFunc();

	ASSERT(CloseHandle(runThread), "Couldn't close thread handle");

	return;
}

SystemInformation GetSystemInformation(void)
{
	SystemInformation sysInfo = { 0 };

	sysInfo.memInfo.dwLength = sizeof(sysInfo.memInfo);

	GetSystemInfo(&sysInfo.sysInfo);
	GlobalMemoryStatusEx(&sysInfo.memInfo);

	ZeroMemory(sysInfo.processorName, ARRAY_SIZE(sysInfo.processorName));
	__cpuid((int*)(sysInfo.processorName), 0x80000002);
	__cpuid((int*)(sysInfo.processorName + 16), 0x80000003);
	__cpuid((int*)(sysInfo.processorName + 32), 0x80000004);

	switch (sysInfo.sysInfo.wProcessorArchitecture)
	{
	case PROCESSOR_ARCHITECTURE_INTEL:
		sysInfo.processorArchitecture = "x86 32 bit";
		break;
	case PROCESSOR_ARCHITECTURE_AMD64:
		sysInfo.processorArchitecture = "x86 64 bit";
		break;
	case PROCESSOR_ARCHITECTURE_ARM:
		sysInfo.processorArchitecture = "ARM 32 bit";
		break;
	case PROCESSOR_ARCHITECTURE_ARM64:
		sysInfo.processorArchitecture = "ARM 64 bit";
		break;
	case PROCESSOR_ARCHITECTURE_IA64:
		sysInfo.processorArchitecture = "IA 64 bit";
		break;
	}

	return sysInfo;
}