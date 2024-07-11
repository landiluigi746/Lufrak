#include <lufrak.h>

#define START_Y LINES / 2 + 2

static const char* banner[] = {
    " ___           _        _ _            ",
    "|_ _|_ __  ___| |_ __ _| | | ___ _ __  ",
    " | || '_ \\/ __| __/ _` | | |/ _ \\ '__| ",
    " | || | | \\__ \\ || (_| | | |  __/ |    ",
    "|___|_| |_|___/\\__\\__,_|_|_|\\___|_|    ",
};

static const Package packages[] = {
    { "Google Chrome",         "Google.Chrome" },
    { "Mozilla Firefox",       "Mozilla.Firefox" },
    { "Adobe Acrobat Reader",  "Adobe.Acrobat.Reader.64-bit" },
    { "Discord",               "Discord.Discord" },
    { "Steam",                 "Valve.Steam" },
    { "Epic Games Launcher",   "EpicGames.EpicGamesLauncher" },
    { "WhatsApp",              "WhatsApp.WhatsApp" },
    { "Malwarebytes",          "Malwarebytes.Malwarebytes" },
    { "VLC Media Player",      "VideoLAN.VLC" },
    { "WinRAR",                "RARLab.WinRAR" },
    { "Telegram Desktop",      "Telegram.TelegramDesktop" },
    { "Visual Studio Code",    "Microsoft.VisualStudioCode" },
    { "Notepad++",             "Notepad++.Notepad++" },
    { "OBS Studio",            "OBSProjecct.OBSStudio" },
    { "qBittorrent",           "qBittorrent.qBittorrent" },
    { "CCleaner",              "Piriform.CCleaner" },
    { "Logitech G HUB",        "Logitech.GHUB" },
    { "GIMP",                  "GIMP.GIMP" },
    { "EA Desktop",            "ElectronicArts.EADesktop" },
    { "HWiNFO",                "REALiX.HWiNFO" }
};

static const size_t numPackages = sizeof(packages) / sizeof(Package);

static const char* msgs[] = {
    "Select the apps you want to install",
    "Press space to add an app to the list",
    "Press enter to run the installer",
    "Press m to return to menu"
};

static const size_t numMsg = sizeof(msgs) / sizeof(char*);
static Package* selectedPackages = NULL;
static int* selectedIdxs = NULL;
static int selectedCounter = 0;

static int i;
static int result = PROCESSING;
TOOL_MESSAGES()

static bool GetSelection(void)
{
    attr_t hoverAttr = A_BOLD | COLOR_PAIR(1);
    attr_t selectedAttr = A_BOLD | COLOR_PAIR(2);

    selectedCounter = 0;
    selectedIdxs = SafeMalloc(sizeof(int) * numPackages);
    int i, j, drawX, drawY;
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

            for (j = 0; j < selectedCounter; j++)
                if (selectedIdxs[j] == i)
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
                if (selectedIdxs[selectedCounter - 1] == hovered) selectedCounter--;
                else selectedIdxs[selectedCounter++] = hovered;
                
                break;

            case 'm':       return false;
        }
    } while (key != '\n');

    return (selectedCounter > 0);
}

static void* Draw(void* arg)
{
    char msgRunning[STR_SIZE];

    char chars[] = "|/-|-\\";
    size_t charsLen = strlen(chars);
    
    int j = 0;

    while (i < selectedCounter)
    {
        (j < charsLen - 1) ? (j++) : (j = 0);

        sprintf_s(msgRunning, STR_SIZE, "Installing %s %c", selectedPackages[i].displayName, chars[j]);
        PrintMessage(banner, 5, msgRunning);

        Wait(500);            
    }

    return NULL;
}

static void* Run(void* arg)
{
    for(i = 0; i < selectedCounter; i++)
        result += InstallPackage(&selectedPackages[i]);

    free(selectedIdxs);
    free(selectedPackages);

    return NULL;
}

DEFINE_TOOL(Installer)
{
    pthread_t installThread;
    pthread_t drawThread;

    bool selectionDone = GetSelection();

    if (selectionDone)
    {
        selectedPackages = (Package*) SafeMalloc(sizeof(Package) * selectedCounter);

        for(i = 0; i < selectedCounter; i++)
            selectedPackages[i] = packages[selectedIdxs[i]];

        pthread_create(&installThread, NULL, &Run, NULL);
        pthread_create(&drawThread, NULL, &Draw, NULL);

        pthread_join(installThread, NULL);
        pthread_join(drawThread, NULL);

        PrintMessage(banner, 5, (result == selectedCounter) ? msgSuccess : msgFailure);

        getch();
    }

    return;
}