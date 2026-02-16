#include <iostream>
#include <string>
#include <windows.h> // للوصول لبيئة النظام

class Config {
public:
    static std::string GetAPIKey() {
        // الطريقة الأكثر أماناً: جلب المفتاح من متغيرات البيئة (Environment Variables)
        char* key = std::getenv("AIO_IDE_KEY");
        if (key == nullptr) {
            return "NOT_FOUND";
        }
        return std::string(key);
    }
};
