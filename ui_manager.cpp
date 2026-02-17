#include "ui_manager.h"
#include "ai_engine.h"
#include "security.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <string>

// حالة تشغيل التطبيق
bool g_AppRunning = true;

bool InitSystem() {
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
    // ألوان ويندوز 2000 الاحترافية
    style.Colors[ImGuiCol_WindowBg]      = ImVec4(0.82f, 0.82f, 0.82f, 1.00f); 
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 0.00f, 0.50f, 1.00f); 
    style.WindowRounding = 0.0f; 
}

void RenderIDE() {
    // --- 1. شاشة التفعيل (Security Layer) ---
    if (!LicenseSystem::IsActivated) {
        ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
        ImGui::Begin("Product Activation", NULL, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::Text("AIO Smart IDE is Locked.\nEnter Serial Key:");
        static char keyInput[32] = "";
        ImGui::InputText("##Key", keyInput, IM_ARRAYSIZE(keyInput));
        if (ImGui::Button("Activate", ImVec2(-1, 0))) {
            if (LicenseSystem::ValidateKey(keyInput)) { /* Success */ }
        }
        ImGui::End();
        return; 
    }

    // --- 2. واجهة البرنامج الرئيسية (IDE Interface) ---
    static char codeBuffer[1024 * 64] = "// Start Coding here...";
    static char aiPrompt[256] = ""; // لوصف الكود المطلوب توليده
    static std::string aiStatus = "AI Assistant Ready.";

    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
    ImGui::Begin("AIO Smart Developer Platform - Licensed Version", &g_AppRunning, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

    // محرر الأكواد (يسار)
    ImGui::InputTextMultiline("##Editor", codeBuffer, IM_ARRAYSIZE(codeBuffer), ImVec2(ImGui::GetWindowWidth() * 0.7f, -1.0f));
    
    ImGui::SameLine();

    // لوحة التحكم والذكاء الاصطناعي (يمين)
    ImGui::BeginGroup();
    
    ImGui::Text("Internal Compiler:");
    if (ImGui::Button("Build EXE", ImVec2(150, 30))) { 
        aiStatus = "Compiling internally..."; 
    }
    
    ImGui::Separator();
    ImGui::Spacing();

    // قسم توليد الأكواد (New AI Feature)
    ImGui::Text("AI Code Generator:");
    ImGui::InputText("##Prompt", aiPrompt, IM_ARRAYSIZE(aiPrompt));
    if (ImGui::Button("Generate New Code", ImVec2(150, 30))) {
        aiStatus = "AI is writing code...";
        std::string generated = AIEngine::GenerateNewCode(aiPrompt);
        strncpy(codeBuffer, generated.c_str(), sizeof(codeBuffer));
        aiStatus = "Code Generated.";
    }

    ImGui::Spacing();

    // قسم إصلاح الأكواد
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
