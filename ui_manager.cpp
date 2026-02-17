#define _CRT_SECURE_NO_WARNINGS // لمنع تحذيرات strncpy وتأمين التجميع
#include "ui_manager.h"
#include "ai_engine.h"
#include "security.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <string>
#include <cstring> // ضروري لدالة strncpy

// حالة تشغيل التطبيق
bool g_AppRunning = true;

bool InitSystem() {
    IMGUI_CHECKVERSION();
    if (ImGui::CreateContext() == nullptr) return false;
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
    // ألوان ويندوز 2000 الاحترافية (رمادي وأزرق داكن)
    style.Colors[ImGuiCol_WindowBg]      = ImVec4(0.82f, 0.82f, 0.82f, 1.00f); 
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 0.00f, 0.50f, 1.00f); 
    style.WindowRounding = 0.0f; // حواف حادة تماماً كالنظام الكلاسيكي
}

void RenderIDE() {
    // --- 1. شاشة التفعيل (Security Layer) ---
    // تم استخدام اسم الكلاس LicenseSystem لضمان التعرف على المتغير
    if (!LicenseSystem::IsActivated) {
        ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
        ImGui::Begin("Product Activation", NULL, ImGuiWindowFlags_AlwaysAutoResize);
        
        ImGui::Text("AIO Smart IDE is Locked.\nPlease enter your Serial Key:");
        static char keyInput[64] = ""; // تم تكبير الحجم لضمان الاستقرار
        
        ImGui::InputText("##Key", keyInput, IM_ARRAYSIZE(keyInput));
        
        ImGui::Spacing();
        if (ImGui::Button("Activate License", ImVec2(-1, 0))) {
            if (LicenseSystem::ValidateKey(keyInput)) {
                // سيتم فتح الواجهة تلقائياً في الفريم القادم
            } else {
                // يمكن إضافة رسالة خطأ هنا
            }
        }
        ImGui::End();
        return; 
    }

    // --- 2. واجهة البرنامج الرئيسية (IDE Interface) ---
    static char codeBuffer[1024 * 64] = "// Welcome to AIO Smart IDE\n// Start Coding here...";
    static char aiPrompt[512] = ""; 
    static std::string aiStatus = "AI Assistant Ready.";

    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
    ImGui::Begin("AIO Smart Developer Platform - Licensed Version", &g_AppRunning, 
                 ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);

    // محرر الأكواد (يحتل 70% من العرض)
    ImGui::InputTextMultiline("##Editor", codeBuffer, IM_ARRAYSIZE(codeBuffer), 
                              ImVec2(ImGui::GetWindowWidth() * 0.7f, -1.0f));
    
    ImGui::SameLine();

    // لوحة التحكم والذكاء الاصطناعي (الجانب الأيمن)
    ImGui::BeginGroup();
    
    ImGui::Text("Build & Compile:");
    if (ImGui::Button("Internal Build", ImVec2(160, 35))) { 
        aiStatus = "Compiling internally... (Classic Mode)"; 
    }
    
    ImGui::Separator();
    ImGui::Spacing();

    // خاصية توليد الأكواد (AI Code Generator)
    ImGui::Text("AI Generator Prompt:");
    ImGui::InputText("##Prompt", aiPrompt, IM_ARRAYSIZE(aiPrompt));
    
    if (ImGui::Button("Generate Code", ImVec2(160, 35))) {
        aiStatus = "AI is thinking and writing...";
        std::string generated = AIEngine::GenerateNewCode(aiPrompt);
        strncpy(codeBuffer, generated.c_str(), sizeof(codeBuffer) - 1);
        aiStatus = "New Code Generated successfully.";
    }

    ImGui::Spacing();

    // خاصية تطوير الأكواد (AI Fix)
    if (ImGui::Button("AI Refactor", ImVec2(160, 35))) {
        aiStatus = "AI is optimizing your code...";
        std::string result = AIEngine::RequestRefactor(codeBuffer);
        strncpy(codeBuffer, result.c_str(), sizeof(codeBuffer) - 1);
        aiStatus = "Code Refactored and Optimized.";
    }

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Text("System Log:");
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1, 1, 0, 1)); // لون أصفر للتنبيهات
    ImGui::TextWrapped(aiStatus.c_str());
    ImGui::PopStyleColor();
    
    ImGui::EndGroup();

    ImGui::End();
}
