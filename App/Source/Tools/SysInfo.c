#include "Lufrak.h"
#include "LufrakInternal.h"

#include <raylib.h>
#include <raygui.h>
#include <style_dark.h>

IMPL_TOOL(SystemInfo)
{
	SystemInformation sysInfo = GetSystemInformation();

	const char* texts[] = {
		TextFormat("Processor: %s", sysInfo.processorName),
		TextFormat("Architecture: %s", sysInfo.processorArchitecture),
		TextFormat("Logical Processors: %lu", sysInfo.sysInfo.dwNumberOfProcessors),
		TextFormat("Total RAM: %.2lf GB", (double)sysInfo.memInfo.ullTotalPhys / (1024 * 1024 * 1024))
	};

	const size_t numTexts = sizeof(texts) / sizeof(texts[0]);
	size_t i;

	bool running = true;

	GuiSetState(STATE_DISABLED);

	while (running)
	{
		BeginDrawing();

		{
			ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

			uint32_t textLineSpacing = 20;
			Vector2 textPos = { GetScreenWidth() * 1 / 4, GetScreenHeight() / 2 - textLineSpacing * 4};

			GuiSetStyle(DEFAULT, TEXT_SIZE, SUBTITLE_FONT_SIZE);

			GuiLabel((Rectangle) { GetScreenWidth() / 2 - 150, textPos.y - textLineSpacing * 4, 300, 35 }, "System Information");

			for (i = 0; i < numTexts; ++i)
			{
				DrawTextEx(GuiGetFont(), texts[i], textPos, BUTTON_FONT_SIZE, 1, GetColor(GuiGetStyle(DEFAULT, TEXT_COLOR_NORMAL)));
				textPos.y += textLineSpacing;
			}

			GuiSetStyle(DEFAULT, TEXT_SIZE, BUTTON_FONT_SIZE);

			if (GuiButton((Rectangle){ GetScreenWidth() / 2 - 130, textPos.y + textLineSpacing * 2, 260, 35 }, "Exit"))
				running = false;

			GuiSetState(STATE_NORMAL);
		}

		EndDrawing();
	}

	return;
}