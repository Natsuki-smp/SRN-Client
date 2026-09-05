#include <windows.h>
#include "srn_client.h"

static HANDLE g_thread = nullptr;
static volatile bool g_running = false;

static DWORD WINAPI Worker(LPVOID) {
    srn::Start();
    while (g_running) {
        srn::Tick();
        Sleep(10);
    }
    srn::Stop();
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID) {
    if (reason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hModule);
        g_running = true;
        g_thread = CreateThread(nullptr, 0, Worker, nullptr, 0, nullptr);
    } else if (reason == DLL_PROCESS_DETACH) {
        g_running = false;
        if (g_thread) {
            WaitForSingleObject(g_thread, 1000);
            CloseHandle(g_thread);
            g_thread = nullptr;
        }
    }
    return TRUE;
}
