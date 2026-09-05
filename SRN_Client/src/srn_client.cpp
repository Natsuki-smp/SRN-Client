#include "srn_client.h"
#include <windows.h>
#include <atomic>

namespace {
srn::Config cfg;
std::atomic<bool> started{false};

void Notify(const wchar_t* text) {
    // Temporary development feedback. Replace with the Client's ImGui/toast UI.
    OutputDebugStringW(text);
    OutputDebugStringW(L"\n");
}

void PollKeys() {
    static bool prevC=false, prevX=false, prevG=false;
    const bool c = (GetAsyncKeyState('C') & 0x8000) != 0;
    const bool x = (GetAsyncKeyState('X') & 0x8000) != 0;
    const bool g = (GetAsyncKeyState('G') & 0x8000) != 0;
    if (c && !prevC) srn::OnFovCycle();
    if (x && !prevX) srn::OnRenderCycle();
    if (g && !prevG) srn::OnFullBrightToggle();
    prevC=c; prevX=x; prevG=g;
}
}

namespace srn {
void Start() { started=true; Notify(L"[SRN] Client started"); }
void Stop() { started=false; }

void Tick() {
    if (!started) return;
    PollKeys();
    // IMPORTANT: actual Bedrock 1.26.45.1 hooks are intentionally not guessed here.
    // FOV, render distance and fullbright must be wired to the exact 1.26.45.1
    // game structures/functions before this DLL is considered functional.
}

void OnFovCycle() {
    cfg.fovIndex = (cfg.fovIndex + 1) % 3;
    wchar_t b[96];
    swprintf_s(b, L"[SRN] FOV -> %d", cfg.fovValues[cfg.fovIndex]);
    Notify(b);
    // TODO: call the 1.26.45.1 camera/FOV setter.
}

void OnRenderCycle() {
    cfg.renderIndex = (cfg.renderIndex + 1) % 3;
    wchar_t b[96];
    swprintf_s(b, L"[SRN] Render Distance -> %d", cfg.renderValues[cfg.renderIndex]);
    Notify(b);
    // TODO: call the 1.26.45.1 render-distance setter.
}

void OnFullBrightToggle() {
    cfg.fullBright = !cfg.fullBright;
    Notify(cfg.fullBright ? L"[SRN] FullBright -> ON" : L"[SRN] FullBright -> OFF");
    // TODO: apply gamma/lighting override through a 1.26.45.1-safe hook.
}
}
