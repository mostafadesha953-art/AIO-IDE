#include <iostream>
#include <string>
#include <curl/curl.h> // المكتبة الأساسية للإنترنت

// دالة تقنية لاستلام البيانات من السيرفر وتخزينها في نص (String)
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    userp->append((char*)contents, size * nmemb);
    return size * nmemb;
}

class AIChat {
public:
    static std::string SendToAI(std::string userMessage) {
        CURL* curl;
        CURLcode res;
        std::string readBuffer;

        curl = curl_easy_init();
        if(curl) {
            // استبدل هذا الرابط برابط خادم البايثون الخاص بك
            std::string serverUrl = "https://yourname.pythonanywhere.com";
            
            // تجهيز البيانات لإرسالها بصيغة JSON
            std::string jsonData = "{\"code\": \"" + userMessage + "\"}";

            struct curl_slist* headers = NULL;
            headers = curl_slist_append(headers, "Content-Type: application/json");

            curl_easy_setopt(curl, CURLOPT_URL, serverUrl.c_str());
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonData.c_str());
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

            // تنفيذ الإرسال
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);

            if(res != CURLE_OK) return "خطأ في الاتصال بالخادم!";
        }
        return readBuffer; // يعود بالرد الذكي (JSON)
    }
};
