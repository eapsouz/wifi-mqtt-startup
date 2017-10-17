#include "wifi-helper.h"

void initWifi()
{
    delay(10);
    Serial.println("------ Wi-fi Conection------");
    Serial.print("Conecting: ");
    Serial.println(SSID);
    Serial.println("Hold on");
    Serial.println("------ Wi-fi Conection------");
}

void checkWifi()
{
    if (WiFi.status() == WL_CONNECTED)
        return;

    WiFi.begin(SSID, PASSWORD);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(100);
    }

    Serial.println();
    Serial.println("Wifi Connected!");
    Serial.println(SSID);
    Serial.print("Under IP: ");
    Serial.println(WiFi.localIP());
}
