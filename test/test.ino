#include <ESP8266WiFi.h>

// Connection
char ssid[] = "Srikandi";
char pass[] = "Herro897";
//char host[] = "192.168.8.115";
char host[] = "124.40.249.86:1001";

// Variable
WiFiClient client;
const int httpPort = 1002;
String url;
long data;
unsigned long timeout;
boolean start = true;

void setup() {
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
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Wi-Fi connected successfully");

}

void sensor() {
  data = 100;
  Serial.print(data);

}
void loop() {

  if (start == true) {
    // Read sensor
    Serial.print("Baca sensor");
    sensor();

    Serial.print("connecting to");
    Serial.println(host);

    if (!client.connect(host, httpPort)) {
      Serial.println("connection failed!");
    }


    // Request URI
    url = "/sensor/store?data=";
//    url = "/cmos/sensor/store?data=";
    url += data;

    Serial.print("Requesting URL: ");
    Serial.println(url);

    // Send request to server
    client.print(String("GET ") + url + " HTTP/1.0\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");
    timeout = millis();
    while (client.available() == 0)
    {
      if (millis() - timeout > 5000)
      {
        Serial.println(">>> Client Timeout !");
        client.stop();
        return;
      }
    }

    while (client.available())
    {
      String line = client.readStringUntil('\r');
      Serial.print(line);
    }

    Serial.println();
    Serial.println("Closing Connetion");
    Serial.println();
    delay(5000);
  }

  start = false;
}
