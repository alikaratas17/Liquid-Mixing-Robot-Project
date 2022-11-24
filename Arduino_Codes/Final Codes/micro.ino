#define ENABLE_MOTOR_A_PIN 9
#define IN1_PIN 8
#define IN2_PIN 7

#define ENABLE_MOTOR_B_PIN 4
#define IN3_PIN 5
#define IN4_PIN 6

#define ECHO_PIN 11
#define TRIG_PIN 12

#define EN_A_SPEED_CONTROL 255 // 0<= <=255
#define EN_B_SPEED_CONTROL 255 // 0<= <=255



void setup(){
  setup_pins();
  stop_motors();
  Serial.begin(9600); 
  Serial.println("Starting!!");
}
void loop(){
  int dist = get_distance();
  if (dist<30){
    go_forward();
  }else{
    stop_motors();
  }
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
int get_distance(){
  digitalWrite(TRIG_PIN, LOW); 
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH); 
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH);
  int distance = duration * 0.034 / 2;
  return distance;
}
