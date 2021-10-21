#include <Arduino.h>
#include <Tone.h>
#include <Stepper.h>

char incomingbyte;

const int Aia = A4;
const int Aib = A5;
const int Bia = A2;
const int Bib = A3;

const int headMotor1 = 9 ;
const int headMotor2 = 10; 
const int headMotor3 = 11;
const int headMotor4 = 12;

const int ledRed = 3;
const int ledBlue = 4;

const int tonePin = 2;

const int stepsPerRev = 24;

Stepper head(stepsPerRev, headMotor1, headMotor2, headMotor3, headMotor4);
Stepper headRev(stepsPerRev, headMotor1, headMotor3, headMotor2, headMotor4);


void setup() {
  Serial.begin(9600);

  pinMode(ledBlue, OUTPUT);
  digitalWrite(ledBlue, LOW);
  pinMode(ledRed, OUTPUT);
  digitalWrite(ledRed, LOW);

  pinMode(Aia, OUTPUT);
  digitalWrite(Aia, LOW);
  pinMode(Aib, OUTPUT);
  digitalWrite(Aib, LOW);
  pinMode(Bia, OUTPUT);
  digitalWrite(Bia, LOW);
  pinMode(Bib, OUTPUT);
  digitalWrite(Bib, LOW);
}

void goForward() {
  digitalWrite(Aia, LOW);
  digitalWrite(Aib, HIGH);
  digitalWrite(Bia, LOW);
  digitalWrite(Bib, HIGH);
}

void goBack() {
  digitalWrite(Aia, HIGH);
  digitalWrite(Aib, LOW);
  digitalWrite(Bia, HIGH);
  digitalWrite(Bib, LOW);
} 

void goRigth() {
  digitalWrite(Aia, LOW);
  digitalWrite(Aib, HIGH);
  digitalWrite(Bia, HIGH);
  digitalWrite(Bib, LOW);
}

void goLeft() {
  digitalWrite(Aia, HIGH);
  digitalWrite(Aib, LOW);
  digitalWrite(Bia, LOW);
  digitalWrite(Bib, HIGH);
}

void stopRobot() {
  digitalWrite(Aia, LOW);
  digitalWrite(Aib, LOW);
  digitalWrite(Bia, LOW);
  digitalWrite(Bib, LOW);
}

void rightSpinHead() {  
  headRev.setSpeed(600);
  headRev.step(stepsPerRev / 4);
}

void leftSpinHead() {

  head.setSpeed(600);
  head.step(stepsPerRev / 4);
}

void stopSpinHead() {
  head.setSpeed(0);
  headRev.setSpeed(0);
}

void loop() {
  if (Serial.available() > 0) {
    String message = Serial.readStringUntil('\n');

    digitalWrite(ledBlue, HIGH);
    digitalWrite(ledRed, HIGH);
    

    if (message.length() > 1) {
      // convertSong(message);
      Serial.print(message);
    }

    if (message == "0") {
      stopRobot();
    }

    if (message == "1") {
      goForward();
    }

    if (message == "2") {
      goBack();
    }

    if (message == "3") {
      goRigth();
    }
    
    if (message == "4") {
      goLeft();
    }

    if (message == "a") {
      rightSpinHead();
    }
    
    if (message == "b") {
      leftSpinHead();
    }

    if (message == "c") {
      stopSpinHead();
    }

    if (message == "7") {
      digitalWrite(ledBlue, HIGH);
      digitalWrite(ledRed, LOW);
    }

    if (message == "8") {
      digitalWrite(ledRed, HIGH);
      digitalWrite(ledBlue, LOW);
    }
    
    if (message == "9") {
      digitalWrite(ledRed, HIGH);
      digitalWrite(ledBlue, HIGH);
    }
  }
}