int btn = 2;
void setup() {
  Serial.begin(9600);
  pinMode(btn, INPUT);

}

void loop() {
  int x = digitalRead(btn);
  Serial.print("kondisi = ");
  Serial.println(x);

}
