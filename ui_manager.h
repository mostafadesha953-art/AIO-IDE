#include "ui_manager.h"
#include "ai_engine.h"
#include <string>

// --- الجزء الأول: محرك التشغيل (Logic) ---
bool g_AppRunning = true;

bool InitSystem() {
    // إعداد سياق ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
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
    // ألوان ويندوز 2000 الكلاسيكية
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.82f, 0.82f, 0.82f, 1.00f);
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 0.00f, 0.50f, 1.00f);
    style.WindowRounding = 0.0f; // حواف حادة
}

// --- الجزء الثاني: كود واجهتك الذي أرسلته (Render) ---
void RenderIDE() {
    static char codeBuffer[1024 * 64] = "// Start Coding here...";
    static std::string aiStatus = "AI Assistant Ready.";

    // نافذة البرنامج الرئيسية
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
    ImGui::Begin("AIO Smart Developer Platform", &g_AppRunning, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

    // محرر الأكواد (Code Editor)
    ImGui::InputTextMultiline("##Editor", codeBuffer, IM_ARRAYSIZE(codeBuffer), ImVec2(ImGui::GetWindowWidth() * 0.7f, -1.0f));
    
    ImGui::SameLine();

    // التحكم بالذكاء الاصطناعي (AI Chat & Controls)
    ImGui::BeginGroup();
    ImGui::Text("AI Operations:");
    
    if (ImGui::Button("Compile (Internal)", ImVec2(150, 30))) { 
        aiStatus = "Compiling locally..."; 
    }
    
    ImGui::Spacing();

    if (ImGui::Button("AI Fix & Update", ImVec2(150, 30))) {
        aiStatus = "AI is analyzing code...";
        std::string result = AIEngine::RequestRefactor(codeBuffer);
        // هنا يتم تحديث المحرر بالنتيجة
        strncpy(codeBuffer, result.c_str(), sizeof(codeBuffer));
        aiStatus = "AI Optimization Complete.";
    }

    ImGui::Separator();
    ImGui::Text("Status:");
    ImGui::TextWrapped(aiStatus.c_str());
    
    ImGui::EndGroup();

    ImGui::End();
}
