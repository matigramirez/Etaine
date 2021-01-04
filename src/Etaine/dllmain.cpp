#include "pch.h"
#include <iostream>
#include <thread>
#include <Etaine/Analyzer.h>
#include <Etaine/Helpers/ImGuiHelper.h>

DWORD WINAPI MainThread(LPVOID lpReserved)
{
    ImGuiHelper::Initialize();
    Analyzer::Initialize();

    return TRUE;
}

/// <summary>
///  Defines the entry method of the dll
/// </summary>
/// <param name="hModule"></param>
/// <param name="ul_reason_for_call"></param>
/// <param name="lpReserved"></param>
/// <returns></returns>
BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD  ul_reason_for_call,
                      LPVOID lpReserved)
{
    std::thread newThread;
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        CreateThread(nullptr, 0, MainThread, hModule, 0, nullptr);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}