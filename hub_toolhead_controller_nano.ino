/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

//DC motor control - H-Bridge L298N
int hpin1 = 8;
int hpin2 = 7;
int ENA_pin = 11;

int pos = 0;    // variable to store the servo position

int cmd = 0;
//int roll_time = 4;

const int PUSHER_OUT = 0;
const int PUSHER_IN = 1;
const int SPIN_IN = 4;
const int SPIN_OUT = 5;
const int SPIN_IDLE = 6;

void setup() {
  pinMode(hpin1, OUTPUT);
  pinMode(hpin2, OUTPUT);
  pinMode(ENA_pin, OUTPUT);
  
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  
  Serial.begin(115200);
  //Serial.println("Serial Started.");
  myservo.write(0);
  delay(1000);
}

void loop() {
  while(Serial.available() == 0){
  }
  char input = Serial.read();
  cmd = input - '0';
  //Serial.println(cmd);

  analogWrite(ENA_pin,150);
  
  if (cmd == PUSHER_OUT){
    //PUSHER OUT
    if (pos <= 0){
      for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
        // in steps of 1 degree
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(15);                       // waits 15ms for the servo to reach the position
      }
      pos = 90;
    }
    Serial.println(PUSHER_OUT);
  }
  else if (cmd == PUSHER_IN){ 
    //PUSHER IN
    //Serial.println("Command = 1");
    
    if (pos >= 90){
      for (pos = 90; pos >= 0; pos -= 1) { 
        myservo.write(pos);              
        delay(15);                       
      }
      pos = 0;
    }
    Serial.println(PUSHER_IN);
  }
  else if (cmd == SPIN_IN){ 
    //SPIN IN
    //Serial.println("Command = 4");
    digitalWrite(hpin1, LOW);
    digitalWrite(hpin2, HIGH);
 
    Serial.println(SPIN_IN); 
  }
  else if (cmd == SPIN_OUT){ 
    //SPIN OUT
    //Serial.println("Command = 5");
    digitalWrite(hpin1, HIGH);
    digitalWrite(hpin2, LOW);
 
    Serial.println(SPIN_OUT); 
  }
  else if (cmd == SPIN_IDLE){ 
    //SPIN OUT
    //Serial.println("Command = 6");
    digitalWrite(hpin1, LOW);
    digitalWrite(hpin2, LOW);
 
    Serial.println(SPIN_IDLE); 
  }
}
