
/*
// PIN Setup if huzzah is used

*/
int state; 
#define WAITING_FOR_MESSAGE_STATE 0
#define WAITING_FOR_MOVEMENT_STATE 1
#define DISPENSING_STATE 2

void setup(){
  setup_pins();
  Serial.begin(9600); 
  Serial.println("Starting!!");
  state = WAITING_FOR_MESSAGE_STATE;
}
void loop(){
  
}
// Set pins to be output or input
void setup_pins(){


}
