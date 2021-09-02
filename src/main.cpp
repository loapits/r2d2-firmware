#include <Arduino.h>
#include <Tone.h>
#include <Stepper.h>

char incomingbyte;

const int head1 = 10;
const int head2 = 11;
const int head3 = 12;
const int head4 = 13;
const int rightLeg1 = A0;
const int rightLeg2 = A1;
const int rightLeg3 = A2;
const int rightLeg4 = A3;
const int leftLeg1 = A4;
const int leftLeg2 = A5;
const int leftLeg3 = A6;
const int leftLeg4 = A7;

const int tonePin = 5;
const int ledRed = 6;
const int ledBlue = 7;
const int triggerPin = 8;
const int echoPin = 9;


bool isAuto = false;
long Duration = 0;

const int stepsPerRev = 32;
Stepper head(stepsPerRev, head1, head2, head3, head4);
Stepper leftLeg(stepsPerRev, leftLeg1, leftLeg2, leftLeg3, leftLeg4);
Stepper rightLeg(stepsPerRev, rightLeg1, rightLeg2, rightLeg3, rightLeg4);


class Robot {
  public:int cryNotes[58] = {
    659, 587, 739, 659, 698, 1046, 830, 739, 1046, 830, 739,
    932, 1318, 1108, 1396, 1661, 783, 1108, 1760, 1244, 2637,
    1244, 880, 987, 1479, 1108, 1318, 2093, 932, 987, 1244, 1760, 
    1396, 1046, 1108, 1244, 2093, 1046, 1108, 3135, 1244, 3135, 
    987, 2093, 880, 1244, 1108, 2637, 1244, 698, 1174, 1046, 783,
    739, 659, 622, 698, 783
  };

  public:int cryDuration[58] = {
    9, 26, 26, 9, 9, 9, 9, 9, 9, 9, 9, 17, 9, 17, 9, 9,
    9, 9, 9, 17, 9, 9, 9, 17, 9, 9, 17, 9, 17, 17, 9, 9,
    17, 9, 9, 26, 9, 9, 9, 9, 9, 61, 9, 9, 9, 9, 9, 9, 9, 
    9, 9, 9, 17, 9, 9, 9, 17
  };

  public:int cryDelay[58] = {
    20, 39, 29, 78, 10, 10, 10, 30, 10, 10, 10, 10, 29, 10, 
    49, 10, 10, 30, 69, 30, 19, 10, 10, 20, 19, 10, 10, 77, 
    10, 29, 19, 10, 10, 48, 20, 49, 29, 30, 30, 30, 10, 20, 
    117, 10, 20, 10, 20, 60, 10, 10, 10, 10, 40, 117, 10, 10, 
    10, 19
  };


  public:int questionNotes[34] = {
     2793, 3135, 1864, 1661, 1479, 1567, 1661, 1760, 1864, 1975, 2093, 2217, 2349, 2489, 2959, 2637, 2637, 2793, 2959, 2489, 2959, 2793, 1864, 1760, 1864, 1975, 2093, 2217, 2349, 2489, 2637, 2793, 2959, 3135
  };

  public:int questionDuration[34] = {
    17, 17, 9, 96, 17, 35, 9, 17, 17, 9, 9, 9, 9, 9, 26, 35, 35, 17, 17, 26, 9, 9, 17, 235, 17, 26, 44, 26, 26, 9, 17, 17, 26, 70
  };

  public:int questionDelay[34] = {
    19, 65, 10, 349, 19, 39, 10, 19, 19, 10, 10, 10, 10, 38, 29, 47, 47, 19, 330, 29, 105, 46, 19, 262, 19, 29, 48, 29, 49, 10, 19, 19, 29, 78
  };


  public:int surpriseNotes[35] = {
    233, 246, 277, 293, 349, 391, 440, 493, 1479, 1567, 1864, 2093, 2489, 739, 880, 659, 830, 880, 932, 783, 2793, 880, 1108, 1396, 1174, 1244, 1396, 1479, 1864, 2217, 2349, 2793, 2489, 987, 932
  };

  public:int surpriseDuration[35] = {
    9, 9, 9, 9, 9, 9, 9, 9, 17, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9
  };

  public:int surpriseDelay[35] = {
    10, 10, 10, 10, 10, 10, 10, 39, 19, 20, 10, 10, 58, 20, 10, 10, 10, 20, 10, 10, 10, 59, 10, 10, 10, 10, 10, 10, 10, 10, 10, 118, 50, 10, 10
  };


  public:int quoteNotes[41] = {
     1760, 1864, 1975, 2489, 2349, 1396, 1174, 1108, 1479, 2637, 1864, 415, 554, 622, 739, 440, 987, 1046, 739, 698, 987, 1174, 1864, 523, 698, 1174, 1661, 1479, 1760, 2217, 3135, 2217, 523, 1760, 2349, 1318, 1864, 2637, 2489, 1760, 1567
  };

  public:int quoteDuration[41] = {
    17, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 17, 9, 17, 9, 9, 9, 9, 17, 35, 26, 9, 9, 9, 9, 9, 9, 9, 9
  };

  public:int quoteDelay[41] = {
    19, 10, 10, 10, 59, 10, 10, 156, 10, 98, 10, 49, 10, 20, 10, 10, 29, 20, 20, 10, 10, 10, 117, 19, 39, 19, 10, 10, 10, 10, 49, 49, 29, 10, 10, 10, 10, 10, 68, 10, 10
  };


  public:int offerNotes[32] = {
    174, 554, 184, 195, 207, 233, 293, 233, 369, 440, 493, 554, 622, 698, 783, 1396, 1174, 1318, 1661, 1760, 2093, 2349, 2637, 2793, 2959, 3135, 1975, 1174, 554, 2217, 659, 783
  };

  public:int offerDuration[32] = {
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 17, 9, 9, 9, 9, 35, 9, 9, 9
  };

  public:int offerDelay[32] = {
    10, 10, 10, 10, 10, 20, 10, 10, 10, 20, 10, 10, 10, 20, 10, 10, 10, 10, 10, 10, 10, 10, 10, 19, 10, 380, 20, 90, 39, 10, 10, 10
  };

  
  public:int brokenNotes[23] = {
     1174, 1760, 987, 1661, 2793, 554, 587, 523, 2637, 2793, 1108, 523, 783, 493, 783, 1108, 1174, 493, 523, 207, 1046, 1108, 220 
  };

  public:int brokenDuration[23] = {
    9, 9, 9, 17, 17, 9, 9, 26, 9, 148, 9, 9, 9, 17, 9, 26, 26, 26, 26, 17, 17, 61, 9
  };

  public:int brokenDelay[23] = {
    10, 10, 10, 19, 19, 49, 89, 29, 10, 204, 10, 10, 49, 19, 10, 107, 39, 29, 87, 19, 19, 68, 10
  };
  
  public:void crying() {
    for (int i = 0; i < 58; i++) {  
      tone(tonePin, this->cryNotes[i], this->cryDuration[i]);
      delay(this->cryDelay[i]);
    };
   
    noTone(tonePin);
  }

  public:void r2d2QuestionSong1() {
    for (int i = 0; i < 34; i++) {  
      tone(tonePin, this->questionNotes[i], this->questionDuration[i]);
      delay(this->questionDelay[i]);
    }
  }

  public:void surpriceEl() {
    for (int i = 0; i < 32; i++) {  
      tone(tonePin, this->surpriseNotes[i], this->surpriseDuration[i]);
      delay(this->surpriseDelay[i]);
    }
  }

  public:void quoteTwo() {
    for (int i = 0; i < 41; i++) {  
      tone(tonePin, this->quoteNotes[i], this->quoteDuration[i]);
      delay(this->quoteDelay[i]);
    }
  }

  public:void offerSong() {
    for (int i = 0; i < 23; i++) {  
      tone(tonePin, this->offerNotes[i], this->offerDuration[i]);
      delay(this->offerDelay[i]);
    }
  }

  public:void brokenSong() { 
    for (int i = 0; i < 23; i++) {  
      tone(tonePin, this->brokenNotes[i], this->brokenDuration[i]);
      delay(this->brokenDelay[i]);
    }
  }
};

Robot rob = Robot();


void setup() {
  // Serial.begin(9600);
  // myStepper.setSpeed(5);
}

long Distance(long time) {
  long DistanceCalc;

  DistanceCalc = ((time * 0.034) / 2);
  return DistanceCalc;
}


void go_forward() {
  leftLeg.setSpeed(1);
  leftLeg.step(stepsPerRev);
}

void go_back() {
  leftLeg.step(-stepsPerRev);
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

void loop() {  
  leftLeg.setSpeed(700);
  leftLeg.step(stepsPerRev / 4);
  rightLeg.setSpeed(700);
  rightLeg.step(-stepsPerRev / 4);
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

    if (incomingbyte == 'd') {
      rob.crying();
    }

    if (incomingbyte == 'e') {
      rob.r2d2QuestionSong1();
    }

    if (incomingbyte == 'f') {
      rob.surpriceEl();
    }

    if (incomingbyte == 'g') {
      rob.quoteTwo();
    }

    if (incomingbyte == 'h') {
      rob.offerSong();
    }

    if (incomingbyte == 'i') {
      rob.brokenSong();
    }

    if (incomingbyte == '6') {
      isAuto = true;
    }
    
    if (incomingbyte == '7') {
      // digitalWrite(LedBlue, HIGH);
      // digitalWrite(LedRed, LOW);
    }

    if (incomingbyte == '8') {
      // digitalWrite(LedBlue, LOW);
      // digitalWrite(LedRed, HIGH);
    }
    
    if (incomingbyte == '9') {
      // digitalWrite(LedBlue, HIGH);
      // digitalWrite(LedRed, HIGH);
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
    // digitalWrite(TriggerPin, LOW);
    // delayMicroseconds(2);
    // digitalWrite(TriggerPin, HIGH);
    // delayMicroseconds(10);
    // digitalWrite(TriggerPin, LOW);
    
    // Duration = pulseIn(EchoPin, HIGH);
    // long Distance_cm = Distance(Duration);

    // if (Distance_cm < 50) {
    //   go_rigth();
    //   delay(100);
    //   go_forward();
    // }
    // go_forward();

    // delay(1000);
  }
}