#include "Arduino.h"

const int A_IA = 4;
const int A_IB = 5;
const int TriggerPin = 8;
const int EchoPin = 9;

long Duration = 0;


void setup() {
  pinMode(TriggerPin, OUTPUT);
  pinMode(EchoPin, INPUT);

  pinMode(A_IA, OUTPUT);
  digitalWrite(A_IA, HIGH);
  pinMode(A_IB, OUTPUT);
  digitalWrite(A_IB, HIGH);
  Serial.begin(9600);
}

long Distance(long time) {
  long DistanceCalc;

  DistanceCalc = ((time * 0.034) / 2);
  return DistanceCalc;
}

void loop() {
  digitalWrite(TriggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TriggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TriggerPin, LOW);
  
  Duration = pulseIn(EchoPin, HIGH);
  long Distance_cm = Distance(Duration);

  if (Distance_cm < 7) {
    digitalWrite(A_IA, HIGH);
    digitalWrite(A_IB, HIGH);
  } else {
    digitalWrite(A_IA, HIGH);
    digitalWrite(A_IB, LOW);
  }

  delay(1000);
}
