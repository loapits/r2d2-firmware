#include <Arduino.h>
#include <Tone.h>
#include <Stepper.h>


// freePins =  a1, a3;

char incomingbyte; // переменная для приема данных
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

void go_forward() {

}

void go_back() {

} 

void go_rigth() {

}

void go_left() {

}

void stop_robot() {

}

void right_spin_head() {  

}

void left_spin_head() {

}

void stop_spin_head() {

}

//Основной цикл программы
void loop() {  
  if (Serial.available() > 0) {
    digitalWrite(ledBlue, HIGH);
    digitalWrite(ledRed, HIGH);
    
    incomingbyte = Serial.read();

    if (incomingbyte == '0') {
      isAuto = false;
      // stop robot
    }

    if (incomingbyte == '1') {
      isAuto = false;
      //go forward
    }

    if (incomingbyte == '2') {
      isAuto = false;
      // go back
    }

    if (incomingbyte == '3') {
      // go rigth
      isAuto = false;
    }
    
    if (incomingbyte == '4') {
      isAuto = false;
      // go left
    }

    if (incomingbyte == 'd') {
      // crying song
    }

    if (incomingbyte == 'e') {
      //question song
    }

    if (incomingbyte == 'f') {
      // surprise song
    }

    if (incomingbyte == 'g') {
      // quote song
    }

    if (incomingbyte == 'h') {
      // offer song
    }

    if (incomingbyte == 'i') {
      // broken song
    }

    if (incomingbyte == '6') {
      // autopilot
      isAuto = true;
    }
    
    if (incomingbyte == '7') {
      // blue light
    }

    if (incomingbyte == '8') {
      // Red light
    }
    
    if (incomingbyte == '9') {
      // led and blue light
    }

    if (incomingbyte == 'a') {
      // Spin head to right
    }
    
    if (incomingbyte == 'b') {
      // spin head to left
    }

    if (incomingbyte == 'c') {
      // stop spinning of the head 
    }
  } 

  if (isAuto == true) {
    // digitalWrite(TriggerPin, LOW);
    // delayMicroseconds(2);
    // digitalWrite(TriggerPin, HIGH);
    // delayMicroseconds(10);
    // digitalWrite(TriggerPin, LOW);
    
    // duration = pulseIn(echoPin, HIGH);
    // long distance_cm = Distance(duration);

    // if (distance_cm < 50) {
    //   go_rigth();
    //   delay(100);
    //   go_forward();
    // }
    // go_forward();

    // delay(1000);
  }
}