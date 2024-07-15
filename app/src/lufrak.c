#include <lufrak.h>

void InitApp(void)
{
    initscr();

    if(has_colors())
    {
        start_color();

        init_pair(HOVER, COLOR_BLACK, COLOR_WHITE);
        init_pair(SELECTED, COLOR_WHITE, COLOR_GREEN);
    }

    noecho();
    curs_set(0);
    keypad(stdscr, true);

    CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

    return;
}

void CloseApp(void)
{
	CoUninitialize();

	return;
}

void RunTool(ToolFuncPtr runFunc, ToolFuncPtr drawFunc)
{
	pthread_t runThread, drawThread;

	pthread_create(&runThread, NULL, runFunc, NULL);
	pthread_create(&drawThread, NULL, drawFunc, NULL);

	pthread_join(runThread, NULL);
	pthread_join(drawThread, NULL);

	return;
}

bool RunCommand(const Command* command)
{
	if(command == NULL)
		return false;

    SHELLEXECUTEINFOA sei = { 0 };

	sei.cbSize = sizeof(sei);
	sei.fMask = SEE_MASK_NOCLOSEPROCESS;
	sei.lpVerb = "runas";
	sei.lpFile = command->command;
	sei.lpParameters = command->args;
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

bool RunCommands(const Command* commands, size_t numCommands)
{
	if(commands == NULL)
		return false;

	int i, result = 0;

	for(i = 0; i < numCommands; i++)
		result += (int) RunCommand((commands + i));

	return (result == (int)numCommands);
}

bool InstallPackage(const Package* package)
{
	if(package == NULL)
		return false;

	Command command = { 0 };

	command.command = "winget";
	command.args = SafeMalloc(sizeof(char) * STR_SIZE);

	sprintf_s(command.args, STR_SIZE, "install -e --id %s", package->wingetID);

	bool result = RunCommand(&command);

	free(command.args);

    return result;
}

void GetSystemInformation(SystemInformation* sysInfo)
{
	if(sysInfo == NULL)
		return;
	
	*sysInfo = (SystemInformation){ 0 };

	sysInfo->wMemInfo.dwLength = sizeof(sysInfo->wMemInfo);
	
	GetSystemInfo(&sysInfo->wSysInfo);
	GlobalMemoryStatusEx(&sysInfo->wMemInfo);

	sysInfo->processorName = SafeMalloc(sizeof(char) * 48);
	
	memset(sysInfo->processorName, 0, sizeof(char) * 48);
	__cpuid((int*)(sysInfo->processorName), 0x80000002);
	__cpuid((int*)(sysInfo->processorName + 16), 0x80000003);
	__cpuid((int*)(sysInfo->processorName + 32), 0x80000004);

	switch (sysInfo->wSysInfo.wProcessorArchitecture)
	{
		case PROCESSOR_ARCHITECTURE_INTEL:
			sysInfo->processorArchitecture = "x86 32 bit";
			break;
		case PROCESSOR_ARCHITECTURE_AMD64:
			sysInfo->processorArchitecture = "x86 64 bit";
			break;
		case PROCESSOR_ARCHITECTURE_ARM:
			sysInfo->processorArchitecture = "ARM 32 bit";
			break;
		case PROCESSOR_ARCHITECTURE_ARM64:
			sysInfo->processorArchitecture = "ARM 64 bit";
			break;
		case PROCESSOR_ARCHITECTURE_IA64:
			sysInfo->processorArchitecture = "IA 64 bit";
			break;
	}

	return;
}