#include "ui_manager.h"
#include "protection.h"  // محرك الحماية الفولاذي
#include "security.h"    // نظام التراخيص والسيريالات

int main() {
    // 1. إخفاء خيط المعالجة عن برامج الكراك والمخترقين (Anti-Tamper)
    SecurityShield::HideThread();

    // 2. فحص أولي لأمان النظام ومنع تشغيل البرنامج داخل Debugger
    SecurityShield::CheckIntegrity();

    // 3. بدء النظام والرسوميات (DirectX 11)
    if (!InitSystem()) {
        return 1;
    }

    // 4. تطبيق سمة ويندوز 2000 الكلاسيكية الرمادية لتقليل استهلاك الموارد
    ApplyClassicWindowsTheme();

    // 5. حلقة تشغيل البرنامج الرئيسية (The Core Loop)
    while (IsRunning()) {
        // فحص الأمان في كل "إطار" لضمان عدم اختراق البرنامج أثناء عمله
        SecurityShield::CheckIntegrity();

        // بدء إطار رسم جديد للواجهة الرسومية
        NewFrame();

        // رسم واجهة المبرمج (تشمل شاشة التفعيل أو محرر الأكواد والذكاء الاصطناعي)
        RenderIDE();

        // إنهاء الرسم وعرض المحتوى على الشاشة
        EndFrame();
    }

    // 6. تنظيف الذاكرة وإغلاق المحركات الرسومية عند الخروج
    CleanupSystem();

    return 0;
}
اكتب إلى مصطفى البحيرى
