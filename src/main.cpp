#include <Arduino.h>
#include <Tone.h>
#include <Stepper.h>

char incomingbyte;

const int Aia = 9;
const int Aib = 10;
const int Bia = 11;
const int Bib = 12;

const int headMotor1 = A0;
const int headMotor2 = 13; 
const int headMotor3 = 12;
const int headMotor4 = 11;

const int ledRed = 6;
const int ledBlue = A2;

const int triggerPin = 2;
const int echoPin = 3;

const int tonePin = 9;

long duration = 0;

const int stepsPerRev = 32;

Stepper head(stepsPerRev, headMotor1, headMotor2, headMotor3, headMotor4);

void setup() {
  Serial.begin(9600);
  Serial.begin(9600);


  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);

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
  head.setSpeed(700);
  head.step(stepsPerRev / 4);
}

void leftSpinHead() {
  head.setSpeed(70);
  head.step(stepsPerRev / 4);
}

void stopSpinHead() {
  head.setSpeed(0);
}



// void song() {
//     int notes[32] = {
//     174, 554, 184, 195, 207, 233, 293, 233, 369, 440, 493, 554, 622, 698, 783, 1396, 1174, 1318, 1661, 1760, 2093, 2349, 2637, 2793, 2959, 3135, 1975, 1174, 554, 2217, 659, 783
//   };

//   int duration[32] = {
//     9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 17, 9, 9, 9, 9, 35, 9, 9, 9
//   };

//   int delaed[32] = {
//     10, 10, 10, 10, 10, 20, 10, 10, 10, 20, 10, 10, 10, 20, 10, 10, 10, 10, 10, 10, 10, 10, 10, 19, 10, 380, 20, 90, 39, 10, 10, 10
//   };

//   for (int i = 0; i < 58; i++) {  
//       tone(tonePin, notes[i], duration[i]);
//       delay(delaed[i]);
//     };
// }

String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i) == separator || i == maxIndex){
      found++;
      strIndex[0] = strIndex[1]+1;
      strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}


int* getIntArr(String str) {
  String input = "3,2,7,12,14,2";  
  int * intArray = new int[str.length()];  
  int arrayCounter = 0; //needed
  for (int i = 0; i < input.length(); ++i) {  
    if(input[i] != ',') {  //Notice the single quotes for a character  
      intArray[arrayCounter] = input[i];  
      arrayCounter++;
    }  
  }

  return intArray;  
}

void convertSong(String message) {
  int* notes = getIntArr(getValue(message, ';', 0));
  int* durations = getIntArr(getValue(message, ';', 1));
  int* delays = getIntArr(getValue(message, ';', 2));


  for (int i = 0; i < 58; i++) {  
    tone(tonePin, notes[i], durations[i]);
    delay(delays[i]);
  };
  noTone(tonePin);
}



void loop() {
  if (Serial.available() > 0) {
    String message = Serial.readStringUntil('\n');

    digitalWrite(ledBlue, HIGH);
    digitalWrite(ledRed, HIGH);
    
    Serial.print(message);

    // // incomingbyte = Serial.read();
    // if (message.length() > 1) {
      convertSong(message);
      Serial.println("Yeah");
    // }

    // if (message == "0") {
    //   stopRobot();
    // }

    // if (message == "1") {
    //   goForward();
    // }

    // if (message == "2") {
    //   goBack();
    // }

    // if (message == "3") {
    //   goRigth();
    // }
    
    // if (message == "4") {
    //   goLeft();
    // }

    // if (message == "a") {
    //   rightSpinHead();
    // }
    
    // if (message == "b") {
    //   leftSpinHead();
    // }

    // if (message == "c") {
    //   stopSpinHead();
    // }

    // // if (incomingbyte[0] == "d") {
    // //   songConverter(incomingbyte);
    //   // crying song
    // // }

    // if (message == "7") {
    //   digitalWrite(ledBlue, HIGH);
    //   digitalWrite(ledRed, LOW);
    // }

    // if (message == "8") {
    //   digitalWrite(ledRed, HIGH);
    //   digitalWrite(ledBlue, LOW);
    // }
    
    // if (message == "9") {
    //   digitalWrite(ledRed, HIGH);
    //   digitalWrite(ledBlue, HIGH);
    // }
  }
}