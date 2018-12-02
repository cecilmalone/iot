/* Teste inicial da Porta Serial */
/*void setup() {
  Serial.begin(9600);
  Serial.println("Gerando valores sequencias.");

  }

  int numero = 0;

  void loop() {
  Serial.print("Valor: ");
  Serial.println(numero);
  delay(500);
  numero++;
  }*/

/* Exibindo valores em diferentes sistemas de numeração */
int valor = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Exibindo valores em sistemas diversos");
}

void loop() {
  for (valor = 0; valor <= 255; valor++) {
    Serial.print("DEC: ");
    Serial.print(valor);
    Serial.print(" HEX: ");
    Serial.print(valor, HEX);
    Serial.print(" BIN: ");
    Serial.println(valor, BIN);

    delay(200);
  }

  /* Se o valor for 255, não repetir mais a geração de números.
    Entrar nesse loop para sempre:
  */
  if (valor >= 255) {
    while (true) {
      continue;
    }
  }
}
