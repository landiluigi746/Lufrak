#include "Lufrak.h"
#include "LufrakInternal.h"

#include <raygui.h>

static ExecutionStatus status = PROCESSING;
static LufrakCommand command = CMD_COMMAND("God Mode", "mkdir", "\"C:\\GodMode.{ED7BA470-8E54-465E-825C-99712043E01C}\"");

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

			Rectangle textRect = { GetScreenWidth() / 2 - 250, GetScreenHeight() / 2 - 60, 500, 70};

			GuiSetStyle(DEFAULT, TEXT_SIZE, SUBTITLE_FONT_SIZE);
			GuiLabel((Rectangle) { GetScreenWidth() / 2 - 150, textRect.y - 100, 300, 35 }, "God Mode");

			switch (status)
			{
			case PROCESSING:
				text = "Unlocking god mode. Please wait";
				break;
			case SUCCESS:
				text = "Done! You can find the God Mode folder in C:\nPress the exit button to return to menu.";
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

IMPL_TOOL(GodMode)
{
	status = PROCESSING;

	RUN_TOOL();

	return;
}