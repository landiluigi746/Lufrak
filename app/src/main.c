#include <lufrak.h>

int main(void)
{
    InitApp();
    
    Tool tools[] = {
        GET_TOOL(Upgrader),
        GET_TOOL(Installer)
    };

    int choice;

    do{
        choice = Menu();

        if(choice != endMenuIdx)
            tools[choice]();
    } while(choice != endMenuIdx);

    return 0;
}