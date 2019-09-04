#if defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#else
#include <WiFi.h>
#include <WebServer.h>
#endif

#include <DNSServer.h>
#include <WiFiManager.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTTYPE DHT11

const int PIN_AP = 2;
const int DHTPIN = 27;

DHT dht(DHTPIN, DHTTYPE);

void setup()
{
    Serial.begin(115200);
    pinMode(PIN_AP,INPUT);
    dht.begin();
    WiFiManager wifiManager;
    wifiManager.autoConnect("GaboESP32","123456");
}
void loop ()
{
    WiFiManager wifiManager;
    if (digitalRead(PIN_AP)== HIGH)
    {
        if (!wifiManager.startConfigPortal("GaboESP32","123456"))
        {
            delay(2000);
            ESP.restart();
            delay(1000);
        } 

        Serial.println("Estoy connectado a la red :D");
        Serial.println (dht.readHumidity());
        Serial.println (dht.readTemperature());
    }    
}