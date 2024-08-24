#include "Lufrak.h"
#include "LufrakInternal.h"

#include <raylib.h>
#include <raygui.h>
#include <style_dark.h>

static Font font = { 0 };

static const int windowWidth = 800;
static const int windowHeight = 600;

void LufrakInit(void)
{
	LufrakInternalInit();

	InitWindow(windowWidth, windowHeight, "Example");
	SetTargetFPS(60);

	GuiLoadStyleDark();
	font = LoadFont("App/Resources/Fonts/Comfortaa.ttf");

	SetTextureFilter(font.texture, TEXTURE_FILTER_TRILINEAR);
	GuiSetFont(font);

	GuiSetStyle(LABEL, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);

	return;
}

void LufrakClose(void)
{
	CloseWindow();
	UnloadFont(font);

	LufrakInternalClose();

	return;
}