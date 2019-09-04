#if defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#else
#include <WiFi.h>
#include <WebServer.h>
#endif

#include <DNSServer.h>
#include <WiFiManager.h>
#include <DHT11.h>
#include <HTTPClient.h>

#define DHTTYPE DHT11

const int PIN_AP = 2;
const int DHTPIN = 27;

DHT11 dht11(DHTPIN);

void setup()
{
    Serial.begin(115200);
    pinMode(PIN_AP,INPUT);
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

        if (WiFi.status()== WL_CONNECTED)
        {
            HTTPClient http;
            Serial.println("Estoy connectado a la red :D");
            int err;
            float temp,hum = 0.0;
            if ((err = dht11.read(hum, temp))==0)
            {
                Serial.print ("Temperatura: ");
                Serial.println (temp);
                Serial.print ("Humedad: ");
                Serial.println (hum);
                http.begin("https://iot-apps-course.firebaseio.com/sensor.json");
                http.addHeader("Content-Type","text/plain");
                String payload = "{\"Temperature\":" + String(temp) + ", \"Humidity\": }" + String(hum);
                int httpCode = http.POST(payload);
            }
            else
            {
                Serial.println("Error del sensor :'(");
            }
        }   
    }    
}