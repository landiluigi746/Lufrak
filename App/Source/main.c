#include "Lufrak.h"

#include <raygui.h>

int main(void)
{
	const LufrakTool tools[] = {
		{ "Upgrader", &Upgrader },
		{ "Installer", &Installer },
		{ "Optimizer", &Optimizer },
		{ "Security", &Security },
		{ "Display System Information", &SystemInfo },
		{ "Enable God Mode", &GodMode }
	};

	const size_t numTools = ARRAY_SIZE(tools);
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