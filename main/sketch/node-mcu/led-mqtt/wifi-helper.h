#ifndef WIFI_HELPER_H
#define WIFI_HELPER_H

#include <ESP8266WiFi.h>

static const char *SSID = "REPUBLICA ALPHA";
static const char *PASSWORD = "chucknorris";

void initWifi();
void checkWifi();

#endif
