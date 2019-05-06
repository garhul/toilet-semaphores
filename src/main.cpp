#include <Arduino.h>
#include <Hash.h>
#include <creds.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <MQTT.h>


const byte interruptPin = 13;
volatile byte interruptCounter = 0;
int numberOfInterrupts = 0;

WiFiClient net;
MQTTClient client;

unsigned long lastMillis = 0;

void connect() {
  Serial.print("connecting to wifi");
  while (WiFi.status() != WL_CONNECTED){
    delay(10);
  }

  Serial.print("\nConnecting to broker");
  while (!client.connect("arduino", "try", "try")) {
    Serial.print(".");
    delay(10);
  }

  Serial.println("\nconnected!");
}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);
}

void setup() {
  int start = millis();
  digitalWrite(BUILTIN_LED, LOW);

  Serial.begin(115200);
  Serial.println(""); Serial.print("Startup reason :");Serial.println(ESP.getResetReason());

  WiFi.begin(LOCAL_SSID, LOCAL_PWD);
  client.begin(BROKER, net);
  //client.onMessage(messageReceived);
  connect();

  float val = analogRead(A0) * VBAT_MULTIPLIER;
  client.publish("/sensor/toilet_0/vbat", "Battery level is " + String(val,10)+"V");
  Serial.println("Battery level is" + String(val,10));

  delay(10);

  Serial.println("Waking time: ");Serial.print(millis()-start);Serial.println("ms");
  Serial.println("Go to deep sleep");
  ESP.deepSleep(10e6);
}

void loop() { }
