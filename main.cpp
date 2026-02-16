#include "ui_manager.h"

int main() {
    // بدء النظام والرسوميات
    if (!InitSystem()) return 1;

    // تطبيق سمة ويندوز 2000 الكلاسيكية
    ApplyClassicWindowsTheme();

    // حلقة تشغيل البرنامج
    while (IsRunning()) {
        NewFrame();    // بدء إطار رسم جديد
        RenderIDE();   // رسم واجهة المبرمج والذكاء الاصطناعي
        EndFrame();    // إنهاء الرسم وعرضه على الشاشة
    }

    // تنظيف الذاكرة عند الإغلاق
    CleanupSystem();
    return 0;
}
