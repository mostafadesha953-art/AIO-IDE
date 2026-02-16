from flask import Flask, request, jsonify
import openai

app = Flask(_name_)

# ضع مفتاحك هنا (سيكون آمناً لأنه على الخادم وليس في جهاز المستخدم)
openai.api_key = "YOUR_OPENAI_API_KEY"

@app.route('/refactor', methods=['POST'])
def refactor_code():
    user_code = request.json.get('code')
    
    # إرسال الطلب لـ AI
    response = openai.ChatCompletion.create(
      model="gpt-4",
      messages=[{"role": "user", "content": f"Optimize this: {user_code}"}]
    )
    
    return jsonify({"refined_code": response.choices[0].message.content})

if _name_ == '_main_':
    app.run(port=5000) # تشغيل الخادم