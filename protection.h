#ifndef PROTECTION_H
#define PROTECTION_H

#include <windows.h>
#include <iostream>

class SecurityShield {
public:
    static void CheckIntegrity() {
        // 1. فحص هل البرنامج يعمل تحت "مصحح أخطاء" (Debugger)
        if (IsDebuggerPresent()) {
            MessageBoxA(NULL, "Security Breach: Debugger Detected!", "AIO Protection", MB_ICONERROR);
            exit(0); // إغلاق فوري
        }

        // 2. فحص "التلاعب بالوقت" (منع تسريع الفترة التجريبية)
        static DWORD lastTick = GetTickCount();
        if (GetTickCount() - lastTick > 5000) { // إذا توقف المعالج فجأة (BreakPoint)
             exit(0);
        }
        lastTick = GetTickCount();
    }

    static void HideThread() {
        // إخفاء خيط المعالجة عن أدوات النسخ
        typedef NTSTATUS (NTAPI *pNtSetInformationThread)(HANDLE, UINT, PVOID, ULONG);
        HMODULE ntdll = GetModuleHandleA("ntdll.dll");
        if (ntdll) {
            auto NtSetInformationThread = (pNtSetInformationThread)GetProcAddress(ntdll, "NtSetInformationThread");
            if (NtSetInformationThread)
                NtSetInformationThread(GetCurrentThread(), 0x11, NULL, 0); // 0x11 = ThreadHideFromDebugger
        }
    }
};

#endif
