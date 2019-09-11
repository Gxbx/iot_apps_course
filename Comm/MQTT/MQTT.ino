#include <WiFi.h>
#include <PubSubClient.h>   

const char* ssid = "Emprendedores";
const char* password = "AxtVvm13";
const char* mqtt_broker = "192.168.1.197";
const int pinCell = 36;

WiFiClient wifi;
PubSubClient client(wifi);
long lasMsg = 0;
char msg[25];

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

void callback(char* topic, byte* message, unsigned int length)
{
    Serial.println("Ohh! ha llegado un mensaje");
    Serial.print("Canal: ");
    Serial.println(topic);
    Serial.print("Mensaje: ");

    String incoming;
    for (int i = 0; i < length; i++)
    {
        Serial.print((char)message[i]);
        incoming += (char)message[i];

        //Parsing variable.toString() ó String(variable)
        //Casting (char)variable ó (float)variable
    }
    Serial.println();
    
    //AQUI AGREGAR LA LÓGICA
}
void reconnect()
{
    while (!client.connected())
    {
        if (client.connect("ESP32"))
        {
            Serial.println("Estoy conectado :D");
            client.subscribe("esp32/fotocell/output");
        }
        else
        {
            Serial.print("conexión fallida :'/");
            Serial.print(client.state());
            delay(3000);
        }   
    }  
}

void setup()
{
    Serial.begin(115200);
    connectToNetwork();
    client.setServer(mqtt_broker,1883);
    client.setCallback(callback);
}

void loop ()
{
    if (!client.connected())
    {
        reconnect();
    }
    client.loop();

    long now = millis();
    if (now - lasMsg >3000)
    {
        //Aqui el codigo de lectura de la fotocelda
        
        char value[8];
        dtostrf(analogRead(pinCell),1, 2, value);
        //dtostrf()
        client.publish("esp32/fotocell/output", value);
    }
    
    
}