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

bool RunCommand(const Command* command)
{
    SHELLEXECUTEINFOA sei = { 0 };

	sei.cbSize = sizeof(sei);
	//sei.fMask = SEE_MASK_NOCLOSEPROCESS;
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
	int i, result = 0;

	for(i = 0; i < numCommands; i++)
		result += (int) RunCommand((commands + i));

	return (result == (int)numCommands);
}

bool InstallPackage(const Package* package)
{
	Command command = { 0 };

	command.command = "winget";
	command.args = SafeMalloc(sizeof(char) * STR_SIZE);

	sprintf_s(command.args, STR_SIZE, "install -e --id %s", package->wingetID);

    return RunCommand(&command);
}