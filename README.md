# Wifi Mqtt Startup

>Getting start with mqtt, wifi and nodeMCU
This is a basic project for understand how mqtt works.

The board's objective is to write in to  a topic named **led/future** and write in to another topic, named **led/current**


## Mqtt ##

Go for the Docs:
[Wiki](https://github.com/mqtt/mqtt.github.io/wiki)

Make sure you undestand the base of mqtt, and then:
Install **mqtt** mosquitto 
[Mosquitto WebSite](mosquitto.org)

I also recommed check mosquito client bash
Make sure you have the broker up and running.

You are using deb based **linux** (like me), so:
```bash
sudo apt-get install mosquitto mosquitto-clients
```
To use mosquitto-clients, just subscript in a topic:
```bash
mosquitto_sub -h localhost -t test
```
Open a new terminal and:
```bash
mosquitto_pub -h localhost -t test -m "hello world" -t test
```

>Our application will work just like this...


## Python ##
>I'm using python client scripts to publish and monitor the mqtt topics:

Setup your Python environment. **I used Python3**

install [paho-mqtt](https://eclipse.org/paho/clients/python/)
```bash
pip install paho-mqtt
```
or
```bash
pip3 install paho-mqtt
```

### publisher.py
cd into python-for-mock and:
```bash
python3 publisher.py
```
This script will post on **led/future** topic counting to 6 in binary, so the board subscriber can read the messages and answer properly.

### subscriber.py
```bash
python3 subscriber.py
```
This script subscribe and read **led/future** and **led/current** topics and print their results.
At this point, you'll be able to see just the post of **led/future** topic

### board-mock.py
```bash
python3 board-mock.py
```
This script mocks the board, simulating it's behavior, read **led/future** topic and write back to the **led/current** topic.
Now, back to the subscriber terminal you will se the two topics in action.


## Board ##

### Materials ###

*3 - LEDs
*3 - 220Ohms resistors
*1 - NodeMcu board
*1 - breadboard
*  - Jumpers

### Schematic ###

- D1 -> greenLed -> 220 resistor -> gnd
- D2 -> blueLed  -> 220 resistor -> gnd
- D3 -> redLed   -> 220 resistor -> gnd

### Arduino IDE ###
[Quick Start to Nodemcu (ESP8266) on Arduino IDE](http://www.instructables.com/id/Quick-Start-to-Nodemcu-ESP8266-on-Arduino-IDE/)

### Libraries ###
Make sure you had downloaded (use **arduino IDE** ;) the two libraries necessary for this example:
[ESP8266WiFi]()
[PubSubClient](https://pubsubclient.knolleary.net/)


With all set, just have fun.

