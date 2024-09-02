#include "Lufrak.h"
#include "LufrakInternal.h"

#include <raygui.h>

static ExecutionStatus status = PROCESSING;
static LufrakCommand commands[] = {
	CMD_COMMAND("Create a Windows Restore Point", "wmic.exe", "/Namespace:\\\\root\\default Path SystemRestore Call CreateRestorePoint \"Lufrak\", 100, 7"),
	CMD_COMMAND("Run a rapid virus scan", "C:\\Program Files\\Windows Defender\\MpCmdRun.exe", "-Scan -ScanType 1"),
	CMD_COMMAND("Run a complete virus scan", "C:\\Program Files\\Windows Defender\\MpCmdRun.exe", "-Scan -ScanType 2")
};

static const size_t numCommands = ARRAY_SIZE(commands);
static size_t selected = 0;

static bool GetSelection(void)
{
	bool running = true;
	size_t i;

	selected = 0;

	GuiSetState(STATE_DISABLED);

	while (running)
	{
		BeginDrawing();

		{
			ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

			uint32_t buttonSpacing = 45;
			Rectangle buttonRect = { GetScreenWidth() / 2 - 150, GetScreenHeight() / 2 - (numCommands + 1) * buttonSpacing / 2, 300, 35 };

			GuiSetStyle(DEFAULT, TEXT_SIZE, SUBTITLE_FONT_SIZE);
			GuiLabel((Rectangle) { GetScreenWidth() / 2 - 150, GetScreenHeight() / 2 - 180, 300, 35 }, "Backup and Security");

			GuiSetStyle(DEFAULT, TEXT_SIZE, BUTTON_FONT_SIZE);

			for (i = 0; i < numCommands; ++i)
			{
				buttonRect.y += buttonSpacing;

				if (GuiButton(buttonRect, commands[i].displayName))
				{
					selected = i;
					return true;
				}
			}

			buttonRect.y += buttonSpacing * 3;

			if (GuiButton(buttonRect, "Exit"))
			{
				SetMousePosition(GetMouseX(), GetMouseY() + buttonSpacing);
				return false;
			}

			GuiSetState(STATE_NORMAL);
		}

		EndDrawing();
	}
}

TOOL_RUN_FUNC()
{
	status = RunLufrakCommand(&commands[selected]) ? SUCCESS : FAILURE;

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
			GuiLabel((Rectangle) { GetScreenWidth() / 2 - 150, textRect.y - 100, 300, 35 }, "Backup and Security");

			switch (status)
			{
			case PROCESSING:
				text = TextFormat("Running %s. Please wait", commands[selected].displayName);
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

IMPL_TOOL(BackupSecurity)
{
	status = PROCESSING;
	selected = 0;

	if (GetSelection())
		RUN_TOOL();

	return;
}