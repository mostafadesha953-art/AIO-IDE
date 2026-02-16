#include "ui_manager.h"
#include "ai_engine.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <string>

// حالة تشغيل التطبيق
bool g_AppRunning = true;

bool InitSystem() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    // إعدادات إضافية للمحرك الرسومي توضع هنا عند الربط الفعلي
    return true; 
}

bool IsRunning() { return g_AppRunning; }

void NewFrame() {
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
}

void EndFrame() {
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void CleanupSystem() {
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

void ApplyClassicWindowsTheme() {
    ImGuiStyle& style = ImGui::GetStyle();
    style.Colors[ImGuiCol_WindowBg]      = ImVec4(0.82f, 0.82f, 0.82f, 1.00f); // رمادي
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 0.00f, 0.50f, 1.00f); // أزرق كلاسيك
    style.WindowRounding = 0.0f; // حواف حادة
}

void RenderIDE() {
    static char codeBuffer[1024 * 64] = "// Start Coding here...";
    static std::string aiStatus = "AI Assistant Ready.";

    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
    
    ImGui::Begin("AIO Smart Developer Platform", &g_AppRunning, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

    // محرر الأكواد
    ImGui::InputTextMultiline("##Editor", codeBuffer, IM_ARRAYSIZE(codeBuffer), ImVec2(ImGui::GetWindowWidth() * 0.7f, -1.0f));
    
    ImGui::SameLine();

    // لوحة التحكم والذكاء الاصطناعي
    ImGui::BeginGroup();
    if (ImGui::Button("Compile (Internal)", ImVec2(150, 30))) { 
        aiStatus = "Compiling internally..."; 
    }
    
    ImGui::Spacing();

    if (ImGui::Button("AI Fix & Update", ImVec2(150, 30))) {
        aiStatus = "AI is analyzing...";
        std::string result = AIEngine::RequestRefactor(codeBuffer);
        strncpy(codeBuffer, result.c_str(), sizeof(codeBuffer));
        aiStatus = "AI Refactor Complete.";
    }

    ImGui::Separator();
    ImGui::Text("System Status:");
    ImGui::TextWrapped(aiStatus.c_str());
    ImGui::EndGroup();

    ImGui::End();
}
