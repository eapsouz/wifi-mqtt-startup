#!/usr/bin/env python3
# See http://www.eclipse.org/paho/ for more info
import paho.mqtt.client as mqtt
import time  # is money!!!

MQTT_HOST = "localhost"     # Change for your setup
MQTT_PORT = 1883            # Change for your setup
MQTT_TOPIC = "led/future"       # Change for your setup
MQTT_CLIENT = 60

# When connect to the server:
# go and subscribe!!!
def on_connect(client, mosq, userdata, rc):
    print("Connected with result code "+str(rc))
    client.subscribe(MQTT_TOPIC) #

# When a new message from the subscribed topic arrive:
def on_message(client, userdata, msg):
    print(msg.topic+": "+str(msg.payload))

client = mqtt.Client(client_id="publisher")  # Create a client instance

# Callback declarations
client.on_connect = on_connect
client.on_message = on_message

client.connect(MQTT_HOST, MQTT_PORT, MQTT_CLIENT)

# Blocking call that processes network traffic, dispatches callbacks and
# handles reconnecting.
# Other loop*() functions are available that give a threaded interface and a
# manual interface.
client.loop_start()
index = 0
while True:
    # I am flooding the topic with messages
    # I will count from 0 to 7 in binary
    if (index == 7): 
        # soon as I reach 8 i start again
        index = 0
    else:
        index = index + 1
    # little rest
    time.sleep(2)
    # here we go!
    client.publish(MQTT_TOPIC, payload=str('{0:03b}'.format(index)),
                   qos=0, retain=False)