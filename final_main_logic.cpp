#include "imgui.h"
#include "AIChat_Connector.cpp"

void DrawFinalInterface() {
    static char codeBuffer[1024 * 32] = ""; // منطقة الكود
    static std::string aiStatus = "الذكاء الاصطناعي جاهز...";

    ImGui::Begin("AIO Developer Platform");

    // الجزء الأيسر: محرر الأكواد
    ImGui::BeginChild("Editor", ImVec2(ImGui::GetWindowWidth() * 0.6f, 0), true);
    ImGui::Text("كود البرمجة (C++, Python, etc.):");
    ImGui::InputTextMultiline("##source", codeBuffer, IM_ARRAYSIZE(codeBuffer), ImVec2(-1, -1));
    ImGui::EndChild();

    ImGui::SameLine();

    // الجزء الأيمن: حوار الذكاء الاصطناعي
    ImGui::BeginChild("AI_Chat", ImVec2(0, 0), true);
    ImGui::Text("مساعد البرمجة الذكي:");
    if (ImGui::Button("تحليل الكود وترقيته عبر الويب 3")) {
        aiStatus = "جاري التحليل...";
        std::string result = AIChat::SendToAI(codeBuffer);
        // هنا نقوم بتحديث كود المحرر بالنتيجة الجديدة
        strncpy(codeBuffer, result.c_str(), sizeof(codeBuffer));
        aiStatus = "تم التحديث بنجاح!";
    }
    ImGui::TextWrapped("%s", aiStatus.c_str());
    ImGui::EndChild();

    ImGui::End();
}
