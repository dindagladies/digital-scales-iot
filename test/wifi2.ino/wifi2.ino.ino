#include <ESP8266WiFi.h>
#define USE_SERIAL Serial

char ssid[] = "cagak listrik";
char pass[] = "asdfasdf";


void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
   WiFi.begin(ssid, pass);
   USE_SERIAL.print("Test");

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Test");

}
