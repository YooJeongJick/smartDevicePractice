#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "WEBSERVER";          // WiFi 네트워크 이름
const char* password = "20240403";  // WiFi 비밀번호

String output2State = "off";  // GPIO 핀의 초기 상태
const int output2 = 2;        // GPIO 핀 번호

AsyncWebServer server(80);    // 서버 포트 설정

void setup() {
  Serial.begin(115200);
  pinMode(output2, OUTPUT);   // GPIO 핀을 출력으로 설정
  digitalWrite(output2, LOW); // 초기 상태를 LOW로 설정

  // WiFi에 연결
  WiFi.begin(ssid, password);
  Serial.print("WiFi 연결 중");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("연결된 WiFi 네트워크: ");
  Serial.println(WiFi.SSID());
  Serial.print("IP 주소: ");
  Serial.println(WiFi.localIP());

  // 루트 경로 설정
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    String message = "GPIO 2 현재 상태: " + output2State;
    request->send(200, "text/plain; charset=utf-8", message);  // Content-Type에 charset=utf-8 추가
  });

  // GPIO 핀 ON 설정 경로
  server.on("/2/on", HTTP_GET, [] (AsyncWebServerRequest *request) {
    Serial.println("GPIO 2 ON");
    output2State = "on";
    digitalWrite(output2, HIGH);
    String message = "GPIO 2 변경됨: ON";
    request->send(200, "text/plain; charset=utf-8", message);  // Content-Type에 charset=utf-8 추가
  });

  // GPIO 핀 OFF 설정 경로
  server.on("/2/off", HTTP_GET, [] (AsyncWebServerRequest *request) {
    Serial.println("GPIO 2 OFF");
    output2State = "off";
    digitalWrite(output2, LOW);
    String message = "GPIO 2 변경됨: OFF";
    request->send(200, "text/plain; charset=utf-8", message);  // Content-Type에 charset=utf-8 추가
  });

  server.begin();  // 웹 서버 시작
}

void loop() {
}