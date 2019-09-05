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
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

static const int RXPin = 16, TXPin = 17;

HTTPClient http;
TinyGPSPlus gps;
SoftwareSerial SerialGPS(RXPin,TXPin);

void setup() {
    Serial.begin(115200);
    SerialGPS.begin(115200);
    WiFiManager wifiManager;
    wifiManager.autoConnect("GaboESP32");
    Serial.println("Estoy connectado a la red :D");
}

void loop() {  

    http.begin("https://iot-apps-course.firebaseio.com/position.json");
    http.addHeader("Content-Type","text/plain");
 
    while (SerialGPS.available())
    {
        gps.encode(SerialGPS.read());
        if (gps.location.isUpdated())
        {
            Serial.print ("Latitude= ");
            Serial.print (gps.location.lat(), 6);
            Serial.print ("Latitude= ");
            Serial.print (gps.location.lng(), 6);      
            String payload = "{\"Lat\":" + String(gps.location.lat()) + ", \"Lng\": " + String(gps.location.lat())+"}";
            int httpCode = http.POST(payload);
            Serial.println(httpCode);
            Serial.println(payload);
        }
        
    }

}
