#include "Lufrak.h"

#include <raygui.h>
#include <style_dark.h>

int main(void)
{
	const LufrakTool tools[] = {
		{ "Upgrader", NULL },
		{ "Installer", NULL },
		{ "Optimizer", NULL },
		{ "Backup and Security", NULL },
		{ "Display System Information", &SystemInfo },
		{ "Enable God Mode", NULL }
	};

	const size_t numTools = sizeof(tools) / sizeof(tools[0]);
	size_t i;

	LufrakInit();

	while (!WindowShouldClose())
	{
		BeginDrawing();

		{
			ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

			uint32_t buttonSpacing = 45;
			Rectangle buttonRect = { GetScreenWidth() / 2 - 130, GetScreenHeight() / 2 - (numTools + 1) * buttonSpacing / 2, 260, 35};
			Vector2 titlePos = { buttonRect.x, buttonRect.y - buttonSpacing * 2 };

			GuiSetStyle(DEFAULT, TEXT_SIZE, TITLE_FONT_SIZE);

			GuiLabel((Rectangle){ buttonRect.x, buttonRect.y - buttonSpacing * 2, 260, 50 }, "Lufrak");

			GuiSetStyle(DEFAULT, TEXT_SIZE, BUTTON_FONT_SIZE);

			for (i = 0; i < numTools; ++i)
			{
				buttonRect.y += buttonSpacing;

				if (GuiButton(buttonRect, tools[i].displayText))
				{
					TraceLog(LOG_INFO, "Button %zu clicked!", i);

					if (tools[i].function != NULL)
						tools[i].function();
				}
			}

			buttonRect.y += buttonSpacing;

			if (GuiButton(buttonRect, "Exit"))
				break;
		}

		EndDrawing();
	}

	LufrakClose();

	return 0;
}