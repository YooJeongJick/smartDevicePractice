#include <ArduinoJson.h>
void setup() {
  // Initialize serial port
  Serial.begin(115200);
  while (!Serial) continue;
  delay(3000);

  StaticJsonDocument<96> doc;

  char json[] = R"rawliteral({
    "token_type":"bearer",
    "access_token":"c281d73b097",
    "expires_in":43199,
    "refresh_token":"0a0c90af08f",
    "refresh_token_expires_in":5184000,
    "scope":"account_email profile"
  })rawliteral";

  Serial.println(json);
  // Deserialize the JSON document
  DeserializationError error = deserializeJson(doc, json);
  // Test if parsing succeeds.
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }
  // Fetch values.
  const char* access_token = doc["access_token"];
  const char* refresh_token = doc["refresh_token"];
  long expires_in = doc["expires_in"];
  // Print values.
  Serial.print("Access token : ");
  Serial.println(access_token);
  Serial.print("Refresh token : ");
  Serial.println(refresh_token);
  Serial.print("Expire time : ");
  Serial.println(expires_in);
}
void loop() {
  // not used in this example
}