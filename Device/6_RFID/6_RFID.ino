#include <WiFi.h>
#include <SPI.h>
#include <MFRC522.h>

const char* ssid = "Emprendedores";
const char* password = "AxtVvm13";
const int RST_PIN = 22;
const int SS_PIN = 21;

MFRC522 mfrc522(SS_PIN , RST_PIN);

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
    SPI.begin();
    mfrc522.PCD_Init();
    delay(6);
    mfrc522.PCD_DumpVersionToSerial();
    connectToNetwork();

    Serial.println(WiFi.macAddress());
    Serial.println(WiFi.localIP());
}

void loop()
{
    if (! mfrc522.PICC_IsNewCardPresent())
    {
        return;
    }
    if (! mfrc522.PICC_ReadCardSerial())
    {
        return;
    }

    mfrc522.PICC_DumpToSerial(&(mfrc522.uid));   
    
}
