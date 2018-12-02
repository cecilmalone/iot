int d2 = 4;

void setup() {
  pinMode(d2, OUTPUT);

}

void loop() {
  digitalWrite(d2, HIGH);
  delay(5000);
  digitalWrite(d2, LOW);
  delay(5000);
}
