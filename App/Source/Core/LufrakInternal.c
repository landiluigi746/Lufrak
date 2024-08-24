#include "LufrakInternal.h"

#include <intrin.h>
#include <Objbase.h>
#include <Shellapi.h>

#define INTERNAL_BUF_SIZE 256

void LufrakInternalInit(void)
{
	assert(SUCCEEDED(CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE)));

	return;
}

void LufrakInternalClose(void)
{
	CoUninitialize();
}

static bool RunCmdCommand(const LufrakCommand* cmd)
{
	assert(cmd != NULL && "Null pointer caught by RunCmdCommand()\n");

	SHELLEXECUTEINFOA sei = { 0 };

	sei.cbSize = sizeof(sei);
	sei.fMask = SEE_MASK_NOCLOSEPROCESS;
	sei.lpVerb = "runas";
	sei.lpFile = cmd->command;
	sei.lpParameters = cmd->args;
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
	assert(package != NULL && "Null pointer caught by InstallPackage()\n");
	assert(package->type == WINGET_PACKAGE && "Non winget package caught by InstallPackage()\n");

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
	assert(command != NULL && "Null pointer caught by RunLufrakCommand()\n");

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
	size_t i, result = 0;

	for (i = 0; i < numCommands; ++i)
		result += (size_t)RunLufrakCommand((commands + i));

	return (result == numCommands);
}

SystemInformation GetSystemInformation(void)
{
	SystemInformation sysInfo = { 0 };

	sysInfo.memInfo.dwLength = sizeof(sysInfo.memInfo);

	GetSystemInfo(&sysInfo.sysInfo);
	GlobalMemoryStatusEx(&sysInfo.memInfo);

	ZeroMemory(sysInfo.processorName, sizeof(char) * 49);
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