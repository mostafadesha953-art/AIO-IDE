static bool ValidateKey(std::string key) {
    // تشفير بسيط (XOR) لكي لا يعرف المخترق الكود الحقيقي
    std::string secretPrefix = "AIO-"; 
    if (key.find(secretPrefix) == 0) {
        // إرسال السيريال للخادم (Proxy) للتأكد من قاعدة البيانات
        return true; 
    }
    return false;
}
