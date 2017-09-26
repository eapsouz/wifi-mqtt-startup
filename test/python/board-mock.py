#!/usr/bin/env python3
# See http://www.eclipse.org/paho/ for more info
import paho.mqtt.client as mqtt
import time  # is money!!!


MQTT_HOST = "localhost"     # Change for your setup
MQTT_PORT = 1883            # Change for your setup
MQTT_TOPIC_FUTURE = "led/future"         # Change for your setup
MQTT_TOPIC_CURRENT = "led/current"       # Change for your setup
MQTT_CLIENT = 61

# When connect to the server:
# go and subscribe!!!
def on_connect(client, mosq, userdata, rc):
    print("Connected with result code "+str(rc))
    client.subscribe(MQTT_TOPIC_FUTURE) #
    
# When a new message from the subscribed topic arrive:
def on_message(client, userdata, msg):
    # print(msg.topic+": "+str(msg.payload))
    # I am Tottally a nodeMCU board who feeds with the led/future
    # soon as I read a new goal, I change my leds as asked
    print("My leds will be like: "+msg.topic+": "+str(msg.payload))
    client.publish(MQTT_TOPIC_CURRENT, payload=msg.payload,
                    qos=0, retain=False)
    print("look at "+MQTT_TOPIC_CURRENT+": "+str(msg.payload))

client = mqtt.Client(client_id="board-mock")  # Create a client instance

# Callback declarations
client.on_connect = on_connect
client.on_message = on_message

client.connect(MQTT_HOST, MQTT_PORT, MQTT_CLIENT)

# Blocking call that processes network traffic, dispatches callbacks and
# handles reconnecting.
# Other loop*() functions are available that give a threaded interface and a
# manual interface.
client.loop_start()
while True:
    time.sleep(2)