#include "Lufrak.h"
#include "LufrakInternal.h"

#include <raygui.h>

static ExecutionStatus status = PROCESSING;
static LufrakCommand packages[] = {
	WINGET_PACKAGE("Google Chrome",         "Google.Chrome"),
	WINGET_PACKAGE("Mozilla Firefox",       "Mozilla.Firefox"),
	WINGET_PACKAGE("Adobe Acrobat Reader",  "Adobe.Acrobat.Reader.64-bit"),
	WINGET_PACKAGE("Discord",               "Discord.Discord"),
	WINGET_PACKAGE("Steam",                 "Valve.Steam"),
	WINGET_PACKAGE("Epic Games Launcher",   "EpicGames.EpicGamesLauncher"),
	WINGET_PACKAGE("WhatsApp",              "WhatsApp.WhatsApp"),
	WINGET_PACKAGE("Malwarebytes",          "Malwarebytes.Malwarebytes"),
	WINGET_PACKAGE("VLC Media Player",      "VideoLAN.VLC"),
	WINGET_PACKAGE("WinRAR",                "RARLab.WinRAR"),
	WINGET_PACKAGE("Telegram Desktop",      "Telegram.TelegramDesktop"),
	WINGET_PACKAGE("Visual Studio Code",    "Microsoft.VisualStudioCode"),
	WINGET_PACKAGE("Notepad++",             "Notepad++.Notepad++"),
	WINGET_PACKAGE("OBS Studio",            "OBSProjecct.OBSStudio"),
	WINGET_PACKAGE("qBittorrent",           "qBittorrent.qBittorrent"),
	WINGET_PACKAGE("CCleaner",              "Piriform.CCleaner"),
	WINGET_PACKAGE("Logitech G HUB",        "Logitech.GHUB"),
	WINGET_PACKAGE("GIMP",                  "GIMP.GIMP"),
	WINGET_PACKAGE("EA Desktop",            "ElectronicArts.EADesktop"),
	WINGET_PACKAGE("HWiNFO",                "REALiX.HWiNFO")
};

static const size_t numPackages = ARRAY_SIZE(packages);

static int numSelectedPackages = 0;
static size_t currentPackage = 0;

static bool GetSelection(void)
{
	numSelectedPackages = 0;

	bool running = true;
	size_t i;

	for (i = 0; i < numPackages; i++)
		packages[i].toInstall = false;

	while (running)
	{
		BeginDrawing();

		{
			ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

			Rectangle checkBoxRect = { GetScreenWidth() / 2 - 225, GetScreenHeight() / 2 - 175, 15, 15 };

			GuiSetStyle(DEFAULT, TEXT_SIZE, SUBTITLE_FONT_SIZE);
			GuiLabel((Rectangle) { GetScreenWidth() / 2 - 150, GetScreenHeight() / 2 - 230, 300, 35 }, "Installer");

			GuiSetStyle(DEFAULT, TEXT_SIZE, CHECKBOX_FONT_SIZE);

			for (i = 0; i < numPackages; i++)
			{
				if (i == numPackages / 2)
				{
					checkBoxRect.x += 300;
					checkBoxRect.y = GetScreenHeight() / 2 - 175;
				}

				checkBoxRect.y += 25;

				GuiCheckBox(checkBoxRect, packages[i].displayName, &packages[i].toInstall);
			}

			Rectangle buttonRect = { GetScreenWidth() / 2 - 130, checkBoxRect.y + 100, 260, 35 };

			if (GuiButton(buttonRect, "Install"))
				running = false;

			buttonRect.y += 40;

			if (GuiButton(buttonRect, "Exit"))
				return false;
		}

		EndDrawing();
	}

	for (i = 0; i < numPackages; i++)
	{
		if (packages[i].toInstall)
			numSelectedPackages++;
	}

	return (numSelectedPackages > 0);
}

TOOL_RUN_FUNC()
{
	size_t result = 0;

	for (currentPackage = 0; currentPackage < numPackages; currentPackage++)
	{
		if (packages[currentPackage].toInstall)
			result += (size_t)RunLufrakCommand(&packages[currentPackage]);
	}

	status = (result == numSelectedPackages) ? SUCCESS : FAILURE;

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

			Rectangle textRect = { GetScreenWidth() / 2 - 250, GetScreenHeight() / 2 - 60, 500, 70 };

			GuiSetStyle(DEFAULT, TEXT_SIZE, SUBTITLE_FONT_SIZE);
			GuiLabel((Rectangle) { GetScreenWidth() / 2 - 150, textRect.y - 100, 300, 35 }, "Installer");

			switch (status)
			{
			case PROCESSING:
				text = TextFormat("Installing %s. Please wait", packages[currentPackage].displayName);
				break;
			case SUCCESS:
				text = "Done! Press the exit button to return to menu.";
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

IMPL_TOOL(Installer)
{
	status = PROCESSING;

	if (GetSelection())
		RUN_TOOL();

	return;
}