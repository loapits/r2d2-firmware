#include "Arduino.h"

char incomingbyte; // переменная для приема данных
const int A_IA = 4;
const int A_IB = 5;
const int B_IA = 6;
const int B_IB = 7;
const int TriggerPin = 8;
const int EchoPin = 9;

bool isAuto = false;
long Duration = 0;

void setup() {
  Serial.begin(9600);
  pinMode(TriggerPin, OUTPUT);
  pinMode(EchoPin, INPUT);

  pinMode(A_IA, OUTPUT);
  digitalWrite(A_IA, HIGH);
  pinMode(A_IB, OUTPUT);
  digitalWrite(A_IB, HIGH);
  pinMode(B_IA, OUTPUT);
  digitalWrite(B_IA, HIGH);
  pinMode(B_IB, OUTPUT);
  digitalWrite(B_IB, HIGH);

}

long Distance(long time) {
  long DistanceCalc;

  DistanceCalc = ((time * 0.034) / 2);
  return DistanceCalc;
}

void go_forward() {
  digitalWrite(A_IA, LOW);
  digitalWrite(A_IB, HIGH);

  digitalWrite(B_IA, LOW);
  digitalWrite(B_IB, HIGH);  
}

void go_back() {
  digitalWrite(A_IA, HIGH);
  digitalWrite(A_IB, LOW);
  
  digitalWrite(B_IA, HIGH);
  digitalWrite(B_IB, LOW);
}

void go_rigth() {
  digitalWrite(A_IA, LOW);
  digitalWrite(A_IB, LOW);
  
  digitalWrite(B_IA, HIGH);
  digitalWrite(B_IB, LOW);
}

void go_left() {
  digitalWrite(A_IA, LOW);
  digitalWrite(A_IB, HIGH);

  digitalWrite(B_IA, LOW);
  digitalWrite(B_IB, LOW);
}

void stop_robot() {

  digitalWrite(A_IA, LOW);
  digitalWrite(A_IB, LOW);

  digitalWrite(B_IA, LOW);
  digitalWrite(B_IB, LOW);
}

//Основной цикл программы
void loop() {
  if (Serial.available() > 0) {
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