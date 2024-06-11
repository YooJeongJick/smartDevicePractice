const int soilSensorPin = 34;

 void setup(){
 Serial.begin(115200);
 }

 void loop(){
 Serial.print("토양습도센서값:");
 Serial.println(analogRead(soilSensorPin));
 delay(1000);
 }