#if defined(ESP8266)
#include <ESP8266WiFi.h>          
#else
#include <WiFi.h>          
#endif

#include <DNSServer.h>
#if defined(ESP8266)
#include <ESP8266WebServer.h>
#else
#include <WebServer.h>
#endif
#include <WiFiManager.h> 
#include <HTTPClient.h>   
#include <DHT11.h>     

const int DHTPIN = 27;
DHT11 dht11(DHTPIN);
HTTPClient http;
void setup() {
    Serial.begin(115200);
    WiFiManager wifiManager;
    wifiManager.autoConnect("GaboESP32");
    Serial.println("Estoy connectado a la red :D");
}

void loop() {  
    float temp,hum = 0.0;
    int err;
    http.begin("https://iot-apps-course.firebaseio.com/data.json");
    http.addHeader("Content-Type","text/plain");
    if ((err = dht11.read(hum, temp))==0)
    {
        Serial.print ("Temperatura: ");
        Serial.println (temp);
        Serial.print ("Humedad: ");
        Serial.println (hum);
        String payload = "{\"Temperature\":" + String(temp) + ", \"Humidity\": " + String(hum)+"}";
        int httpCode = http.POST(payload);
        Serial.println(httpCode);
        Serial.println(payload);
        delay(3000);
    }
    else{
        Serial.println("Error del sensor :'(");
    }
}