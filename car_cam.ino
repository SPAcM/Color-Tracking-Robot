int posX = 256;
int time_waiting=0;
long previous_millis=0;
long stop_millis=0;
long start_millis=0;
long interval=1000; // this value is how long we want the program to wait while the distance forward is less than 150, can change
int distance_forward=0;
int distance_left=0;
int distance_right=0;
int wall_diagonal_left=100; //this value is how far away the wall should be to the left
int turning_interval=1000; // this value is how long we want the side sensors to sense a large value before turning
int turning_millis=0;
int turning_millis2=0;
int first_turn_counter=0;
int straight_counter=0;
int motor_turn_pwm=60; // this value will change how sharp of a corner the rover makes min=0 max=255

int E1 = 6;     //M1 Speed Control
int E2 = 5;     //M2 Speed Control
int M1 = 4;    //M1 Direction Control
int M2 = 7;    //M2 Direction Control




void setup(){
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  
  //Start Serial
  Serial.begin(9600);
  
  //delay(2000);
}

double sense(int sensor_number){
  double result=0;
  if(sensor_number==1){ // FRONT SENSOR
    digitalWrite(9,HIGH);
    delayMicroseconds(20);
    digitalWrite(9,LOW);
    result=analogRead(A0);
    return result;
  }
  if(sensor_number==2){ // LEFT SENSOR
    digitalWrite(10,HIGH);
    delayMicroseconds(20);
    digitalWrite(10,LOW);
    result=analogRead(A1);
    return result;
  }
  if(sensor_number==3){
    // for future addition of an additional right sensor
  }
}

void stop_car(void)                    //Stop
{
  digitalWrite(E1,LOW);  
  digitalWrite(E2,LOW);
  digitalWrite(M1,LOW);
  digitalWrite(M2,LOW);  
}  

void advance()          //Move forward
{
  analogWrite (E1,255);      //PWM Speed Control
  digitalWrite(M1,HIGH);   
  analogWrite (E2,255);   
  digitalWrite(M2,HIGH);
} 
void back_off ()          //Move backward
{
  analogWrite (E1,255);
  digitalWrite(M1,LOW);  
  analogWrite (E2,255);   
  digitalWrite(M2,LOW);
}
void turn_L ()             //Turn Left
{
  analogWrite (E1,motor_turn_pwm);
  digitalWrite(M1,HIGH);   
  analogWrite (E2,255);   
  digitalWrite(M2,HIGH);
}
void turn_R ()             //Turn Right
{
  analogWrite (E1,255);
  digitalWrite(M1,HIGH);   
  analogWrite (E2,motor_turn_pwm);   
  digitalWrite(M2,HIGH);
}
void rotate_R () {
  analogWrite (E1,255);
  digitalWrite(M1,LOW);   
  analogWrite (E2,255);   
  digitalWrite(M2,HIGH);
  delay(500);
}



void loop(){
  
  if(Serial.available() > 0){
      posX = Serial.read();
  }
  
  if(posX < 114){
      turn_L();
  }
  else if(posX > 114 && posX < 142){
      advance();    
  }
  else if(posX > 143 && posX < 255){
      turn_R();
  }
  else{
      stop_car();
  }
  
  //The sonic sensor control loop will be re-integrated after the camera is worked out 
  /*distance_forward=sense(1);
  distance_left=sense(2);

  if(distance_forward < 50){ //150 here is the distance in cm we want to allow for the thing to stop before
    while(distance_forward < 50) {
      stop_car();
      rotate_R();  
      distance_forward=sense(1);            
    }
  }
  else {
     if(distance_left < 80){
      turn_R(); 
     }
     else if(distance_left > 100) {
      turn_L(); 
     }
     else {
      advance(); 
     }
  }
 */
 
}
