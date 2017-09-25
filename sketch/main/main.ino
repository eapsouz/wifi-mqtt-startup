#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define ID_MQTT "NODE_MCU_DEVICE"

// YOUR setup
// =================================
//wifi
static const char* SSID = "";
static const char* PASSWORD = "";

//topics
#define SUBSCRIBE "led/future"
#define PUBLISH "led/current"

//BROKER
static const char* BROKER_HOST = "192.168.1.39"; // DNS/IP
static const int BROKER_PORT = 1883;

//LEDs
static const uint8_t redPin = D3;
static const uint8_t bluePin = D2;
static const uint8_t greenPin = D1;

String _ledState = "000";
//================================

void initLEDs(){
  pinMode(redPin,OUTPUT);
  pinMode(bluePin,OUTPUT);
  pinMode(greenPin,OUTPUT);
}

void changeState(){
  digitalWrite(greenPin, _ledState[0]=='1'); 
  digitalWrite(bluePin, _ledState[1]=='1');
  digitalWrite(redPin, _ledState[2]=='1');
  publishState();
}
// ### LEDs ###

WiFiClient espClient;
PubSubClient MQTT(espClient);

void initSerial();
void initWifi();
void initMqtt();
void checkWifi();
void checkMqtt();
void mqttHandle(char* topic, byte* payload, unsigned int length);

// ### WiFi ###
void initWifi(){
  delay(10);
  Serial.println("------ Wi-fi Conection------");
  Serial.print("Conecting: ");
  Serial.println(SSID);
  Serial.println("Hold on");
  checkWifi();
  Serial.println("------ Wi-fi Conection------");
}

void checkWifi(){
  if(WiFi.status() == WL_CONNECTED)
    return;

  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED){
    delay(100);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Wifi Connected!");
  Serial.println(SSID);
  Serial.println("Under IP: ");
  Serial.println(WiFi.localIP());
}
// ### WiFi ###

// ### MQTT ###
// -- Initialize --
void initMqtt() 
{
    Serial.println("------ MQTT BROKER Conection------");
    MQTT.setServer(BROKER_HOST, BROKER_PORT);   //informa qual broker e porta deve ser conectado
    MQTT.setCallback(mqttHandle);            //atribui função de callback (função chamada quando qualquer informação de um dos tópicos subescritos chega)
    checkMqtt();
    Serial.println("------ MQTT BROKER Conection------");
}
// -- check and keep connection alive --
void checkMqtt() 
{
    while (!MQTT.connected()) 
    {
        Serial.print("Connecting to Broker MQTT: ");
        Serial.println(BROKER_HOST);
        if (MQTT.connect(ID_MQTT)) 
        {
            Serial.println("Sucess!");
            MQTT.subscribe(SUBSCRIBE); 
        } 
        else 
        {
            Serial.println("Failed!");
            Serial.println("New try in 5 secs!");
            delay(5000);
        }
    }
}
// -- callback for handle mqtt messages --
void mqttHandle(char* topic, byte* payload, unsigned int length) 
{
  Serial.println("------ Message Received ------");
  _ledState="";
  //obtem a string do payload recebido
  for(int i = 0; i < length; i++) 
  {
     char c = (char)payload[i];
     _ledState+= c;
  }
  Serial.print("Content: ");
  Serial.println(_ledState);
  changeState();
  Serial.println("------ DONE ------");
}
// -- publish mqtt messages
void publishState()
{
  char msg[4];
  Serial.print("State reached: ");
  Serial.println(_ledState);
  msg[0]=_ledState[0];
  msg[1]=_ledState[1];
  msg[2]=_ledState[2];
  msg[3]='\0';
  MQTT.publish(PUBLISH, msg);
}
// ### MQTT ###

// ### Serial Monitor ###
void initSerial(){
  Serial.begin(115200);
}
// ### Serial Monitor ###

// ## PROGRAM ###
void setup() {
  initLEDs();
  initSerial();
  initWifi();
  initMqtt();
}

void loop() {
  MQTT.loop();
}
// ## PROGRAM ###
