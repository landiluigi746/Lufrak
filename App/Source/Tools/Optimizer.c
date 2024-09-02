#include "Lufrak.h"
#include "LufrakInternal.h"

#include <raygui.h>

static ExecutionStatus status = PROCESSING;
static LufrakCommand commands[] = {
	CMD_COMMAND("", "ipconfig",	"/flushdns"),
	CMD_COMMAND("", "cleanmgr",	"/sagerun:1"),
	CMD_COMMAND("", "rmdir",	"/s /q \"%LocalAppData%\\Google\\Chrome\\User Data\\Default\\Cache\""),
	CMD_COMMAND("", "net",		"stop wuauserv"),
	CMD_COMMAND("", "rmdir",	"/s /q %windir%\\SoftwareDistribution"),
	CMD_COMMAND("", "net",		"start wuauserv")
};

TOOL_RUN_FUNC()
{
	status = RunLufrakCommands(commands, ARRAY_SIZE(commands)) ? SUCCESS : FAILURE;

	return 0;
}

TOOL_DRAW_FUNC()
{
	bool running = true;
	char* text = NULL;

	GuiSetState(STATE_DISABLED);

	while (running)
	{
		BeginDrawing();

		{
			ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

			Rectangle textRect = { GetScreenWidth() / 2 - 250, GetScreenHeight() / 2 - 60, 500, 70 };

			GuiSetStyle(DEFAULT, TEXT_SIZE, SUBTITLE_FONT_SIZE);
			GuiLabel((Rectangle) { GetScreenWidth() / 2 - 150, textRect.y - 100, 300, 35 }, "Optimizer");

			switch (status)
			{
			case PROCESSING:
				text = "Running optimizer. Please wait";
				break;
			case SUCCESS:
				text = "Done! Press the exit button to return to menu.";
				break;
			case FAILURE:
				text = "Fail! An error has occurred! Press any key to return to menu.";
				break;
			}

			if (status != PROCESSING)
			{
				GuiSetStyle(DEFAULT, TEXT_SIZE, BUTTON_FONT_SIZE);
				GuiSetState(STATE_NORMAL);

				if (GuiButton((Rectangle) { GetScreenWidth() / 2 - 130, textRect.y + 120, 260, 35 }, "Exit"))
					running = false;
			}

			GuiSetStyle(DEFAULT, TEXT_SIZE, NORMAL_FONT_SIZE);
			GuiLabel(textRect, text);
		}

		EndDrawing();
	}

	return;
}

IMPL_TOOL(Optimizer)
{
	status = PROCESSING;

	RUN_TOOL();

	return;
}