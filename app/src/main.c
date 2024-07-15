#include <lufrak.h>

int main(void)
{
    InitApp();
    
    Tool tools[] = {
        GET_TOOL(Upgrader),
        GET_TOOL(Installer),
        GET_TOOL(Optimizer),
        GET_TOOL(BackupAndSecurity),
        GET_TOOL(SystemInfo),
        GET_TOOL(GodMode)
    };

    int choice;

    do{
        choice = Menu();

        if(choice != endMenuIdx)
            tools[choice]();
    } while(choice != endMenuIdx);

    CloseApp();

    return 0;
}