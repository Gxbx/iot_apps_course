#if defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#else
#include <WiFi.h>
#include <WebServer.h>
#endif

#include <DNSServer.h>
#include <WiFiManager.h>

const int PIN_AP = 2;

void setup()
{
    Serial.begin(115200);
    pinMode(PIN_AP,INPUT);

    WiFiManager wifiManager;

    wifiManager.setAPCallback(configModeCallback(wifiManager));
    wifiManager.setSaveConfigCallback(saveConfigCallback());

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
    }    
}

void configModeCallback (WifiManager *wiFiManager)
{
    Serial.println("Modo de configuración...");
    Serial.println(WiFi.softAPIP());
    Serial.println(wiFiManager->getConfigPortalSSID());
}

void saveConfigCallback ()
{
    Serial.println("Configuración guardada");
    Serial.println(WiFi.softAPIP());
}
