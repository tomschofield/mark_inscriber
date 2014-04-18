#include <AFMotor.h>

//for the stepper
AF_Stepper motor(200, 2); 
boolean goForward=true;
boolean goBack=true;
int numturns=1;

//for the solonoid circuit
float mappedPot=0;
int analogPin =A0;
int potVal=0;
//only digital pins 2 and 13 are not used
int outPin=2;
char val; // Data received from the serial port
void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  motor.setSpeed(20);  // 10 rpm   

  pinMode(outPin, OUTPUT);  
}

void loop() {

  potVal = analogRead(analogPin);    
  mappedPot=map(potVal,0,1024,0,100);

  if (Serial.available()) { // If data is available to read,
    val = Serial.read(); // read it and store it in val
    //if the serial reads between 0 and 9 then make that the number of motor increments
    if(int(val)>=48 && int(val)<=57){
      numturns=map(int(val),48,57,0,2000);
      Serial.println(numturns);
    }

  }
  if (val == 'H') { // If H was received
    goForward=true;
    motor.step(numturns, FORWARD, DOUBLE);
    motor.release();
    val='x';

  }  
  if (val == 'L') {
    goForward=false;
    motor.step(numturns, BACKWARD, DOUBLE);
    motor.release();
    val='x';

  }
  if (val == 'F') { // If H was received
    motor.setSpeed(30);  // 10 rpm   
    val='x';

  }  
  if (val == 'S') {
    motor.setSpeed(20);  // 10 rpm   =false;
    val='x';

  }

  if (val == 'M') { // If H was received
    int numCycles=50;//mappedPot;
    for(int i=0;i<numCycles;i++){
      digitalWrite(outPin, HIGH);  
      delay(1);

    }
    digitalWrite(outPin, LOW);  
    val='x';  
  }

}


/*
void fire(){
 for(int i=0;i<50;i++){
    digitalWrite(pin, HIGH);  
    delay(1);

  }
  digitalWrite(pin, LOW);  
  delay(500);
}
*/



