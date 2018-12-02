#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Atualize para os dados de sua Rede

const char* ssid = "Malone";
const char* password = "12345678";

//Atualize para os dados do seu Broquer MQTT
const char* mqtt_server = "test.mosquitto.org";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;


void setup_wifi() {

  delay(10);
  // Iniciando a tentativa de conectar a rede WiFi
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("Enderço IP: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensagem recebida: [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Alterna o valor do LED para desLigado, quando o primeiro valor no Payload for 1
  if ((char)payload[0] == '1') {
    digitalWrite(D5, HIGH);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is active low on the ESP-01)
  } else {
    digitalWrite(D5, LOW);  // passa energia para o dispositivo ligado na porta D5
  }

}

//Metodo que insisti em tentar se conectar na Rede WiFi
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Tentando conectar ao MQTT...");
    // Cria um ID randomico para o seu dispositivo conectado ao MQTT
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Tentativa para conectar
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      //client.publish("outTopic", "hello world"); //Metodo para publicar no Broquer
      // ... and resubscribe
      client.subscribe("cecil/ledcontrole"); //Metodo para se inscrever no Tópico do Broquer
    } else {
      Serial.print("falha ao conectar no MQTT, rc=");
      Serial.print(client.state());
      Serial.println(" Nova tentaiva em  5 segundos");
      //Espera 5 segundos
      delay(5000);
    }
  }
}

void setup() {
  pinMode(D5, OUTPUT);     // Inicializa o PIN D5 como output
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883); //Seta o MQTT server e a porta
  client.setCallback(callback); //Seta o Callback - chamadas ao NodeMCU
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  
}
