#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
#include <WiFiClient.h>
#include "dht.h"

const char* ssid     = "";
const char* password = "";
const char light = A0;

#define dht_apin 4 //This is the GPIO pin number, not the psysical number on the board

WiFiClient client;
unsigned long myChannelNumber = 1685990;
const char* myWriteAPIKey = "0OI86N43DVCLRWQT";
dht DHT;

void setup() {
  Serial.begin(115200);
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

  ThingSpeak.begin(client);
  pinMode(light, INPUT);
}

void loop() {

  DHT.read11(dht_apin);
  int lightInput = analogRead(light);
  int lightInputCompressed = map(lightInput,0,1024,0,100);
  
  float humidity = DHT.humidity;
  float temp = DHT.temperature;
  
  Serial.print("Temp - ");
  Serial.print(temp);
  Serial.print(" | Humidity % - ");
  Serial.println(humidity);

 Serial.println("Uploading to Thingspeak server.");
  ThingSpeak.writeField(myChannelNumber, 1,lightInputCompressed, myWriteAPIKey);
  delay(15000);
  ThingSpeak.writeField(myChannelNumber, 2,temp, myWriteAPIKey);
  delay(15000);


}
