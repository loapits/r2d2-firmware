#include "Arduino.h"

char incomingbyte; // переменная для приема данных
const int AIA = 4;
const int AIB = 5;
const int BIA = 6;
const int BIB = 7;
const int TriggerPin = 8;
const int EchoPin = 9;
const int LedRed = 10;
const int LedBlue = 11;

const int HeadBIA = 2;
const int HeadBIB = 3;


bool isAuto = false;
long Duration = 0;

void setup() {
  Serial.begin(9600);
  pinMode(TriggerPin, OUTPUT);
  pinMode(EchoPin, INPUT);

  pinMode(LedBlue, OUTPUT);
  digitalWrite(LedBlue, LOW);
  pinMode(LedRed, OUTPUT);
  digitalWrite(LedRed, LOW);

  pinMode(HeadBIA, OUTPUT);
  digitalWrite(HeadBIA, HIGH);
  pinMode(HeadBIB, OUTPUT);
  digitalWrite(HeadBIB, HIGH);

  pinMode(AIA, OUTPUT);
  digitalWrite(AIA, HIGH);
  pinMode(AIB, OUTPUT);
  digitalWrite(AIB, HIGH);
  pinMode(BIA, OUTPUT);
  digitalWrite(BIA, HIGH);
  pinMode(BIB, OUTPUT);
  digitalWrite(BIB, HIGH);
}

long Distance(long time) {
  long DistanceCalc;

  DistanceCalc = ((time * 0.034) / 2);
  return DistanceCalc;
}

void go_forward() {
  digitalWrite(AIA, LOW);
  digitalWrite(AIB, HIGH);

  digitalWrite(BIA, LOW);
  digitalWrite(BIB, HIGH);  
}

void go_back() {
  digitalWrite(AIA, HIGH);
  digitalWrite(AIB, LOW);
  
  digitalWrite(BIA, HIGH);
  digitalWrite(BIB, LOW);
}

void go_rigth() {
  digitalWrite(AIA, LOW);
  digitalWrite(AIB, LOW);
  
  digitalWrite(BIA, HIGH);
  digitalWrite(BIB, LOW);
}

void go_left() {
  digitalWrite(AIA, LOW);
  digitalWrite(AIB, HIGH);

  digitalWrite(BIA, LOW);
  digitalWrite(BIB, LOW);
}

void stop_robot() {
  digitalWrite(AIA, LOW);
  digitalWrite(AIB, LOW);

  digitalWrite(BIA, LOW);
  digitalWrite(BIB, LOW);
}

void right_spin_head() {  
  digitalWrite(HeadBIA, LOW);
  digitalWrite(HeadBIB, HIGH);
}

void left_spin_head() {
  digitalWrite(HeadBIA, HIGH);
  digitalWrite(HeadBIB, LOW);
}

void stop_spin_head() {
  digitalWrite(HeadBIA, LOW);
  digitalWrite(HeadBIB, LOW);
}



//Основной цикл программы
void loop() {
  if (Serial.available() > 0) {
    digitalWrite(LedBlue, HIGH);
    digitalWrite(LedRed, HIGH);
    
    incomingbyte = Serial.read();

    if (incomingbyte == '0') {
      isAuto = false;
      stop_robot();
    }

    if (incomingbyte == '1') {
      isAuto = false;
      go_forward();
    }

    if (incomingbyte == '2') {
      isAuto = false;
      go_back();
    }

    if (incomingbyte == '3') {
      isAuto = false;
      go_rigth(); 
    }
    
    if (incomingbyte == '4') {
      isAuto = false;
      go_left();
    }

    if (incomingbyte == '5') {
      isAuto = false;
    }

    if (incomingbyte == '6') {
      isAuto = true;
    }
    
    if (incomingbyte == '7') {
      digitalWrite(LedBlue, HIGH);
      digitalWrite(LedRed, LOW);
    }

    if (incomingbyte == '8') {
      digitalWrite(LedBlue, LOW);
      digitalWrite(LedRed, HIGH);
    }
    
    if (incomingbyte == '9') {
      digitalWrite(LedBlue, HIGH);
      digitalWrite(LedRed, HIGH);
    }

    if (incomingbyte == 'a') {
      right_spin_head();
    }
    
    if (incomingbyte == 'b') {
      left_spin_head();
    }

    if (incomingbyte == 'c') {
      stop_spin_head();
    }
  } 

  if (isAuto == true) {
    digitalWrite(TriggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(TriggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(TriggerPin, LOW);
    
    Duration = pulseIn(EchoPin, HIGH);
    long Distance_cm = Distance(Duration);

    if (Distance_cm < 50) {
      go_rigth();
      delay(100);
      go_forward();
    }
    go_forward();

    delay(1000);
  }
}