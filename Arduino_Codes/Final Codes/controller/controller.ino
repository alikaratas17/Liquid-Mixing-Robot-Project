
/*
// PIN Setup if huzzah is used

*/
#define HUZZAH_OUT1 13
#define HUZZAH_OUT2 12
#define HUZZAH_OUT3 14
#define HUZZAH_OUT4 16
#define HUZZAH_REVERSE_WAY 15

/*
Waiting for message from server
For i = 1,2,3,4
  Send pump index to the mega
  Wait for confirmation
  Turn on that pump for that a given amount of time
Go back to waiting for message
*/



#define WAITING_FOR_INITIAL_MESSAGE_STATE 0
#define WAITING_FOR_MOVEMENT_STATE 1
#define DISPENSING_STATE 2


#define AMOUNT_CONST 1.0

#include "config.h"
#include <ESP8266WiFi.h>

AdafruitIO_Feed *message = io.feed("message");

int state; 

double amounts[4];
int current_liquid;
void setup(){
  setup_pins();
  state = WAITING_FOR_INITIAL_MESSAGE_STATE;
  Serial.begin(115200);
  while(!Serial);
  Serial.println("----");
  Serial.println("Connecting to Adafruit IO");
  io.connect();
  while(io.status()< AIO_CONNECTED){
    Serial.println(io.statusText());
    delay(500);
  }

  message->onMessage(handleMessage);
  amounts[0]=0.0;
  amounts[1]=0.0;
  amounts[2]=0.0;
  amounts[3]=0.0;
  current_liquid = 0;
  
}
void loop(){
  if(state==WAITING_FOR_INITIAL_MESSAGE_STATE){
    Serial.println(">> Waiting for Initial Message State");
    while(io.status()< AIO_CONNECTED){
      Serial.println("Connection Error");
      delay(500);
    }
    io.run();
    delay(20);

  }else if(state == WAITING_FOR_MOVEMENT_STATE){
    Serial.println(">> Movement State");
    send_movement();
  }else if(state == DISPENSING_STATE){
    Serial.println(">> Dispensing State");
    dispense();
    current_liquid ++;
    state = WAITING_FOR_MOVEMENT_STATE;
    if (current_liquid > 4){
      state = WAITING_FOR_INITIAL_MESSAGE_STATE;
      amounts[0]=0.0;
      amounts[1]=0.0;
      amounts[2]=0.0;
      amounts[3]=0.0;
      current_liquid = 0;
    }
  }
}
// Set pins to be output or input
void setup_pins(){
  pinMode(HUZZAH_REVERSE_WAY,INPUT);
  pinMode(HUZZAH_OUT1,OUTPUT);
  pinMode(HUZZAH_OUT2,OUTPUT);
  pinMode(HUZZAH_OUT3,OUTPUT);
  pinMode(HUZZAH_OUT4,OUTPUT);
}

void handleMessage(AdafruitIO_Data *data){
  if (state != WAITING_FOR_INITIAL_MESSAGE_STATE){
    Serial.println("Not Waiting for message");
    return;
  }
  Serial.println(data->toString());
  String result = data->toString();
  int inputs [4];
  int i = 0;
  int current = 0;
  int prev = 0;
  while(i !=3){
    if (result[current]==','){
      String substr = result.substring(prev,current);

    inputs[i] = substr.toInt();
    prev = current+1;
    i++;
    }
      current ++;
  }
  String substr = result.substring(current,result.length());
  inputs[3] = substr.toInt();
  Serial.println("Received Amounts:");
  Serial.print(inputs[0]);
  Serial.println(", ");
  Serial.print(inputs[1]);
  Serial.println(", ");
  Serial.print(inputs[2]);
  Serial.println(", ");
  Serial.println(inputs[3]);
  amounts[0] = inputs[0]*AMOUNT_CONST;
  amounts[1] = inputs[1]*AMOUNT_CONST;
  amounts[2] = inputs[2]*AMOUNT_CONST;
  amounts[3] = inputs[3]*AMOUNT_CONST;
  delay(500);
  current_liquid = 1;
  state = WAITING_FOR_MOVEMENT_STATE;
}

void dispense(){
  int delay_amount = round(amounts[current_liquid-1]*1000);
  if(delay_amount==0){
    return;
  }
  if(current_liquid==1){
    turn_on1();
  }else if(current_liquid==2){
    turn_on2();
  }else if(current_liquid==3){
    turn_on3();
  }else if(current_liquid==4){
    turn_on4();
  }
  delay(delay_amount);
  if(current_liquid==1){
    turn_off1();
  }else if(current_liquid==2){
    turn_off2();
  }else if(current_liquid==3){
    turn_off3();
  }else if(current_liquid==4){
    turn_off4();
  }
}
void turn_on1(){
digitalWrite(HUZZAH_OUT1,HIGH);}
void turn_on2(){
digitalWrite(HUZZAH_OUT2,HIGH);}
void turn_on3(){
digitalWrite(HUZZAH_OUT3,HIGH);}
void turn_on4(){
digitalWrite(HUZZAH_OUT4,HIGH);}
void turn_off1(){
digitalWrite(HUZZAH_OUT1,LOW);}
void turn_off2(){
digitalWrite(HUZZAH_OUT2,LOW);}
void turn_off3(){
digitalWrite(HUZZAH_OUT3,LOW);}
void turn_off4(){
digitalWrite(HUZZAH_OUT4,LOW);}

void send_movement(){
  while(digitalRead(HUZZAH_REVERSE_WAY) == HIGH){
    delay(100);
    Serial.print("Waiting for Huzzah REVERSE to be LOW ");
    Serial.println(current_liquid);
  }
  if (current_liquid==1){
    turn_on1();
  }else if (current_liquid==2){
    turn_on2();
  }else if (current_liquid==3){
    turn_on3();
  }else if (current_liquid==4){
    turn_on4();
  }
  while(digitalRead(HUZZAH_REVERSE_WAY) == LOW){
    delay(100);
    Serial.print("Waiting for movement to liquid ");
    Serial.println(current_liquid);
  }
  if (current_liquid==1){
    turn_off1();
  }else if (current_liquid==2){
    turn_off2();
  }else if (current_liquid==3){
    turn_off3();
  }else if (current_liquid==4){
    turn_off4();
  }
  state = DISPENSING_STATE;


}