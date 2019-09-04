#include <WiFi.h>

const char* ssid = "Emprendedores";
const char* password = "AxtVvm13";

void scanNetworks()
{
    int numberNetworks = WiFi.scanNetworks();

    Serial.print("Redes encontradas");
    Serial.print(numberNetworks);

    for (int i = 0; i < numberNetworks; i++)
    {
        Serial.print("Nombre:");
        Serial.print(WiFi.SSID(i));

        Serial.print("Intensidad:");
        Serial.print(WiFi.RSSI(i));

        Serial.print("MAC:");
        Serial.print(WiFi.BSSIDstr(i));

        Serial.print("Encriptación:");
        Serial.print(WiFi.encryptionType(i));

        Serial.print("======================");
    }
}

void connectToNetwork()
{
    WiFi.begin(ssid,password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Estableciendo conexión...");
    }
    Serial.println("Conectado :D");
}

void setup()
{
    Serial.begin(115200);
    scanNetworks(); 
    connectToNetwork();

    Serial.println(WiFi.macAddress());
    Serial.println(WiFi.localIP());
}

void loop()
{

}
