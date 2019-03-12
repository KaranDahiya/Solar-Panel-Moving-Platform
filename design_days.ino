#include <Servo.h>

// servo motors
Servo servoOne;

// servo panelPosition
int panelPosition = 90;

// photodiode sensors
int sensorOne = A0; // whatever pin # we decide (must be analog)
int sensorOneVal = 0;
int sensorTwo = A2; // whatever pin # we decide (must be analog)
int sensorTwoVal = 0; 

// photodiode threshold
int threshold = 3;

// difference between sensor values
int sensorDifference = 0;

void setup() {
  // put your setup code here, to run once:

  // setup servo motor
  servoOne.attach(3);

  // setup photodiodes as inputs
  pinMode(sensorOne, INPUT);
  pinMode(sensorTwo, INPUT);
  //pinMode(sensorThree, INPUT);
  
  // console output enabled
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  // gets photodiode sensor values
  sensorOneVal = analogRead(sensorOne);
  // delay(5);
  sensorTwoVal = analogRead(sensorTwo);
  // delay(5);

  // displays sensor values
  Serial.print("Sensor 1: ");
  Serial.println(sensorOneVal);
  Serial.print("Sensor 2: ");
  Serial.println(sensorTwoVal);
 
  // SERVO CONTROL

  // calculates current value of sensors' difference
  if(sensorOneVal > sensorTwoVal)
    sensorDifference = sensorOneVal - sensorTwoVal;
  else
    sensorDifference = sensorTwoVal - sensorOneVal;
  
  // if light is hitting both sensors, do nothing
  if(sensorDifference < threshold) {
    Serial.println("Servo: hold");
  }
  // if light is hitting sensor 1, move in that direction
  else if(sensorOneVal > sensorTwoVal) {
    panelPosition += 5; // increments servo angle panelPosition
    Serial.println("Servo: to sensor 1");
  }
  // if light is hitting sensor 2, move in that direction
  else if(sensorOneVal < sensorTwoVal) {
    panelPosition -= 5; // increments servo angle panelPosition
    Serial.println("Servo: to sensor 2");
  }

  // sets panelPosition of servo motor
  servoOne.write(panelPosition);

  // delay
  delay(15);
}
