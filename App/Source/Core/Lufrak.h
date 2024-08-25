#ifndef LUFRAK_H__
#define LUFRAK_H__

#include "Utility.h"

#define TITLE_FONT_SIZE 40
#define SUBTITLE_FONT_SIZE 30
#define BUTTON_FONT_SIZE 18
#define NORMAL_TEXT_SIZE 22

#define DEFINE_TOOL(name) extern void name(void);
#define IMPL_TOOL(name) void name(void)

typedef struct
{
	const char* displayText;
	void (*function)(void);
} LufrakTool;

void LufrakInit(void);
void LufrakClose(void);

DEFINE_TOOL(SystemInfo)
DEFINE_TOOL(GodMode)
DEFINE_TOOL(Upgrader)

#endif // !LUFRAK_H__
