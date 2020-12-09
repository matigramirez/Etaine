#include "pch.h"
#include <iostream>
#include <thread>
#include <Reikeuseu/Analyzer.h>

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
        Analyzer::Initialize();
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
