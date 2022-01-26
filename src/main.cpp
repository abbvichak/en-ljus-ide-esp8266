#include <Arduino.h>
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

#define FIREBASE_HOST "en-ljus-ide-grupp-9-default-rtdb.europe-west1.firebasedatabase.app"
#define FIREBASE_AUTH "E60yxzKHFsrGH5EaXaszig5WPutRHwwvYZYaYX7u"
#define WIFI_SSID "ABBgym_2.4"
#define WIFI_PASSWORD "mittwifiarsabra"

FirebaseData firebaseData;

const byte Ledstrip = D5;

bool buttonstate;

void setup() {
  Serial.begin(9600);
  pinMode(Ledstrip, OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  if (!Firebase.beginStream(firebaseData, "bruh"))
  {
      Serial.println("Could not begin stream");
      Serial.println("REASON: " + firebaseData.errorReason());
      Serial.println();
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}