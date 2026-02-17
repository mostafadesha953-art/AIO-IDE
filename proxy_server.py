from flask import Flask, request, jsonify
from openai import OpenAI
import os

app = Flask(_name_)

# 1. إعداد مفتاح API (يفضل وضعه في متغيرات البيئة للأمان القصوى)
client = OpenAI(api_key="YOUR_OPENAI_API_KEY")

# 2. قائمة السيريالات المفعلة (يمكنك ربطها بقاعدة بيانات مستقبلاً)
# حالياً سنضع قائمة بسيطة للتحقق
VALID_LICENSES = ["AIO-9988-7766", "AIO-1122-3344", "AIO-BOSS-2024"]

@app.route('/refactor', methods=['POST'])
def handle_ai_requests():
    # استلام البيانات من برنامج الـ C++
    data = request.json
    user_code = data.get('code', '')
    user_prompt = data.get('prompt', '') # للطلب الجديد (توليد كود)
    license_key = data.get('license_key', '')
    request_type = data.get('type', 'refactor') # تحديد نوع الطلب

    # --- نظام الحماية (Security Layer) ---
    if license_key not in VALID_LICENSES:
        return jsonify({"error": "Unauthorized: Invalid License Key"}), 403

    try:
        # صياغة الطلب بناءً على نوع العملية
        if request_type == "generate":
            system_msg = "You are a professional software architect. Generate complete, clean code based on the user description."
            user_msg = f"Generate this code: {user_prompt}"
        else:
            system_msg = "You are a senior developer. Optimize and fix the following code for high performance."
            user_msg = f"Optimize this code: {user_code}"

        # إرسال الطلب لـ GPT-4
        response = client.chat.completions.create(
            model="gpt-4",
            messages=[
                {"role": "system", "content": system_msg},
                {"role": "user", "content": user_msg}
            ]
        )

        return jsonify({
            "refined_code": response.choices[0].message.content,
            "status": "success"
        })

    except Exception as e:
        return jsonify({"error": str(e)}), 500

if _name_ == '_main_':
    # تشغيل الخادم (سيتم رفعه على PythonAnywhere)
    app.run(host='0.0.0.0', port=5000)
