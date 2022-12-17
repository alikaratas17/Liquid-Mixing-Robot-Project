
/*
// PIN Setup if uno is used
TODO
*/

// PIN Setup if micro is used
#define ENABLE_MOTOR_A_PIN 9
#define IN1_PIN 8
#define IN2_PIN 7
#define ENABLE_MOTOR_B_PIN 4
#define IN3_PIN 5
#define IN4_PIN 6
#define ECHO_PIN_FORWARD 11
#define TRIG_PIN_FORWARD 12
#define ECHO_PIN_BACKWARD 13 //?
#define TRIG_PIN_BACKWARD 14 //?

#include <SoftwareSerial.h>
SoftwareSerial Bluetooth (3,2);
//#define PINS OF BLUETOOTH

#define EN_A_SPEED_CONTROL 127 // 0<= <=255
#define EN_B_SPEED_CONTROL 127 // 0<= <=255

// go Delay(50) stop Delay(500)

int state; 
#define WAITING_STATE 0
#define MOVING_STATE 1
#define SENDING_INFO_STATE 2

#define car_length 10.0

void setup(){
  setup_pins();
  stop_motors();
  Serial.begin(9600); 
  Serial.println("Starting!!");
  state = WAITING_STATE;
  Bluetooth.begin(38400);
}
void loop(){
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
  pinMode(TRIG_PIN, OUTPUT); 
  pinMode(ECHO_PIN, INPUT); 

}
// Turns motors in forward direction
void go_forward(){
    analogWrite(ENABLE_MOTOR_A_PIN,EN_A_SPEED_CONTROL);
    analogWrite(ENABLE_MOTOR_B_PIN,EN_B_SPEED_CONTROL);
    digitalWrite(IN1_PIN, HIGH);
    digitalWrite(IN2_PIN, LOW);
    digitalWrite(IN3_PIN, HIGH);
    digitalWrite(IN4_PIN, LOW);
}
// Turns motors in negative direction
void go_backward(){
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