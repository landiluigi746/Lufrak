#ifndef LUFRAK_H__
#define LUFRAK_H__

#include "Utility.h"

#define TITLE_FONT_SIZE 40
#define SUBTITLE_FONT_SIZE 30
#define BUTTON_FONT_SIZE 18

#define DEFINE_TOOL(name) void name(void);
#define IMPL_TOOL(name) void name(void)

typedef struct
{
	const char* displayText;
	void (*function)(void);
} LufrakTool;

void LufrakInit(void);
void LufrakClose(void);

DEFINE_TOOL(SystemInfo)

#endif // !LUFRAK_H__
