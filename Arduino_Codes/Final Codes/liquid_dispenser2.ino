/* Description
This code is for the arduino uno that will receive signal from huzzah
and pour specific liquids using pumps
*/




// PIN Setup for arduino uno
#define ENABLE_1 3 // ENA 1 PWM
#define ENABLE_2 5 // ENB 1 PWM
#define ENABLE_3 11 // ENA 2 PWM
#define ENABLE_4 10 // ENB 2 PWM
#define IN1_1 2 //IN1 1
#define IN1_2 4//IN2 1
#define IN2_1 7 //IN3 1
#define IN2_2 6 //IN4 1
#define IN3_1 12 //IN1 2
#define IN3_2 13 //IN2 2
#define IN4_1 8 //IN3 2
#define IN4_2 9 //IN4 2


// Can be reduced to 3 if needed
#define HUZZAH_IN1 A0
#define HUZZAH_IN2 A1
#define HUZZAH_IN3 A2
#define HUZZAH_IN4 A3




#define ENABLE_AMOUNT 255 // 0 <= x <= 255

#define DEBUG_MODE 1

// States
#define NO_ACTION 0
#define ACTION1 1
#define ACTION2 2
#define ACTION3 3
#define ACTION4 4

int state;
int next_state;
void setup(){
  setup_pins();
  Serial.begin(9600); 
  Serial.println("Starting!!");
  state = NO_ACTION;
  next_state = NO_ACTION;
}
void loop(){
  pour_drink();
  int is_on = digitalRead(HUZZAH_IN1);
  if (is_on){
    if (DEBUG_MODE)
    Serial.println("HUZZAH1");
    next_state = ACTION1;
    return;
  }
  is_on = digitalRead(HUZZAH_IN2);
  if (is_on){
    if (DEBUG_MODE)
    Serial.println("HUZZAH2");
    next_state = ACTION2;
    return;

  }
  is_on = digitalRead(HUZZAH_IN3);
  if (is_on){
    if (DEBUG_MODE)
    Serial.println("HUZZAH3");
    next_state = ACTION3;
    return;

  }
  is_on = digitalRead(HUZZAH_IN4);
  if (is_on){
    if (DEBUG_MODE)
    Serial.println("HUZZAH4");
    next_state = ACTION4;
    return;

  }
  if (DEBUG_MODE)
    Serial.println("No HUZZAH INPUT");
  next_state = NO_ACTION;
  //delay(20); // Might consider changing this or removing this
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
}
void pour_drink(){
  if(state==next_state)
    return;
  if(state==ACTION1){
    turn_off1();

  }else if(state==ACTION2){
    turn_off2();

  }else if(state==ACTION3){
    turn_off3();

  }else if(state==ACTION4){
    turn_off4();

  }
  state = next_state;
  if(next_state==ACTION1){
    turn_on1();
  }else if(next_state==ACTION2){
    turn_on2();

  }else if(next_state==ACTION3){
    turn_on3();

  }else if(next_state==ACTION4){
    turn_on4();
  }
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