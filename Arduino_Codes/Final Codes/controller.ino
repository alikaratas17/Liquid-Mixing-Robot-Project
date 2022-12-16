
/*
// PIN Setup if huzzah is used

*/
int state; 
#define WAITING_FOR_MESSAGE_STATE 0
#define WAITING_FOR_MOVEMENT_STATE 1
#define DISPENSING_STATE 2

#include "config.h"
#include <ESP8266WiFi.h>

AdafruitIO_Feed *message = io.feed("message");



void setup(){
  setup_pins();
  state = WAITING_FOR_MESSAGE_STATE;
  Serial.begin(115200);
  while(!Serial);
  Serial.println("----");
  Serial.println("Connecting to Adafruit IO");
  io.connect();
  message->onMessage(handleMessage);
  
}
void loop(){
  
  io.run();
  delay(20);
}
// Set pins to be output or input
void setup_pins(){


}

void handleMessage(AdafruitIO_Data *data){
  Serial.println(data->toString());
  String result = data->toString();
  int inputs [4];
  int i = 0;
  int current = 0;
  int prev = 0;
  while(i !=3){
    if (result[current]==','){
      String substr = result.substring(prev,current);
      //Serial.println(substr);
      //Serial.println(prev);
      //Serial.println(current);
    inputs[i] = substr.toInt();
    prev = current+1;
    i++;
    }
      current ++;
  }
  String substr = result.substring(current,result.length());
  inputs[3] = substr.toInt();
  Serial.println("__________");
  Serial.println(inputs[0]);
  Serial.println(inputs[1]);
  Serial.println(inputs[2]);
  Serial.println(inputs[3]);
  delay(500);
}