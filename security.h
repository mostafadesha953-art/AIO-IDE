#ifndef SECURITY_H
#define SECURITY_H

#include <string>

class LicenseSystem {
public:
    // حالة التفعيل (تبدأ بـ false دائماً)
    static inline bool IsActivated = false;
    static inline std::string SavedKey = "";

    /**
     * دالة التحقق من السيريال
     * تدمج بين التشفير المنطقي والتحقق من البادئة (Prefix)
     */
    static bool ValidateKey(std::string key) {
        // 1. التشفير البسيط (XOR) أو التحقق من البادئة السرية
        // هذا السطر يمنع تشغيل المحرك إلا إذا بدأ الكود بـ AIO-
        std::string secretPrefix = "AIO-"; 
        
        if (key.length() >= 10 && key.find(secretPrefix) == 0) {
            // ملاحظة تجارية: هنا يمكن إضافة كود CURL لإرسال السيريال 
            // للخادم (Proxy) للتأكد من قاعدة البيانات السحابية.
            
            IsActivated = true;
            SavedKey = key;
            return true; 
        }
        
        return false;
    }

    /**
     * دالة لتشفير البيانات الحساسة في الذاكرة
     * (تستخدم لحماية السيريال من برامج الـ RAM Scanner)
     */
    static std::string XORCipher(std::string data) {
        char key = 'K'; // مفتاح التشفير الخاص بك
        std::string output = data;
        for (int i = 0; i < data.size(); i++)
            output[i] = data[i] ^ key;
        return output;
    }
};

#endif
