#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
WiFiClient client;
HTTPClient http;
#include "HX711.h"
#define DOUT  12
#define CLK  13
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Connection
char ssid[] = "Srikandi";
char pass[] = "Herro897";
char host[] = "124.40.249.86:1001";
String url;
long data;
unsigned long current = 0, prev = 0, interval = 2000;
boolean start = true;

// Sensor
HX711 scale(DOUT, CLK);
float calibration_factor = 1030;
int GRAM, oldData;
char input;
int btn = 2;

// Set the LCD address to 0x27
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  delay(10);

  lcd.begin();
  lcd.backlight();
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Connecting to ...");
  lcd.setCursor(1,1);
  lcd.print(ssid);
  
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Wi-Fi connected successfully");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Wi-Fi connected");
  lcd.setCursor(1,1);
  lcd.print("Mulai menimbang");
  
  // Sensor
  scale.set_scale();
  scale.tare();
  delay(1000);

  // Button
  pinMode(btn, INPUT_PULLUP);

}

void sensor() {
  scale.set_scale(calibration_factor);
  GRAM = scale.get_units(), 4;
}

void sendData(int data){

  // Send Data
  url = "http://124.40.249.86:1001/sensor/store?data=";
  url += data;

  http.begin(client, url);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  int httpCode = http.POST(url);   //Send the request
  String payload = http.getString();    //Get the response payload

  Serial.println(httpCode);
  Serial.print(payload);
  lcd.clear();
  lcd.print(payload);
  http.end();
}

void loop() {
  // Button
  int x = digitalRead(btn);
  
  // Sensor
  sensor();
  if(GRAM != oldData){
    // lcd
    lcd.clear();
    lcd.print("Berat : ");
    lcd.print(GRAM);
    lcd.print(" gram");

    oldData = GRAM;
  }

  // Send Data
  if(x == 0){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Data tersimpan : " );
    lcd.setCursor(1,1);
    lcd.print(GRAM);
    lcd.print(" gram");
    // Send Data
    current = millis();
    if (current - prev > interval)
    {
      lcd.clear();
      Serial.print("Data Tersimpan");
      lcd.print("Data Tersimpan");
      sendData(GRAM);
      prev = current;
    }
  }
}
