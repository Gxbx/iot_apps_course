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

HTTPClient http;

void setup() {
    Serial.begin(115200);
    WiFiManager wifiManager;
    wifiManager.autoConnect("GaboESP32");
    Serial.println("Estoy connectado a la red :D");
}

void loop() {  
    http.begin("https://iot-apps-course.firebaseio.com/data.json");
    http.addHeader("Content-Type","text/plain");
 
    String payload = "{\"Temperature\":" + String(temp) + ", \"Humidity\": " + String(hum)+"}";
    int httpCode = http.POST(payload);
    Serial.println(httpCode);
    Serial.println(payload);
}
