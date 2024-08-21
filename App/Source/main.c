#include "raylib.h"

#if defined(_WIN32)
#define NOGDI
#define NOUSER
#endif

#include <Windows.h>

#if defined(_WIN32)
#undef near
#undef far
#endif

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "style_dark.h"

int main(void)
{
	InitWindow(800, 450, "Example");

	GuiLoadStyleDark();

	while (!WindowShouldClose())
	{
		BeginDrawing();

		{
			GuiLabel((Rectangle) { 120, 120, 100, 50 }, "Hello!");

			if (GuiButton((Rectangle) { 250, 120, 100, 50 }, "Button!"))
				TraceLog(LOG_INFO, "Button Clicked!");
		}

		EndDrawing();
	}

	CloseWindow();

	return 0;
}