#include "Lufrak.h"
#include "LufrakInternal.h"

#include <raylib.h>
#include <raygui.h>
#include <style_dark.h>

static Font font = { 0 };
static Image icon = { 0 };

static const int windowWidth = 800;
static const int windowHeight = 600;

static bool initialized = false;

void LufrakInit(void)
{
	if (initialized)
		return;

	LufrakInternalInit();

	InitWindow(windowWidth, windowHeight, "Lufrak");
	SetTargetFPS(60);

	GuiLoadStyleDark();
	font = LoadFont("App/Resources/Fonts/Comfortaa.ttf");

	icon = LoadImage("App/Resources/Images/Logo.png");
	SetWindowIcon(icon);

	SetTextureFilter(font.texture, TEXTURE_FILTER_TRILINEAR);
	GuiSetFont(font);

	GuiSetStyle(LABEL, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);

	initialized = true;

	return;
}

void LufrakClose(void)
{
	if (!initialized)
		return;

	CloseWindow();
	UnloadFont(font);
	UnloadImage(icon);

	LufrakInternalClose();

	initialized = false;

	return;
}