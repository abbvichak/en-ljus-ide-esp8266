#include <Arduino.h>
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

#include "secret.h"
#include "config.h"

// Globals
#if TYPE != 2
FirebaseData r, g, b, on;
#else
FirebaseData power, on;
#endif

// Functions
bool subscribe(FirebaseData &data, const char *path) {
  if (!Firebase.beginStream(data, path)) {
      Serial.println("Could not begin stream");
      Serial.println("REASON: " + data.errorReason());
      return false;
  }
  return true;
}

void read_data(FirebaseData& data) {
  if (!Firebase.readStream(data))
  {
    Serial.println(data.errorReason());
  }
  if (data.streamTimeout())
  {
      Serial.println("Stream timeout, resume streaming...");
      Serial.println();
  }
}

// Code
void setup() {
  Serial.begin(9600);
  pinMode(AO_RED,OUTPUT);
  pinMode(AO_GREEN,OUTPUT);
  pinMode(AO_BLUE,OUTPUT);

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

#if TYPE == 0
  if(!(subscribe(r,  "/lamp_left/r")
    && subscribe(g,  "/lamp_left/g")
    && subscribe(b,  "/lamp_left/b")
    && subscribe(on, "/lamp_left/on"))) {
    while(1) Serial.println("bruh");
  }
#elif TYPE == 1
  if(!(subscribe(r,  "/lamp_right/r")
    && subscribe(g,  "/lamp_right/g")
    && subscribe(b,  "/lamp_right/b")
    && subscribe(on, "/lamp_right/on"))) {
    while(1) Serial.println("bruh");
  }
#else
  if(!(subscribe(power,  "/lamp_right/power")
    && subscribe(on,     "/lamp_right/on"))) {
    while(1) Serial.println("bruh");
  }
#endif
}

void loop() {
#if TYPE != 2
  read_data(r);
  read_data(g);
  read_data(b);
  read_data(on);
#else
  read_data(power);
  read_data(on);
#endif

  Serial.println(on.boolData());
  Serial.println(on.intData());
  Serial.println(on.streamAvailable());
  if(on.boolData()) {
#if TYPE != 2
    analogWrite(AO_RED,   r.intData());
    analogWrite(AO_GREEN, g.intData());
    analogWrite(AO_BLUE,  b.intData());
    Serial.printf("r%d g%d b%d\n", r.intData(), g.intData(), b.intData());
#else
    analogWrite(AO_POWER, power.intData());
#endif
  } else {
#if TYPE != 2
    analogWrite(AO_RED,   0);
    analogWrite(AO_GREEN, 0);
    analogWrite(AO_BLUE,  0);
    Serial.println("off");
#else
    analogWrite(AO_POWER, 0);
#endif
  }
}
