#include <Etaine/Helpers/ConsoleHelper.h>
#include <iostream>

void ConsoleHelper::CreateConsole()
{
    AllocConsole();

    FILE* fDummy;
    freopen_s(&fDummy, "CONIN$", "r", stdin);
    freopen_s(&fDummy, "CONOUT$", "w", stderr);
    freopen_s(&fDummy, "CONOUT$", "w", stdout);

    std::cout << "------------- Etaine Packet Sniffer hooked -------------" << std::endl;
}