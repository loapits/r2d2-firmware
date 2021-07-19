#include <Arduino.h>
#include <Tone.h>

char incomingbyte; // переменная для приема данных
const int AIA = A4;
const int AIB = A5;
const int BIA = 6;
const int BIB = 7;
const int TriggerPin = 8;
const int EchoPin = 9;
const int LedRed = 10;
const int LedBlue = 11;

const int HeadBIA = 2;
const int HeadBIB = 3;

const int tonePin = 12;

bool isAuto = false;
long Duration = 0;
 


class Cry {
  public:int notes[58] = {
    659, 587, 739, 659, 698, 1046, 830, 739, 1046, 830, 739,
    932, 1318, 1108, 1396, 1661, 783, 1108, 1760, 1244, 2637,
    1244, 880, 987, 1479, 1108, 1318, 2093, 932, 987, 1244, 1760, 
    1396, 1046, 1108, 1244, 2093, 1046, 1108, 3135, 1244, 3135, 
    987, 2093, 880, 1244, 1108, 2637, 1244, 698, 1174, 1046, 783,
    739, 659, 622, 698, 783
  };

  public:int duration[58] = {
    9, 26, 26, 9, 9, 9, 9, 9, 9, 9, 9, 17, 9, 17, 9, 9,
    9, 9, 9, 17, 9, 9, 9, 17, 9, 9, 17, 9, 17, 17, 9, 9,
    17, 9, 9, 26, 9, 9, 9, 9, 9, 61, 9, 9, 9, 9, 9, 9, 9, 
    9, 9, 9, 17, 9, 9, 9, 17
  };

  public:int delay[58] = {
    20, 39, 29, 78, 10, 10, 10, 30, 10, 10, 10, 10, 29, 10, 
    49, 10, 10, 30, 69, 30, 19, 10, 10, 20, 19, 10, 10, 77, 
    10, 29, 19, 10, 10, 48, 20, 49, 29, 30, 30, 30, 10, 20, 
    117, 10, 20, 10, 20, 60, 10, 10, 10, 10, 40, 117, 10, 10, 
    10, 19
  };
};

class R2D2Question {
  public:int notes[34] = {
     2793, 3135, 1864, 1661, 1479, 1567, 1661, 1760, 1864, 1975, 2093, 2217, 2349, 2489, 2959, 2637, 2637, 2793, 2959, 2489, 2959, 2793, 1864, 1760, 1864, 1975, 2093, 2217, 2349, 2489, 2637, 2793, 2959, 3135
  };

  public:int duration[34] = {
    17, 17, 9, 96, 17, 35, 9, 17, 17, 9, 9, 9, 9, 9, 26, 35, 35, 17, 17, 26, 9, 9, 17, 235, 17, 26, 44, 26, 26, 9, 17, 17, 26, 70
  };

  public:int delay[34] = {
    19, 65, 10, 349, 19, 39, 10, 19, 19, 10, 10, 10, 10, 38, 29, 47, 47, 19, 330, 29, 105, 46, 19, 262, 19, 29, 48, 29, 49, 10, 19, 19, 29, 78
  };
};

class Surprise {
  public:int notes[35] = {
    233, 246, 277, 293, 349, 391, 440, 493, 1479, 1567, 1864, 2093, 2489, 739, 880, 659, 830, 880, 932, 783, 2793, 880, 1108, 1396, 1174, 1244, 1396, 1479, 1864, 2217, 2349, 2793, 2489, 987, 932
  };

  public:int duration[35] = {
    9, 9, 9, 9, 9, 9, 9, 9, 17, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9
  };

  public:int delay[35] = {
    10, 10, 10, 10, 10, 10, 10, 39, 19, 20, 10, 10, 58, 20, 10, 10, 10, 20, 10, 10, 10, 59, 10, 10, 10, 10, 10, 10, 10, 10, 10, 118, 50, 10, 10
  };
};

class QuoteThree {
  public:int notes[41] = {
     1760, 1864, 1975, 2489, 2349, 1396, 1174, 1108, 1479, 2637, 1864, 415, 554, 622, 739, 440, 987, 1046, 739, 698, 987, 1174, 1864, 523, 698, 1174, 1661, 1479, 1760, 2217, 3135, 2217, 523, 1760, 2349, 1318, 1864, 2637, 2489, 1760, 1567
  };

  public:int duration[41] = {
    17, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 17, 9, 17, 9, 9, 9, 9, 17, 35, 26, 9, 9, 9, 9, 9, 9, 9, 9
  };

  public:int delay[41] = {
    19, 10, 10, 10, 59, 10, 10, 156, 10, 98, 10, 49, 10, 20, 10, 10, 29, 20, 20, 10, 10, 10, 117, 19, 39, 19, 10, 10, 10, 10, 49, 49, 29, 10, 10, 10, 10, 10, 68, 10, 10
  };
};

class Offer {
  public:int notes[32] = {
    174, 554, 184, 195, 207, 233, 293, 233, 369, 440, 493, 554, 622, 698, 783, 1396, 1174, 1318, 1661, 1760, 2093, 2349, 2637, 2793, 2959, 3135, 1975, 1174, 554, 2217, 659, 783
  };

  public:int duration[32] = {
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 17, 9, 9, 9, 9, 35, 9, 9, 9
  };

  public:int delay[32] = {
    10, 10, 10, 10, 10, 20, 10, 10, 10, 20, 10, 10, 10, 20, 10, 10, 10, 10, 10, 10, 10, 10, 10, 19, 10, 380, 20, 90, 39, 10, 10, 10
  };
};

class Broken {
  public:int notes[23] = {
     1174, 1760, 987, 1661, 2793, 554, 587, 523, 2637, 2793, 1108, 523, 783, 493, 783, 1108, 1174, 493, 523, 207, 1046, 1108, 220 
  };

  public:int duration[23] = {
    9, 9, 9, 17, 17, 9, 9, 26, 9, 148, 9, 9, 9, 17, 9, 26, 26, 26, 26, 17, 17, 61, 9
  };

  public:int delay[23] = {
    10, 10, 10, 19, 19, 49, 89, 29, 10, 204, 10, 10, 49, 19, 10, 107, 39, 29, 87, 19, 19, 68, 10
  };
};


class Robot {
  Cry cry = Cry();
  R2D2Question question = R2D2Question();
  Surprise surprise = Surprise();
  QuoteThree quote = QuoteThree();
  Offer offer = Offer();
  Broken broken = Broken();
  
  public:void crying() {
    for (int i = 0; i < 58; i++) {  
      tone(tonePin, cry.notes[i], cry.duration[i]);
      delay(cry.delay[i]);
    };
   
    noTone(tonePin);
  }

  public:void r2d2QuestionSong1() {
    for (int i = 0; i < 34; i++) {  
      tone(tonePin, question.notes[i], question.duration[i]);
      delay(question.delay[i]);
    }
  }

  public:void surpriceEl() {
    for (int i = 0; i < 32; i++) {  
      tone(tonePin, surprise.notes[i], surprise.duration[i]);
      delay(surprise.delay[i]);
    }
  }

  public:void quoteTwo() {
    for (int i = 0; i < 41; i++) {  
      tone(tonePin, quote.notes[i], quote.duration[i]);
      delay(quote.delay[i]);
    }
  }

  public:void offerSong() {
    for (int i = 0; i < 23; i++) {  
      tone(tonePin, offer.notes[i], offer.duration[i]);
      delay(offer.delay[i]);
    }
  }

  public:void brokenSong() { 
    for (int i = 0; i < 23; i++) {  
      tone(tonePin, broken.notes[i], broken.duration[i]);
      delay(broken.delay[i]);
    }
  }
};


 
Robot createRobot() {
  Robot rob = Robot();
  return rob;
}


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

    if (incomingbyte == 'd') {
      createRobot().crying();
    }

    if (incomingbyte == 'e') {
      createRobot().r2d2QuestionSong1();
    }

    if (incomingbyte == 'f') {
      createRobot().surpriceEl();
    }

    if (incomingbyte == 'g') {
      createRobot().quoteTwo();
    }

    if (incomingbyte == 'h') {
      createRobot().offerSong();
    }

    if (incomingbyte == 'i') {
      createRobot().brokenSong();
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