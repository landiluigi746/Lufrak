#include "Lufrak.h"
#include "LufrakInternal.h"

#include <raygui.h>
#include <style_cyber.h>

#include "Logo.h"
#include "Font.h"

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

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(windowWidth, windowHeight, "Lufrak");
	SetTargetFPS(60);

	GuiLoadStyleCyber();
	font = LoadFont_Font();

	icon.width = LOGO_WIDTH;
	icon.height = LOGO_HEIGHT;
	icon.data = LOGO_DATA;
	icon.format = LOGO_FORMAT;
	icon.mipmaps = 1;

	SetWindowIcon(icon);

	SetTextureFilter(font.texture, TEXTURE_FILTER_BILINEAR);
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

	LufrakInternalClose();

	initialized = false;

	return;
}