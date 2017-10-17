#include "mqtt-helper.h"

String _ledState = "000";

static const uint8_t redPin = D3;
static const uint8_t bluePin = D2;
static const uint8_t greenPin = D1;

void initLEDs()
{
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
}

void changeState(String message)
{
  _ledState = message;
  digitalWrite(greenPin, _ledState[0] == '1');
  digitalWrite(bluePin, _ledState[1] == '1');
  digitalWrite(redPin, _ledState[2] == '1');
  publishState();
}
// ### LEDs ###

void initSerial();

// -- Initialize --

// -- publish mqtt messages
void publishState()
{
  char msg[4];
  Serial.print("State reached: ");
  Serial.println(_ledState);
  msg[0] = _ledState[0];
  msg[1] = _ledState[1];
  msg[2] = _ledState[2];
  msg[3] = '\0';
  publish(msg);
}
// ### MQTT ###

// ### Serial Monitor ###
void initSerial()
{
  Serial.begin(115200);
}
// ### Serial Monitor ###

// ## PROGRAM ###
void setup()
{
  initSerial();
  initLEDs();
  initWifi();
  initMqtt(&changeState);
}

void loop()
{
  checkWifi();
  checkMqtt();
}
// ## PROGRAM ###
