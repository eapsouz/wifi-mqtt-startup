#include "mqtt-helper.h"

String mqttHandle(char *topic, byte *payload, unsigned int length)
{
    Serial.println("------ Message Received ------");
    String msg = "";
    //obtem a string do payload recebido
    for (int i = 0; i < length; i++)
    {
        char c = (char)payload[i];
        msg += c;
    }
    Serial.print("Content: ");
    Serial.println(msg);
    (*messageHandle)(msg);
    Serial.println("------ DONE ------");
    return msg;
}

void initMqtt(void (*handler)(String))
{
    Serial.println("------ MQTT BROKER Conection------");
    messageHandle = handler;                  //atribui funcao a ser implementada na aplicação
    Serial.println("Set server: ");
    Serial.print(BROKER_HOST);
    Serial.print(":");
    Serial.println(BROKER_PORT); 
    MQTT.setServer(BROKER_HOST, BROKER_PORT); //informa qual broker e porta deve ser conectado
    MQTT.setCallback(mqttHandle);             //atribui função de callback (função chamada quando qualquer informação de um dos tópicos subescritos chega)
    Serial.println("------ MQTT BROKER Conection------");
}
// -- check and keep connection alive --
void subscribe(char* topico,char* id)
{
    while (!MQTT.connected())
    {
        Serial.print("Connecting to Broker MQTT: ");
        Serial.println(BROKER_HOST);
        if (MQTT.connect(id))
        {
            Serial.println("Sucess!");
            Serial.print("Subscribing at: ");
            MQTT.subscribe(topico);
            Serial.println(topico);
        }
        else
        {
            Serial.println("Failed!");
            Serial.println("New try in 5 secs!");
            delay(5000);
        }
    }
    MQTT.loop();
}

void publish (char* topico,char* message){
    MQTT.publish(topico, message);
}
