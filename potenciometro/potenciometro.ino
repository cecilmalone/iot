int analogPin = 3;

int val = 0;

void setup() {
  Serial.begin(9600);

}

void loop() {
  val = analogRead();
  Serial.println("Digital = ");

  double v = 5.0 * val / 1023.0

  Serial.print("Analógico = ");
  Serial.println(v);

  Serial.println();

}
