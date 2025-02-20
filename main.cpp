#include <Arduino.h>
#include "DHT.h"
#include <WiFi.h>
#include "ThingSpeak.h"
#include "Adafruit_Sensor.h"

DHT dht(15, DHT11);
WiFiClient wc;
const char* ssid = "TECNO SPARK 30 Pro";
const char* pass = "12345678";

int channel = 1;
const char* API = "IRJ7J3OP8T574753";

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHT11 test"));
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  Serial.println("\n dang ket noi toi wifi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(100);
  }
  Serial.println("Da ket noi... local ESP32 IP: ");
  Serial.println( WiFi.localIP());

  ThingSpeak.begin(wc);

  dht.begin();
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h)||isnan(t))
  {
    Serial.println(F("dell co"));
  }

  Serial.println(F("do am: "));
  Serial.println(h);
  Serial.println(F("nhiet do: "));
  Serial.println(t);

  int x = ThingSpeak.writeField(2, 1, t, API);
  delay(500);
  int y = ThingSpeak.writeField(2, 2, h, API);
  if (x == 200 && y == 200){
    Serial.println("Success");
  }
  else{
    Serial.println("error");
  }

  delay(500);
  
}

