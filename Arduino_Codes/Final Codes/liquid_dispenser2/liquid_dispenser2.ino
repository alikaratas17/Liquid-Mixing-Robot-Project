/* Description
This code is for the arduino mega that will receive signal from huzzah
and pour specific liquids using pumps
*/



// PIN Setup for arduino mega
#define ENABLE_1 2 // ENA 1 PWM
#define IN1_1 3 //IN1 1
#define IN1_2 4//IN2 1
#define IN2_1 5 //IN3 1
#define IN2_2 6 //IN4 1
#define ENABLE_2 7 // ENB 1 PWM

#define ENABLE_3 8 // ENA 2 PWM
#define IN3_1 9 //IN1 2
#define IN3_2 10 //IN2 2
#define IN4_1 11 //IN3 2
#define IN4_2 12 //IN4 2
#define ENABLE_4 13 // ENB 2 PWM


// Can be reduced to 3 if needed
#define HUZZAH_IN1 A0
#define HUZZAH_IN2 A1
#define HUZZAH_IN3 A2
#define HUZZAH_IN4 A3

#define HUZZAH_OUT A4

#define BL_RX 50
#define BL_TX 51




#define ENABLE_AMOUNT 255 // 0 <= x <= 255

#define ANALOG_READ_TRESHOLD 511

// States
#define GET_NEXT_LIQUID_ADDRESS 0
#define WAIT_FOR_GO 1
#define POUR 2


#include <SoftwareSerial.h>
SoftwareSerial Bluetooth (BL_RX,BL_TX);

int state;

int current_liquid;
int sent_signal;


void setup(){
  setup_pins();
  turn_off1();
  turn_off2();
  turn_off3();
  turn_off4();
  digitalWrite(HUZZAH_OUT,LOW);
  Serial.begin(9600); 
  Serial.println("Starting!!");
  Bluetooth.begin(38400);
  //Bluetooth.println("TESTING");
  state = GET_NEXT_LIQUID_ADDRESS;
  current_liquid = 0;
  sent_signal = 0;
  delay(250);
}

void loop(){
  if (state == GET_NEXT_LIQUID_ADDRESS){
  Serial.println("Waiting For input");
    wait_for_input();
    if (current_liquid !=0){
      state = WAIT_FOR_GO;
      Serial.print("Time to go with liquid ");
      Serial.println(current_liquid);
    }
  }else if (state == WAIT_FOR_GO){
    Serial.print("Waiting to go");
    Serial.println(current_liquid);
    wait_to_go();

  }else if (state == POUR){
    Serial.print("POURING DRINK");
    Serial.println(current_liquid);
    pour_drink();
  }

}
void pour_drink(){
  digitalWrite(HUZZAH_OUT,LOW);
  if(current_liquid==1){
    pour_drink1();
  }else if(current_liquid==2){
    pour_drink2();
  }else if(current_liquid==3){
    pour_drink3();
  }else if(current_liquid==4){
    pour_drink4();
  } 
}
void pour_drink1(){
  while(analogRead(HUZZAH_IN1)< ANALOG_READ_TRESHOLD);//wait to start
  //digitalWrite(HUZZAH_OUT,LOW);
  turn_on1();
  while(analogRead(HUZZAH_IN1)> ANALOG_READ_TRESHOLD);//wait to end
  turn_off1();
  current_liquid = 0;
  state = GET_NEXT_LIQUID_ADDRESS;
}
void pour_drink2(){
  while(analogRead(HUZZAH_IN2)< ANALOG_READ_TRESHOLD);//wait to start
  //digitalWrite(HUZZAH_OUT,LOW);
  turn_on2();
  while(analogRead(HUZZAH_IN2)> ANALOG_READ_TRESHOLD);//wait to end
  turn_off2();
  current_liquid = 0;
  state = GET_NEXT_LIQUID_ADDRESS;
}
void pour_drink3(){
  while(analogRead(HUZZAH_IN3)< ANALOG_READ_TRESHOLD);//wait to start
  //digitalWrite(HUZZAH_OUT,LOW);
  turn_on3();
  while(analogRead(HUZZAH_IN3)> ANALOG_READ_TRESHOLD);//wait to end
  turn_off3();
  current_liquid = 0;
  state = GET_NEXT_LIQUID_ADDRESS;
}
void pour_drink4(){
  while(analogRead(HUZZAH_IN4)< ANALOG_READ_TRESHOLD);//wait to start
  //digitalWrite(HUZZAH_OUT,LOW);
  turn_on4();
  while(analogRead(HUZZAH_IN4)> ANALOG_READ_TRESHOLD);//wait to end
  turn_off4();
  current_liquid = 0;
  state = GET_NEXT_LIQUID_ADDRESS;
}
void wait_to_go(){
  //if (sent_signal==0){
  //  Bluetooth.write(current_liquid);
    sent_signal = 1;
  //}
  while(sent_signal == 1){
    Bluetooth.write(current_liquid);
    Serial.println("SENT MESSAGE");
    Serial.println(current_liquid);
    delay(500);
  while(Bluetooth.available()){
    int message = Bluetooth.read();
    Serial.println("GOT MESSAGE");
    Serial.println(message);
   if (message == current_liquid){
     sent_signal = 0;
   }
  }
  }
  state = POUR;
}

void wait_for_input(){
  if(analogRead(HUZZAH_IN1)>= ANALOG_READ_TRESHOLD){
    current_liquid = 1;

  }else if(analogRead(HUZZAH_IN2)>= ANALOG_READ_TRESHOLD){
    current_liquid = 2;

  }else if(analogRead(HUZZAH_IN3)>= ANALOG_READ_TRESHOLD){
    current_liquid = 3;

  }else if(analogRead(HUZZAH_IN4)>= ANALOG_READ_TRESHOLD){
    current_liquid = 4;
  }else{
    return;
  }
  digitalWrite(HUZZAH_OUT,HIGH);
  

}

// Set pins to be output or input
void setup_pins(){
  pinMode(ENABLE_1, OUTPUT);
  pinMode(ENABLE_2, OUTPUT);
  pinMode(ENABLE_3, OUTPUT);
  pinMode(ENABLE_4, OUTPUT);
  pinMode(IN1_1, OUTPUT);
  pinMode(IN1_2, OUTPUT);
  pinMode(IN2_1, OUTPUT);
  pinMode(IN2_2, OUTPUT);
  pinMode(IN3_1, OUTPUT);
  pinMode(IN3_2, OUTPUT);
  pinMode(IN4_1, OUTPUT);
  pinMode(IN4_2, OUTPUT);
  pinMode(HUZZAH_IN1, INPUT);
  pinMode(HUZZAH_IN2, INPUT);
  pinMode(HUZZAH_IN3, INPUT);
  pinMode(HUZZAH_IN4, INPUT);

  pinMode(HUZZAH_OUT, OUTPUT);

}

void turn_on1(){
  analogWrite(ENABLE_1,ENABLE_AMOUNT);
    digitalWrite(IN1_1, HIGH);
    digitalWrite(IN1_2, LOW);
}

void turn_on2(){
  analogWrite(ENABLE_2,ENABLE_AMOUNT);
    digitalWrite(IN2_1, HIGH);
    digitalWrite(IN2_2, LOW);}
void turn_on3(){
  analogWrite(ENABLE_3,ENABLE_AMOUNT);
    digitalWrite(IN3_1, HIGH);
    digitalWrite(IN3_2, LOW);}
void turn_on4(){
  analogWrite(ENABLE_4,ENABLE_AMOUNT);
    digitalWrite(IN4_1, HIGH);
    digitalWrite(IN4_2, LOW);}
void turn_off1(){
  analogWrite(ENABLE_1,0);
    digitalWrite(IN1_1, LOW);
    digitalWrite(IN1_2, LOW);}
void turn_off2(){
  analogWrite(ENABLE_2,0);
    digitalWrite(IN2_1, LOW);
    digitalWrite(IN2_2, LOW);}
void turn_off3(){
  analogWrite(ENABLE_3,0);
    digitalWrite(IN3_1, LOW);
    digitalWrite(IN3_2, LOW);}
void turn_off4(){
  analogWrite(ENABLE_4,0);
    digitalWrite(IN4_1, LOW);
    digitalWrite(IN4_2, LOW);}
