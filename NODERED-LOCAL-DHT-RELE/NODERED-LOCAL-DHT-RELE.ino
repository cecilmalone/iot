#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"

// Define o tipo do sensor
#define DHTTYPE DHT11


// Conexão com o roteador local
const char* ssid = "Malone";
const char* password = "12345678";

// Endereço do Servidor MQTT no Raspberry Pi IP 
const char* mqtt_server = "test.mosquitto.org";

// Inicia o espClient.
WiFiClient espCecil;
PubSubClient client(espCecil);

const int DHTPin = 5;
const int rele = 4;


// Inicializa o sensor DHT
DHT dht(DHTPin, DHTTYPE);

// Variáveis auxiliares de tempo
long now = millis();
long lastMeasure = 0;

// Conectando o ESP8266 ao roteador
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.print("WiFi connected - ESP IP address: ");
  Serial.println(WiFi.localIP());
}

// Esta função é executada quando os dispositivos publicando mensagens para um tópico que o ESP8266 está subscrito
// Altere a lógica da função, caso necessário, para fazer algo quando receber uma mensagem dos tópicos subscritos
void callback(String topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  // Concatena a String messageTemp
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  // Aqui é possível adicionar alguma lógica para interagir com os GPIOs

  // Se a mensagem for recebida no tópico UHT1/PiraKids, verifique se o que recebeu é
  // "on" ou "off" e ligue ou deslique o motor
  if(topic=="Topico1/Cecil/Equipamento1"){
      Serial.print("Alterando o estado do rele para: ");
      if(messageTemp == "on"){
        digitalWrite(rele, LOW);
        Serial.print("On");
      }
      else if(messageTemp == "off"){
        digitalWrite(rele, HIGH);
        Serial.print("Off");
      }
  }
  Serial.println();
}

// This functions reconnects your ESP8266 to your MQTT broker
// Change the function below if you want to subscribe to more topics with your ESP8266 

// Esta função reconecta o ESP8266 ao MQTT Broker
// Altere a função abaixo para subscrever o dispositivo a outros tópicos

void reconnect() {
  // Loop até conectar
  while (!client.connected()) {
    Serial.print("Tentando conectar ao MQTT Broker...");

    if (client.connect("ESP1_Local")) {
      Serial.println("connected");  
    // Dê subscribe novamente no canal ou em outros canais, se quiser
      client.subscribe("Topico1/Cecil/Equipamento1");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Aguarde 5 segundos para tentar novamente
      delay(5000);
    }
  }
}

void setup() {

  pinMode(rele, OUTPUT);
  dht.begin();
  Serial.begin(115200);
  setup_wifi();
  
  //Configura o MQTT Broker
  client.setServer(mqtt_server, 1883);
  // Configura qual função de callback será chamada
  client.setCallback(callback);

}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  if(!client.loop())
    client.connect("ESP1_Local");

  now = millis();
  // Plublica novos dados a cada 10 segundos - para o DHT11 deve ser acima de 2 segundos 
  if (now - lastMeasure > 5000) {
    lastMeasure = now;
    
  float h = dht.readHumidity();
    float t = dht.readTemperature();
    float f = dht.readTemperature(true);

    if (isnan(h) || isnan(t) || isnan(f)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }

    // Computar a temperatura em Celsius para enviar
    float hic = dht.computeHeatIndex(t, h, false);
    static char temperatureTemp[7];
    dtostrf(hic, 6, 2, temperatureTemp);
    
   
    static char humidityTemp[7];
    dtostrf(h, 6, 2, humidityTemp);

  // Publicando os valores de temperatura e humidade
    client.publish("Topico2/Cecil/Temp", temperatureTemp);
    client.publish("Topico2/Cecil/Umidade", humidityTemp);
    
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print(" %\t Temperature: ");
    Serial.print(t);
    Serial.print(" *C ");
    Serial.print(f);
    Serial.print(" *F\t Heat index: ");
    Serial.print(hic);
    Serial.println(" *C ");
  }
} 
