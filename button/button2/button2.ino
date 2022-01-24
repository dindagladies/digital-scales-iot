int btn = 2;

void setup() {
  Serial.begin(9600);
  pinMode(btn, INPUT_PULLUP);

}

void loop() {
  int x = digitalRead(btn);
//  Serial.print("Kondisi = ");
//  Serial.println(x);
  if(x == 0){
    Serial.print("Kepencet");
    Serial.println();
  }
//  else if(x == 0){
//    Serial.print("Kepencettt!!!!!!!!!!!!!!!!!!!!!");
//    Serial.println(x);
//  }

}
