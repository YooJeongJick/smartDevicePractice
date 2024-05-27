#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(9600);

  // OLED 디스플레이 초기화
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 오류");
    while (true);
  }

  // OLED 디스플레이 클리어
  display.clearDisplay();
}

void loop() {
  display.clearDisplay();
  display.display();
  delay(2000);
}
