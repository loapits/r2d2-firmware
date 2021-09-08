#include <Arduino.h>
#include <Tone.h>
#include <Stepper.h>

// freePins =  a1, a3;

String incomingbyte; // переменная для приема данных
const int leftMotor1p1 = 5;
const int leftMotor1p2 = 4;
const int leftMotor1p3 = 3;
const int leftMotor1p4 = 2;

const int rightMotor1p1 = A7;
const int rightMotor1p2 = A6;
const int rightMotor1p3 = A5;
const int rightMotor1p4 = A4;

const int headMotor1 = A0;
const int headMotor2 = 13;
const int headMotor3 = 12;
const int headMotor4 = 11;

const int ledRed = 6;
const int ledBlue = A2;

const int triggerPin = 7;
const int echoPin = 8;

const int tonePin = 9;


bool isAuto = false;
long duration = 0;

const int stepsPerRev = 32;
Stepper head(stepsPerRev, headMotor1, headMotor2, headMotor3, headMotor4);
Stepper leftLeg(stepsPerRev, leftMotor1p1, leftMotor1p2, leftMotor1p3, leftMotor1p4);
Stepper rightLeg(stepsPerRev, rightMotor1p1, rightMotor1p2, rightMotor1p3, rightMotor1p4);

void setup() {
  Serial.begin(9600);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(ledBlue, OUTPUT);
  digitalWrite(ledBlue, LOW);
  pinMode(ledRed, OUTPUT);
  digitalWrite(ledRed, LOW);
}

// Calculate distance
long Distance(long time) {
  long distanceCalc;

  distanceCalc = ((time * 0.034) / 2);
  return distanceCalc;
}

void goForward() {
  leftLeg.setSpeed(700);
  leftLeg.step(stepsPerRev / 4);
  rightLeg.setSpeed(700);
  rightLeg.step(stepsPerRev / 4);
}

void goBack() {
  leftLeg.setSpeed(700);
  leftLeg.step(-stepsPerRev / 4);
  rightLeg.setSpeed(700);
  rightLeg.step(-stepsPerRev / 4);
} 

void goRigth() {
  leftLeg.setSpeed(700);
  leftLeg.step(stepsPerRev / 4);
  rightLeg.setSpeed(0);
}

void goLeft() {
  rightLeg.setSpeed(700);
  rightLeg.step(stepsPerRev / 4);
  leftLeg.setSpeed(0);
}

void stopRobot() {
  leftLeg.setSpeed(0);
  leftLeg.setSpeed(0);
}

void rightSpinHead() {  
  leftLeg.setSpeed(700);
  leftLeg.step(stepsPerRev / 4);
}

void leftSpinHead() {
  leftLeg.setSpeed(70);
  leftLeg.step(stepsPerRev / 4);
}

void stopSpinHead() {
  head.setSpeed(0);
}

//Основной цикл программы
void loop() {  
  if (Serial.available() > 0) {
    digitalWrite(ledBlue, HIGH);
    digitalWrite(ledRed, HIGH);
    
    incomingbyte = Serial.read();

    if (incomingbyte == "0") {
      isAuto = false;
      stopRobot();
    }

    if (incomingbyte == "1") {
      isAuto = false;
      goForward();
    }

    if (incomingbyte == "2") {
      isAuto = false;
      goBack();
    }

    if (incomingbyte == "3") {
      isAuto = false;
      goRigth();
    }
    
    if (incomingbyte == "4") {
      isAuto = false;
      goLeft();
    }

    if (incomingbyte == "d") {
      // crying song
    }

    if (incomingbyte == "e") {
      //question song
    }

    if (incomingbyte == "f") {
      // surprise song
    }

    if (incomingbyte == "g") {
      // quote song
    }

    if (incomingbyte == "h") {
      // offer song
    }

    if (incomingbyte == "i") {
      // broken song
    }

    if (incomingbyte == "6") {
      // autopilot
      isAuto = true;
    }
    
    if (incomingbyte == "7") {
      // blue light
    }

    if (incomingbyte == "8") {
      // Red light
    }
    
    if (incomingbyte == "9") {
      // led and blue light
    }

    if (incomingbyte == "a") {
      rightSpinHead();
    }
    
    if (incomingbyte == "b") {
      leftSpinHead();
    }

    if (incomingbyte == "c") {
      stopSpinHead();
    }
  } 

  if (isAuto == true) {
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);
    
    duration = pulseIn(echoPin, HIGH);
    long distanceCm = Distance(duration);

    if (distanceCm < 50) {
      goRigth();
      delay(100);
      goForward();
    }

    goForward();
    delay(1000);
  }
}