#include <SoftwareSerial.h>
#include <stdlib.h>
#include <TinyGPS++.h>

static const int RXPin = 4, TXPin = 3;
// The serial connection to the ESP8266-01
SoftwareSerial ESP8266(2, 3); // Rx,  Tx

// The serial connection to the GPS module
SoftwareSerial ss(RXPin, TXPin);

unsigned char check_connection=0;
unsigned char times_check=0;
String myAPIkey = "PZ3CP1S17OAOQQGK";  
float latitude, longitude;
static const int deviceId = 1;

void setup() {
  Serial.begin(115200);
  ESP8266.begin(115200);  
  ESP8266.print("***VER:");
  delay(2000);
  ESP8266.println("AT+RST");
  delay(1000);
  ESP8266.println("AT+GMR");
  delay(1000);
  ESP8266.println("AT+CWMODE=3");
  delay(1000);
  ESP8266.println("AT+CWLAP");
  delay(1000);
}


void loop() {
  Serial.println("Connecting to Wifi");
  while(check_connection==0) {
    Serial.print(".");
    ESP8266.print("AT+CWJAP=\"JOAO_2G\",\"joaocarlos20\"\r\n");
    ESP8266.setTimeout(5000);

    if(ESP8266.find("WIFI CONNECTED\r\n")==1) {
      Serial.println("WIFI CONNECTED");
      break;
    }
    times_check++;
    if(times_check>3) {
      times_check=0;
      Serial.println("Trying to Reconnect..");
    }
  } 
  while(1) {
    readSensors();
    writeThingSpeak();
    delay(10000);
  };
}

void readSensors(void) {
  gps.encode(ss.read());
  if (gps.location.isUpdated()){
    latitude = gps.location.lat();
    longitude = gps.location.lng();
  }
}

void writeThingSpeak(void) {
  startThingSpeakCmd();
  // preparacao da string GET
  String getStr = "GET /update?api_key=";
  getStr += myAPIkey;
  getStr +="&field1=";
  getStr += String(latitude);
  getStr +="&field2=";
  getStr += String(longitude);
  getStr +="&field3=";
  getStr += String(deviceId);
  getStr += "\r\n\r\n";
  GetThingspeakcmd(getStr); 
}

void startThingSpeakCmd(void) {
  ESP8266.flush();
  //IPAddress ip = WiFi.hostByName("ship-track.fly.io");
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += "184.106.153.149"; // api.thingspeak.com IP address
  cmd += "\",80";
  ESP8266.println(cmd);
  Serial.print("Start Commands: ");
  Serial.println(cmd);

  if(ESP8266.find("Error")) {
    Serial.println("AT+CIPSTART error");
    return;
  }
} 

String GetThingspeakcmd(String postStr) {
  String cmd = "AT+CIPSEND=";
  cmd += String(postStr.length());
  ESP8266.println(cmd);
  Serial.println(cmd);
  ESP8266.readStringUntil('\n');

  if(ESP8266.find(">")) {
    ESP8266.print(postStr);
    Serial.println(postStr);
    delay(500);
    String messageBody = "";
    while (ESP8266.available()) {
      String line = ESP8266.readStringUntil('\n');
      if (line.length() == 1) { 
        messageBody = ESP8266.readStringUntil('\n');
      }
    }
    Serial.print("MessageBody received: ");
    Serial.println(messageBody);
    return messageBody;
  }
  else {
    ESP8266.println("AT+CIPCLOSE");     
    Serial.println("AT+CIPCLOSE"); 
  } 
}
