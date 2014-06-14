#include "pitches.h"


int correctnotes[] = {NOTE_C5, NOTE_E5, NOTE_G5, NOTE_E5, NOTE_G5, NOTE_C6, NOTE_G5, NOTE_C6, NOTE_E6, NOTE_C6, NOTE_E6, NOTE_G6, NOTE_E6, NOTE_G6, NOTE_C7, };
int incorrectnotes[] = {NOTE_C3, NOTE_FS2};
int incorrectnoteslength[] = {2.2, 2};


int firsttime = 1;
int threshold = 1005;
int btn = -1;

//Digital pins
int ledlose = 8;
int ledwin = 7;

int button1 = 9;
int button2 = 10;
int button3 = 11;
int button4 = 12;
int button5 = 13;

int speaker = 6;

//Analog pins
int sensor1 = A3;
int sensor2 = A2;
int sensor3 = A1;


void setup() {
  playsound2();
  Serial.begin(9600);  
  pinMode(ledlose, OUTPUT); 
  pinMode(ledwin, OUTPUT);

  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);

  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);
  pinMode(button5, INPUT);
  
  pinMode(speaker, OUTPUT);
}

void playsound0() { //lose sound
  
  for (int thisNote = 0; thisNote < 2; thisNote++) {
    // to calculate the note duration, take one second 
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000/incorrectnoteslength[thisNote];
    tone(speaker, incorrectnotes[thisNote],noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(speaker);
  }
}


void playsound1() { //win sound
  
  for (int thisNote = 0; thisNote < (sizeof(correctnotes)/sizeof(*correctnotes)); thisNote++) {
    tone(speaker, correctnotes[thisNote], 40);
    delay(40);
    noTone(speaker);
  }
}

void playsound2() { //startup sound
  int upper = 1000;
  int lower = 30;
  for (int i = lower; i <  upper; i+=2) {
    tone(speaker, i, 10);
    delay(1);
  }
  for (int i = upper; i > lower; i-=2) {
    tone(speaker, i, 10);
    delay(1);
  }
}


void playsound3() { //showoff sound
  int q = 0;
  int length = 75;
  int btn = 0;
  while (btn != 14) { 
    int rlo = random(200,1000);
    int rhi = random(1250,2000);

    tone(speaker, rlo, length);
    delay(length * 1.00);
    tone(speaker, rhi, length);
    delay(length * 1.00);
    
    btn = readbuttons();
  }
}


void pulseleds() {
  digitalWrite(ledwin, HIGH);
  digitalWrite(ledlose, LOW);
  delay(50);
  digitalWrite(ledlose, HIGH);
  digitalWrite(ledwin, LOW);
  delay(50);  
}


int readbuttons() {
  int btn1 = digitalRead(button1);
  int btn2 = digitalRead(button2);
  int btn3 = digitalRead(button3);
  int btn4 = digitalRead(button4);
  int btn5 = digitalRead(button5);
  int btn = 0;
  if (btn1 == 1) {btn = btn + 1;} 
  if (btn2 == 1) {btn = btn + 2;} 
  if (btn3 == 1) {btn = btn + 4;} 
  if (btn4 == 1) {btn = btn + 8;} 
  if (btn5 == 1) {btn = btn + 16;}

  return btn; 
}

int readsensors() {
  int svalue1 = analogRead(sensor1);
  int svalue2 = analogRead(sensor2);
  int svalue3 = analogRead(sensor3);

  int answer = 0;
  if (svalue1 < threshold) {answer += 1;}
  if (svalue2 < threshold) {answer += 2;}
  if (svalue3 < threshold) {answer += 4;}
  
  return answer;  
}


void keyboard() { //turns device into a keyboard if outside four buttons are pressed 
  delay(200);
  int length = 10;
  int btn = 0;
  int sensor = 0;
  int octave = 1;

  while (btn != 14) {
    btn = readbuttons();
    sensor = readsensors();
    octave = 1;
    if (sensor == 4 || sensor == 5) {octave = 1;} 
    if (sensor == 7) {octave = 2;}  
    if (sensor == 3) {octave = 4;}  
        
    switch (btn) {
      case 0:
        noTone(speaker);
        digitalWrite(ledwin, LOW);
        digitalWrite(ledlose, LOW);
        break;
      case 1:
        tone(speaker, 146 * octave);
        digitalWrite(ledwin, HIGH);
        digitalWrite(ledlose, HIGH);
        break;
      case 2:
        tone(speaker, 174 * octave);
        digitalWrite(ledwin, HIGH);
        digitalWrite(ledlose, HIGH);
        break;
      case 4:
        tone(speaker, 196 * octave);
        digitalWrite(ledwin, HIGH);
        digitalWrite(ledlose, HIGH);
        break;
      case 8:
        tone(speaker, 220 * octave);
        digitalWrite(ledwin, HIGH);
        digitalWrite(ledlose, HIGH);
        break;
      case 16:
        tone(speaker, 262 * octave);
        digitalWrite(ledwin, HIGH);
        digitalWrite(ledlose, HIGH);
        break;
    }  
  }
}


void pitchbend() { //bends pitch based on user input
  delay(200);
  
  int startfreq = 440;
  int inc = 0;
  int upper = 2000;
  int lower = 100;
  int btn = 0;
  
  while (btn != 14) {
    btn = readbuttons();
    
    if (btn == 0) {
      noTone(speaker);
    } else {
      if (btn == 5) {inc += -1; delay(2);}
      if (btn == 6) {inc += -1; delay(10);}
      if (btn == 12) {inc += 1; delay(10);}
      if (btn == 20) {inc += 1; delay(2);}
      if (startfreq + inc > upper) {inc = upper - startfreq;}
      if (startfreq + inc < lower) {inc = -1 * (startfreq - lower);}
      
      if (btn == 5 || btn == 6 || btn == 4 || btn == 12 || btn == 20) {tone(speaker, startfreq + inc);}
      if (btn == 17) {inc = 0; delay(200);}
    }
  } 
}



















void loop() {
  noTone(speaker);
  if (firsttime == 1) {
    firsttime = 0;
    digitalWrite(ledwin, LOW);
    digitalWrite(ledlose, LOW);
  }
  
  int btn1 = digitalRead(button1);
  int btn2 = digitalRead(button2);
  int btn3 = digitalRead(button3);
  int btn4 = digitalRead(button4);
  int btn5 = digitalRead(button5);
  if (btn1 == HIGH) {btn = 1;} else 
  if (btn2 == HIGH) {btn = 2;} else 
  if (btn3 == HIGH) {btn = 3;} else 
  if (btn4 == HIGH) {btn = 4;} else 
  if (btn5 == HIGH) {btn = 5;} else
  {btn = -1;}
  
  if (btn1 == HIGH && btn2 == HIGH && btn3 == HIGH && btn4 == HIGH && btn5 == HIGH) {playsound3();}
  if (btn1 == HIGH && btn2 == HIGH && btn3 == LOW && btn4 == HIGH && btn5 == HIGH) {keyboard();}
  if (btn1 == HIGH && btn2 == LOW && btn3 == LOW && btn4 == LOW && btn5 == HIGH) {pitchbend();}

  int svalue1 = analogRead(sensor1);
  int svalue2 = analogRead(sensor2);
  int svalue3 = analogRead(sensor3);

  int answer = 0;
  if (svalue1 < threshold) {answer += 1;}
  if (svalue2 < threshold) {answer += 2;}
  if (svalue3 < threshold) {answer += 4;}
  if (answer == 7) {pulseleds();}

  digitalWrite(ledwin, LOW);
  digitalWrite(ledlose, LOW);
  if (btn == answer) {
    digitalWrite(ledwin, HIGH);
    playsound1();
  } 
  
  if (btn != answer && btn != -1 && answer != 7) {
    digitalWrite(ledlose, HIGH);
    playsound0();
  }  
  if (btn == -1) {digitalWrite(ledwin, LOW); digitalWrite(ledlose, LOW);}  


  Serial.print(svalue1);
  Serial.print("\t");
  Serial.print(svalue2);
  Serial.print("\t");
  Serial.print(svalue3);
  Serial.print("\t");
  Serial.print(answer);
  Serial.print("\t");
  Serial.print(btn);
  Serial.print("\t");
  Serial.println(""); 
}
