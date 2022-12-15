
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
  Serial.begin(9600); 
  Serial.println("Starting!!");
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
  delay(500);

}