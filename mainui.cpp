#include "imgui.h"
#include "ai_engine.h"    // استدعاء ملف الذكاء الاصطناعي
#include "compiler.h"     // استدعاء ملف المترجم المدمج
#include "imgui.h"
#include "aichat.h"

void DrawApp() {
    static char codeArea[1024 * 16] = ""; // مخزن الكود
    
    ImGui::Begin("AIO Smart IDE");
    
    // محرر الكود
    ImGui::InputTextMultiline("##editor", codeArea, IM_ARRAYSIZE(codeArea), ImVec2(-1.0f, -100.0f));

    if (ImGui::Button("Run (Internal)")) {
        InternalCompiler::Execute(codeArea); // تنفيذ الكود داخلياً
    }

    ImGui::SameLine();

    if (ImGui::Button("AI Refactor")) {
        std::string optimized = AIEngine::AskAI(codeArea);
        strcpy(codeArea, optimized.c_str()); // تحديث الكود بالذكاء الاصطناعي
    }

    ImGui::End();
}


void RenderChatWindow() {
    static std::vector<Message> chatLog;
    static char inputBuffer[512] = "";
    static bool scrollToBottom = false;

    ImGui::Begin("حوار الذكاء الاصطناعي (AI Assistant)");

    // 1. منطقة عرض الرسائل (Chat History)
    float footerHeight = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
    ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footerHeight), false);
    
    for (const auto& msg : chatLog) {
        if (msg.sender == "User") 
            ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "أنت: "); // لون أخضر
        else 
            ImGui::TextColored(ImVec4(1.0f, 0.8f, 0.0f, 1.0f), "الذكاء الاصطناعي: "); // لون ذهبي
        
        ImGui::TextWrapped("%s", msg.text.c_str());
        ImGui::Separator();
    }

    if (scrollToBottom) { ImGui::SetScrollHereY(1.0f); scrollToBottom = false; }
    ImGui::EndChild();

    // 2. منطقة إدخال النص والزر
    ImGui::PushItemWidth(-70.0f);
    if (ImGui::InputText("##Input", inputBuffer, IM_ARRAYSIZE(inputBuffer), ImGuiInputTextFlags_EnterReturnsTrue)) {
        if (strlen(inputBuffer) > 0) {
            chatLog.push_back({"User", inputBuffer});
            std::string response = AIChat::SendToAI(inputBuffer); // إرسال للخادم
            chatLog.push_back({"AI", response});
            inputBuffer[0] = '\0'; // مسح صندوق الإدخال
            scrollToBottom = true;
        }
    }
    ImGui::PopItemWidth();
    ImGui::SameLine();
    if (ImGui::Button("إرسال")) { /* نفس منطق الضغط على Enter */ }

    ImGui::End();
}

