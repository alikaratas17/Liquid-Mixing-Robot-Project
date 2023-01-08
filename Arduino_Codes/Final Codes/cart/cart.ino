
/*
// PIN Setup if uno is used
TODO
*/

// PIN Setup if micro is used
#define ENABLE_MOTOR_A_PIN 9
#define IN1_PIN 8
#define IN2_PIN 7
#define IN3_PIN 4
#define IN4_PIN 6
#define ENABLE_MOTOR_B_PIN 5
#define ECHO_PIN_FORWARD 11
#define TRIG_PIN_FORWARD 12
#define ECHO_PIN_BACKWARD A0 //?
#define TRIG_PIN_BACKWARD A1 //?

#include <SoftwareSerial.h>
SoftwareSerial Bluetooth (MISO,A3);
//#define PINS OF BLUETOOTH

#define EN_A_SPEED_CONTROL 127 // 0<= <=255
#define EN_B_SPEED_CONTROL 127 // 0<= <=255

// go Delay(50) stop Delay(500)

int state; 
#define WAITING_STATE 0
#define MOVING_STATE 1
#define SENDING_INFO_STATE 2

#define car_length 10.0
int current_pmp;
int pumps_to_go [4]={3,1,4,2};

void setup(){
  setup_pins();
  stop_motors();
  Serial.begin(9600); 
  Serial.println("Starting!!");
  state = WAITING_STATE;
  Bluetooth.begin(38400);
}
void loop(){
    if(Bluetooth.available()){
      int c1 = Bluetooth.read();
      if(c1>=0 && c1 < 5)
        Serial.write(c1+48);
  }
  if(Serial.available()){
    int c = Serial.read();
    if(c>=48 && c < 48+5) 
      Bluetooth.write(c-48);
  }
  return;
  int status =  go_to_pump(pumps_to_go[current_pmp]);
  if(status==0)current_pmp++;
  Serial.print("Current Pump: ");
  Serial.print(pumps_to_go[current_pmp]);
  Serial.print(" Status: ");
  Serial.println(status);
  if(current_pmp==4)current_pmp=0;
  return;
  if(state == WAITING_STATE){
    //BLUETOOTH COMM to get location

  }
  else if(state == MOVING_STATE){
  float forward_dist = get_distance(TRIG_PIN_FORWARD,ECHO_PIN_FORWARD);
  float backward_dist = get_distance(TRIG_PIN_BACKWARD,ECHO_PIN_BACKWARD);
  float total_length = forward_dist+backward_dist + car_length;
  float position =  backward_dist / total_length; // 0.0 1.0
  // TODO: Move to location
  if (position<0.5){
    go_forward();
  }else{
    stop_motors();
  }
  }
  else if(state==SENDING_INFO_STATE){
    //BLUETOOTH COMM to send location
  }
  // TODO: SHOULD THERE BE OTHER STATES
  
}
// Set pins to be output or input
void setup_pins(){
  pinMode(ENABLE_MOTOR_A_PIN, OUTPUT);
  pinMode(ENABLE_MOTOR_B_PIN, OUTPUT);
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);
  pinMode(IN3_PIN, OUTPUT);
  pinMode(IN4_PIN, OUTPUT);
  pinMode(TRIG_PIN_FORWARD, OUTPUT); 
  pinMode(ECHO_PIN_FORWARD, INPUT); 
  pinMode(TRIG_PIN_BACKWARD, OUTPUT); 
  pinMode(ECHO_PIN_BACKWARD, INPUT); 

}
// Turns motors in forward direction
void go_backward(){
    analogWrite(ENABLE_MOTOR_A_PIN,EN_A_SPEED_CONTROL);
    analogWrite(ENABLE_MOTOR_B_PIN,EN_B_SPEED_CONTROL);
    digitalWrite(IN1_PIN, HIGH);
    digitalWrite(IN2_PIN, LOW);
    digitalWrite(IN3_PIN, HIGH);
    digitalWrite(IN4_PIN, LOW);
}
// Turns motors in negative direction
void go_forward(){
    analogWrite(ENABLE_MOTOR_A_PIN,EN_A_SPEED_CONTROL);
    analogWrite(ENABLE_MOTOR_B_PIN,EN_B_SPEED_CONTROL);
    digitalWrite(IN1_PIN, LOW);
    digitalWrite(IN2_PIN, HIGH);
    digitalWrite(IN3_PIN, LOW);
    digitalWrite(IN4_PIN, HIGH);

}
// Stops motors
void stop_motors(){
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, LOW);
  digitalWrite(IN3_PIN, LOW);
  digitalWrite(IN4_PIN, LOW);

}
// Returns the distance in cm using the distance sensor
float get_distance(int trig_pin, int echo_pin){
  digitalWrite(trig_pin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trig_pin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);
  double duration = (double) pulseIn(echo_pin, HIGH);
  float distance = duration * 0.034 / 2;
  return distance;
}

/*
  if(Bluetooth.available()){
    Serial.write(Bluetooth.read());
  }
  if(Serial.available()){
    Bluetooth.write(Serial.read());
  }
*/

/*
Returns 0 if at that pump, 1 if after, -1 if before
*/
int go_to_pump(int pumpNum){
  float current_pos = get_current_pos();
  if ((float)pumpNum == current_pos){
    return 0;
  }
  if((float)pumpNum > current_pos){
    go_forward();
    delay(50);
    stop_motors();
    delay(500);
    return 1;
  }
  //Case 3
    go_backward();
    delay(50);
    stop_motors();
    delay(500);
    return -1;
}

/*
Returns 1.0,2.0,3.0,4.0 if at corresponding pumps, else returns between [1,4] depending on distances
*/
float get_current_pos(){
  float fdist = get_distance(TRIG_PIN_FORWARD,ECHO_PIN_FORWARD);
  float bdist = get_distance(TRIG_PIN_BACKWARD,ECHO_PIN_BACKWARD);
  Serial.print("Forward: ");
  Serial.print(fdist);
  Serial.print(", Backward: ");
  Serial.println(bdist);
  if(fdist > 50 || bdist > fdist){
    //bdist
    if(bdist > 17.5){
      return 4.0;
    }
    if(bdist > 13.5){
      return 3.5;
    }
    if(bdist > 11){
      return 3.0;
    }
    return 2.5;
  }else{
    //fdist
    if(fdist > 15.75){
      return 1.0;
    }
    if(fdist > 12.75){
      return 1.5;
    }
    if(fdist > 10.0){
      return 2.0;
    }
    return 2.5;
  }
  // FWD
  //17.25 - 15.75 -> 1
  // 12. 75 - 10.00 -> 2
  // BWD
  // 13.5 - 11 -> 3
  // 19 - 17.5
  //return 1.0; //TODO
}
