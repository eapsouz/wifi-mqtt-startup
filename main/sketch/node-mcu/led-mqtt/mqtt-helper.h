#ifndef MQTT_HELPER_H
#define MQTT_HELPER_H

#include <PubSubClient.h>
#include "device-config.h"
#include "wifi-helper.h"

static const char* BROKER_HOST = "192.168.1.39"; // DNS/IP
static const int BROKER_PORT = 1883;

static WiFiClient espClient;
static PubSubClient MQTT(espClient);

void initMqtt(void (*handler)(String));
void checkMqtt();
void publish(char* message);
static void (*messageHandle)(String) = NULL;

#endif
