int time_red = 6000;
int time_yellow = 500;
int time_green = 3000;
int d0 = 16;
int d1 = 5;
int d2 = 4;

void setup() {
  pinMode(d0, OUTPUT); // D0 - Amarelo
  pinMode(d1, OUTPUT); // D1 - Verde
  pinMode(d2, OUTPUT); // D2 - Vermelho
}

void loop() {
  digitalWrite(d2, HIGH);
  delay(time_red);
  digitalWrite(d2, LOW);
  digitalWrite(d0, HIGH);
  delay(time_yellow);
  digitalWrite(d0, LOW);
  digitalWrite(d1, HIGH);
  delay(time_green);
  digitalWrite(d1, LOW);
}
