#include "Lufrak.h"
#include "LufrakInternal.h"

#include <raylib.h>
#include <raygui.h>
#include <style_dark.h>

static ExecutionStatus status = PROCESSING;
static LufrakCommand command = { 0 };

TOOL_RUN_FUNC()
{
	status = RunLufrakCommand(&command) ? SUCCESS : FAILURE;

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
			GuiLabel((Rectangle) { GetScreenWidth() / 2 - 150, textRect.y - 100, 300, 35 }, "Upgrader");

			switch (status)
			{
			case PROCESSING:
				text = "Upgrading programs. Please wait";
				break;
			case SUCCESS:
				text = "Done! Press the exit button to return to menu.";

				GuiSetStyle(DEFAULT, TEXT_SIZE, BUTTON_FONT_SIZE);
				GuiSetState(STATE_NORMAL);

				if (GuiButton((Rectangle) { GetScreenWidth() / 2 - 130, textRect.y + 120, 260, 35 }, "Exit"))
					running = false;

				break;
			case FAILURE:
				text = "Fail! An error has occurred! Press any key to return to menu.";
				break;
			}

			GuiSetStyle(DEFAULT, TEXT_SIZE, NORMAL_TEXT_SIZE);
			GuiLabel(textRect, text);
		}

		EndDrawing();
	}

	return;
}

IMPL_TOOL(Upgrader)
{
	command.type = CMD_COMMAND;
	command.command = "winget";
	command.args = "upgrade --all";

	RUN_TOOL();

	return;
}