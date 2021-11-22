 #include <Arduino.h>
 #include <Stepper.h>

char incomingbyte;
const int Aia = A4;
const int Aib = A5;
const int Bia = A2;
const int Bib = A3;
const int headMotor1 = 9;
const int headMotor2 = 10; 
const int headMotor3 = 11;
const int headMotor4 = 12;
const int ledRed = 3;
const int ledBlue = 4;
const int stepsPerRevolution = 2048;

Stepper motor(stepsPerRevolution, headMotor1, headMotor3, headMotor2, headMotor4);

void setup() {
  Serial.begin(9600);
  pinMode(ledBlue, OUTPUT);
  pinMode(ledBlue, OUTPUT);
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
  motor.setSpeed(12);
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
  stopRobot(); 
  motor.step(stepsPerRevolution / 4);
  delay(100);
  motor.step(-stepsPerRevolution / 4);
  digitalWrite(headMotor1, LOW);
  digitalWrite(headMotor2, LOW);
  digitalWrite(headMotor3, LOW);
  digitalWrite(headMotor4, LOW); 
}

void leftSpinHead() {
  stopRobot();
  motor.step(-stepsPerRevolution / 4);
  motor.step(stepsPerRevolution / 4);
  digitalWrite(headMotor1, LOW);
  digitalWrite(headMotor2, LOW);
  digitalWrite(headMotor3, LOW);
  digitalWrite(headMotor4, LOW); 
}

void stopSpinHead() {
  digitalWrite(headMotor1, LOW);
  digitalWrite(headMotor2, LOW);
  digitalWrite(headMotor3, LOW);
  digitalWrite(headMotor4, LOW); 
}

void loop() {
  if (Serial.available() > 0) {
    incomingbyte = Serial.read();

    digitalWrite(ledBlue, HIGH);
    digitalWrite(ledRed, HIGH);

    if (incomingbyte == '0') {
      stopRobot();
    }

    if (incomingbyte == '1') {
      goForward();
    }

    if (incomingbyte == '2') {
      goBack();
    }

    if (incomingbyte == '3') {
      goRigth();
    }
    
    if (incomingbyte == '4') {
      goLeft();
    }

    if (incomingbyte == 'a') {
      rightSpinHead();
    }
    
    if (incomingbyte == 'b') {
      leftSpinHead();
    }

    if (incomingbyte == 'c') {
      stopSpinHead();
    }

    if (incomingbyte == '7') {
      digitalWrite(ledBlue, HIGH);
      digitalWrite(ledRed, LOW);
    }

    if (incomingbyte == '8') {
      digitalWrite(ledRed, HIGH);
      digitalWrite(ledBlue, LOW);
    }
    
    if (incomingbyte == '9') {
      digitalWrite(ledRed, HIGH);
      digitalWrite(ledBlue, HIGH);
    }
  }
}

