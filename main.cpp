#include "imgui.h"
#include "ui_manager.h"

int main() {
    if (!InitSystem()) return 1;

    ApplyClassicWindowsTheme();

    while (IsRunning()) {
        NewFrame();
        RenderIDE(); 
        EndFrame();
    }

    CleanupSystem();
    return 0;
}