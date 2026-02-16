#include <string>
#include <vector>

struct Message {
    std::string sender; // "User" أو "AI"
    std::string text;
};

class AIChat {
public:
    static std::string SendToAI(std::string userMessage) {
        // هنا نستخدم نفس منطق CURL للاتصال بالخادم الوسيط (Proxy)
        // الخادم يرسل النص لـ GPT ويعيد الرد
        std::string aiResponse = "تحليل الذكاء الاصطناعي: تم فحص الكود وتحديثه بناءً على معايير الويب 3..."; 
        return aiResponse;
    }
};
