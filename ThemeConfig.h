void ApplyClassicTheme() {
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    // إعدادات الألوان الكلاسيكية (رمادي مع أزرق)
    colors[ImGuiCol_WindowBg]          = ImVec4(0.82f, 0.82f, 0.82f, 1.00f); // رمادي ويندوز 2000
    colors[ImGuiCol_TitleBgActive]      = ImVec4(0.00f, 0.00f, 0.50f, 1.00f); // أزرق شريط العنوان
    colors[ImGuiCol_Button]             = ImVec4(0.70f, 0.70f, 0.70f, 1.00f);
    colors[ImGuiCol_Text]               = ImVec4(0.00f, 0.00f, 0.00f, 1.00f); // نص أسود
    colors[ImGuiCol_FrameBg]            = ImVec4(1.00f, 1.00f, 1.00f, 1.00f); // خلفية المحرر بيضاء

    style.WindowRounding = 0.0f; // زوايا حادة كلاسيكية
    style.FrameRounding = 0.0f;
}