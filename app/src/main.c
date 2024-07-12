#include <lufrak.h>

int main(void)
{
    InitApp();
    
    Tool tools[] = {
        GET_TOOL(Upgrader),
        GET_TOOL(Installer),
        NULL, // todo: optimizer
        NULL, // todo: backup and security
        GET_TOOL(SystemInfo),
        GET_TOOL(GodMode)
    };

    int choice;

    do{
        choice = Menu();

        if(choice != endMenuIdx)
            tools[choice]();
    } while(choice != endMenuIdx);

    return 0;
}