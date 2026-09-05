#pragma once
#ifdef _WIN32
#include <windows.h>
#endif

namespace srn {
struct Config {
    int fovValues[3] {30, 60, 90};
    int renderValues[3] {6, 8, 10};
    int fovIndex = 1;
    int renderIndex = 0;
    bool fullBright = false;
};

void Start();
void Stop();
void Tick();
void OnFovCycle();
void OnRenderCycle();
void OnFullBrightToggle();
}
