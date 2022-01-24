#include "HX711.h"
#define DOUT  12
#define CLK  13

HX711 scale(DOUT, CLK);
float calibration_factor = 1030;
int GRAM, oldData;
char input;

void setup() {
  Serial.begin(9600);
  scale.set_scale();
  scale.tare();
  long zero_factor = scale.read_average();
  Serial.print("Zero factor: ");
  Serial.println(zero_factor);
  delay(1000);
}

void sensor(){
  scale.set_scale(calibration_factor);
  GRAM = scale.get_units(), 4;

  if (Serial.available()) {
    char temp = Serial.read();
    if (temp == '+' || temp == 'a')
      calibration_factor += 0.1;
    else if (temp == '-' || temp == 'z')
      calibration_factor -= 0.1;
    else if (temp == 's')
      calibration_factor += 10;
    else if (temp == 'x')
      calibration_factor -= 10;
    else if (temp == 'd')
      calibration_factor += 100;
    else if (temp == 'c')
      calibration_factor -= 100;
    else if (temp == 'f')
      calibration_factor += 1000;
    else if (temp == 'v')
      calibration_factor -= 1000;
    else if (temp == 't')
      scale.tare();
  }
}

void loop() {
  sensor();
  if(GRAM != oldData){
    Serial.print("Berat : ");
    Serial.print(GRAM);
    Serial.println();

    oldData = GRAM;
  }

  if(Serial.available()){
      Serial.print("Data saved : " );
      Serial.print(oldData);
      Serial.println();
      Serial.print(GRAM);
      Serial.println();
  }
}
