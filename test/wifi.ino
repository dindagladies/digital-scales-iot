
#include <ESP8266WiFi.h>

//SSID of your network
char ssid[] = "Iphone";        // your network SSID (name)
char pass[] = "asdfasdf123";

void setup()
{
  Serial.begin(9600);
  delay(10);

  // Connect to Wi-Fi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to...");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".hjkuiuuuuuu");
  }
  Serial.println("");
  Serial.println("Wi-Fi connected successfully");
}

void loop () {}
