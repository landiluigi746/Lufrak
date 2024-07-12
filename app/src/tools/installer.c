#include <lufrak.h>

#define START_Y LINES / 2 + 2

static const char* banner[] = {
    " ___           _        _ _            ",
    "|_ _|_ __  ___| |_ __ _| | | ___ _ __  ",
    " | || '_ \\/ __| __/ _` | | |/ _ \\ '__| ",
    " | || | | \\__ \\ || (_| | | |  __/ |    ",
    "|___|_| |_|___/\\__\\__,_|_|_|\\___|_|    ",
};

static Package packages[] = {
    { "Google Chrome",         "Google.Chrome", false },
    { "Mozilla Firefox",       "Mozilla.Firefox", false },
    { "Adobe Acrobat Reader",  "Adobe.Acrobat.Reader.64-bit", false },
    { "Discord",               "Discord.Discord", false },
    { "Steam",                 "Valve.Steam", false },
    { "Epic Games Launcher",   "EpicGames.EpicGamesLauncher", false },
    { "WhatsApp",              "WhatsApp.WhatsApp", false },
    { "Malwarebytes",          "Malwarebytes.Malwarebytes", false },
    { "VLC Media Player",      "VideoLAN.VLC", false },
    { "WinRAR",                "RARLab.WinRAR", false },
    { "Telegram Desktop",      "Telegram.TelegramDesktop", false },
    { "Visual Studio Code",    "Microsoft.VisualStudioCode", false },
    { "Notepad++",             "Notepad++.Notepad++", false },
    { "OBS Studio",            "OBSProjecct.OBSStudio", false },
    { "qBittorrent",           "qBittorrent.qBittorrent", false },
    { "CCleaner",              "Piriform.CCleaner", false },
    { "Logitech G HUB",        "Logitech.GHUB", false },
    { "GIMP",                  "GIMP.GIMP", false },
    { "EA Desktop",            "ElectronicArts.EADesktop", false },
    { "HWiNFO",                "REALiX.HWiNFO", false }
};

static const size_t numPackages = sizeof(packages) / sizeof(Package);

static const char* msgs[] = {
    "Select the apps you want to install",
    "Press space to add an app to the list",
    "Press enter to run the installer",
    "Press m to return to menu"
};

static const size_t numMsg = sizeof(msgs) / sizeof(char*);

static int i;
static int selectedCounter = 0;
static int result = PROCESSING;
TOOL_MESSAGES()

static bool GetSelection(void)
{
    attr_t hoverAttr = A_BOLD | COLOR_PAIR(1);
    attr_t selectedAttr = A_BOLD | COLOR_PAIR(2);

    int i, drawX, drawY;
    int hovered = 0;
    int key = 0;

    do {
        DrawBanner(banner, 5);

        for (i = 0; i < numMsg; i++)
            mvprintw(12 + i, COLS / 2 - strlen(msgs[i]) / 2, msgs[i]);

        drawY = START_Y;

        for (i = 0; i < numPackages; i++)
        {
            drawX = (i < numPackages / 2) ? COLS / 2 - 40 : COLS / 2 + 20;
            
            if (i == numPackages / 2) 
                drawY = START_Y - i;
            
            if (i == hovered)
                attron(hoverAttr);

            if (packages[i].selected)
                attron(selectedAttr);

            mvprintw(drawY + i, drawX, packages[i].displayName);
            attroff(hoverAttr);
            attroff(selectedAttr);
        }

        refresh();

        key = tolower(getch());

        switch (key)
        {
            case KEY_UP:    (hovered == 0) ? hovered = numPackages - 1 : --hovered;   break;
            case KEY_DOWN:  (hovered == numPackages - 1) ? hovered = 0 : ++hovered;   break;

            case ' ':
                packages[hovered].selected = !packages[hovered].selected;
                (packages[hovered].selected) ? selectedCounter++ : selectedCounter--;

                break;

            case 'm':       return false;
        }
    } while (key != '\n');

    return (selectedCounter > 0);
}

TOOL_FUNC(Draw)
{
    char msgRunning[STR_SIZE];

    char chars[] = "|/-|-\\";
    size_t charsLen = sizeof(chars) - 1;
    
    int j = 0;

    while (i < numPackages)
    {
        (j < charsLen - 1) ? (j++) : (j = 0);

        sprintf_s(msgRunning, STR_SIZE, "Installing %s %c", packages[i].displayName, chars[j]);
        PrintMessage(banner, 5, msgRunning);

        Wait(500);            
    }

    return NULL;
}

TOOL_FUNC(Run)
{
    for(i = 0; i < numPackages; i++)
        if(packages[i].selected)
            result += InstallPackage(&packages[i]);

    return NULL;
}

DEFINE_TOOL(Installer)
{
    if (GetSelection())
    {
        RunTool(&Run, &Draw);
        PrintMessage(banner, 5, (result == selectedCounter) ? msgSuccess : msgFailure);

        getch();
    }

    return;
}