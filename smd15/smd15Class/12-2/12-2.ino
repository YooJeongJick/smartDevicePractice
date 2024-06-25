#include <ArduinoJson.h>

void setup() {
  Serial.begin(115200);
  while (!Serial) continue;

  delay(3000);

  StaticJsonDocument<256> doc;

  doc["object_type"] = "text";
  doc["text"] = "텍스트 영역입니다. 최대 " + String(200)+ "자 표시 가능합니다.";

  doc["link"]["web_url"]  = "https://developers.kakao.com";
  doc["link"]["mobile_web_url"] = "https://developers.kakao.com";

  doc["button_title"] = "바로 확인";

  String jsonString ;
  String jsonPretyString ;

  // 최소화된 JSON을 생성하여 직렬 포트로 보냅니다.
  serializeJson(doc, jsonString);
  Serial.println(jsonString);
  /*
   { "object_type": "text", "text": "텍스트 영역입니다. 최대 200자 표시 가능합니다.", "link": { "web_url": "https://developers.kakao.com", "mobile_web_url": "https://developers.kakao.com" }, "button_title": "바로 확인" }
  */

  Serial.println();

  // prettified JSON을 생성하고 직렬 포트로 보냅니다.
  serializeJsonPretty(doc, jsonPretyString);
  Serial.println(jsonPretyString);
  /*
   {
        "object_type": "text",
        "text": "텍스트 영역입니다. 최대 200자 표시 가능합니다.",
        "link": {
            "web_url": "https://developers.kakao.com",
            "mobile_web_url": "https://developers.kakao.com"
        },
        "button_title": "바로 확인"
    }
  */
}

void loop() {
}
