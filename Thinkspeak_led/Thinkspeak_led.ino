#include "ThingSpeak.h"
#include <ESP8266WiFi.h>

const char* ssid     = "FASAM";
const char* password = "#fasam2018";

unsigned long channel = 623696;

unsigned int led1 = 1;
unsigned int led2 = 2;
unsigned int led3 = 3;

int d1 = 5;
int d2 = 4;
int d3 = 0;

WiFiClient  client;


void setup() {
  Serial.begin(115200);
  delay(100);
  
  pinMode(d1, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(d3, OUTPUT);
  digitalWrite(d1, 0);
  digitalWrite(d2, 0);
  digitalWrite(d3, 0);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Netmask: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: ");
  Serial.println(WiFi.gatewayIP());
  ThingSpeak.begin(client);

}

void loop() {

  int led_1 = ThingSpeak.readFloatField(channel, led1);
  int led_2 = ThingSpeak.readFloatField(channel, led2);
  int led_3 = ThingSpeak.readFloatField(channel, led3);

  if(led_1 == 1){
    digitalWrite(d1, 1);
    Serial.println("D1 is On..!");
  }
  else if(led_1 == 0){
    digitalWrite(d1, 0);
    Serial.println("D1 is Off..!");
  }

  if(led_2 == 1){
    digitalWrite(d2, 1);
    Serial.println("D2 is On..!");
  }
  else if(led_2 == 0){
    digitalWrite(d2, 0);
    Serial.println("D2 is Off..!");
  }

  if(led_3 == 1){
    digitalWrite(d3, 1);
    Serial.println("D3 is On..!");
  }
  else if(led_3 == 0){
    digitalWrite(d3, 0);
    Serial.println("D3 is Off..!");
  }
    
  Serial.println(led_1);
  Serial.println(led_2);
  Serial.println(led_3);
  delay(1000);

}
