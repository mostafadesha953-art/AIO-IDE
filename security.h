#ifndef SECURITY_H
#define SECURITY_H

#include <string>
#include <windows.h>

class LicenseSystem {
public:
    static inline bool IsActivated = false;
    static inline int FailedAttempts = 0; // عداد المحاولات الفاشلة

    static bool ValidateKey(std::string key) {
        std::string secretPrefix = "AIO-"; 
        
        if (key.length() >= 10 && key.find(secretPrefix) == 0) {
            IsActivated = true;
            return true; 
        } else {
            FailedAttempts++;
            // --- كود التدمير الذاتي (إغلاق البرنامج بعد 5 محاولات) ---
            if (FailedAttempts >= 5) {
                MessageBoxA(NULL, "Security Alert: Too many failed attempts! System shutting down.", "AIO Shield", MB_ICONSTOP);
                exit(0); 
            }
            return false;
        }
    }
};

#endif
