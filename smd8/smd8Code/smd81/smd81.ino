#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebSrv.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

const char* ssid = "WEBSERVER";
const char* password = "20240403";

#define DHTPIN 18     // DHT 센서에 연결된 디지털 핀
#define DHTTYPE DHT11    

// 온습도 센서 객체 생성
DHT dht(DHTPIN, DHTTYPE);

// 80번 포트에서 AsyncWebServer 객체 생성
AsyncWebServer server(80);

// DHT 온도 읽기 함수
String readDHTTemperature() {
  // 센서 읽기는 최대 2초가 소요될 수 있습니다. (센서가 매우 느립니다.)
  // 기본값으로 섭씨로 온도 읽기
  float t = dht.readTemperature();
  // 화씨로 온도 읽으려면 매개 변수를 true로 설정
  //float t = dht.readTemperature(true);
  // 읽기 실패 시 조기에 종료하고 다시 시도합니다.
  if (isnan(t)) {
    Serial.println("DHT 센서에서 읽기 실패!");
    return "--";
  }
  else {
    Serial.println(t);
    return String(t);
  }
}

// DHT 습도 읽기 함수
String readDHTHumidity() {
  // 센서 읽기는 최대 2초가 소요될 수 있습니다. (센서가 매우 느립니다.)
  float h = dht.readHumidity();
  if (isnan(h)) {
    Serial.println("DHT 센서에서 읽기 실패!");
    return "--";
  }
  else {
    Serial.println(h);
    return String(h);
  }
}

void setup(){
  // 디버깅용 시리얼 포트 설정
  Serial.begin(115200);

  dht.begin();

  // Wi-Fi 연결
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Wi-Fi에 연결 중...");
  }

  // ESP32 로컬 IP 주소 출력
  Serial.println(WiFi.localIP());

  // 루트(/) 웹 페이지 라우팅
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    String temperature = readDHTTemperature();
    String humidity = readDHTHumidity();
    String response = "온도 " + temperature + "\n습도 " + humidity;
    request->send(200, "text/plain; charset=utf-8", response);
  });

  // 서버 시작
  server.begin();
}

void loop(){
}
