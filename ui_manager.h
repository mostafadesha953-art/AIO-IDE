#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include "imgui.h"

// هذه مجرد "وعود" للمترجم بوجود هذه الدوال
bool InitSystem();
bool IsRunning();
void NewFrame();
void RenderIDE();
void EndFrame();
void CleanupSystem();
void ApplyClassicWindowsTheme();

#endif
