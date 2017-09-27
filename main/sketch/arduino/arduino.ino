#include <ArduinoJson.h>
#include <LiquidCrystal.h>

String _jsonMsg="";
String _temperature="";
String _humidity="";
// ### LCD ###
static const uint8_t RS = 12;
static const uint8_t EN = 11;
static const uint8_t D4 = 5;
static const uint8_t D5 = 4;
static const uint8_t D6 = 3;
static const uint8_t D7 = 2;

LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

const uint8_t __degree__ = 0;
byte symbolDegree[8] ={  B00001100,
                          B00010010,
                          B00010010,
                          B00001100,
                          B00000000,
                          B00000000,
                          B00000000,
                          B00000000,};

void initLCD(){
  lcd.begin(16, 2);
  lcd.print("waiting...");
  lcd.createChar(0,symbolDegree);
  lcd.clear();
  delay(200);
  printTemplate();
}

void printTemplate(){
  lcd.setCursor(0,0);
  lcd.print("Temp:");
  lcd.setCursor(12,0);  
  lcd.write((byte)__degree__);
  
  lcd.setCursor(0,1);
  lcd.print("Umid:");
  lcd.setCursor(12,1);
  lcd.print("%");
}

void printData(){
  lcd.setCursor(6,0);
  lcd.print(_temperature);
  lcd.setCursor(6,1);
  lcd.print(_humidity);
}

// ### LCD ###
// ### Serial ###
void initSerial(){
  Serial.begin(115200);
}

bool serialMonitor(){
  String msg;
  if(Serial.available()>0){
    msg = Serial.readString();
    Serial.println(msg);
    _jsonMsg=msg;
    return true;
  }else{
    return false;
  }
}
// ### Serial ###
// ### Parse Info ###
StaticJsonBuffer<512> jsonBuffer;
bool bindInfo(){
  char* t="";
  char* h="";
  bool changed=false;
  JsonObject& jsonObject = jsonBuffer.parseObject(_jsonMsg);
  
  t = jsonObject["temperature"];
  h = jsonObject["humidity"];
  Serial.println(t);
  Serial.println(h);
  
  if(t!=""){
    changed=true;
    _temperature = t;
  }
  if(h!=""){
    changed=true;
    _humidity=h;
  }
  return changed;
}
// ### Parse Info ###
// ### PROGRAM ###
void setup()
{
  initLCD();
  initSerial();
}

void loop()
{
  if(serialMonitor()&&bindInfo()){
    printData();
  }
}
// ### PROGRAM ###
