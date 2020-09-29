#include "Timer.h"
Timer t;

//Pinout for a pro micro, check schematic
/*
int D1 = 2;
int D2 = 5;
int D3 = 6;
int D4 = 12;

int A = 3;
int B = 7;
int C = 14;
int D = 16;
int E = 17;
int F = 4;
int G = 13;
int DOT = 15;

int SENS = 10;
*/

//Pinout for a nano
int D1 = 4;
int D2 = 7;
int D3 = 8;
int D4 = 14;

int A = 5;
int B = 9;
int C = 16;
int D = 18;
int E = 19;
int F = 6;
int G = 15;
int DOT = 17;

int SENS = 12;

double WAIT = 500; //Time between updates
double CIRCUMF = 3.14 * 7; //Circumference of your wheel
double dist = 0;
int speedKMH = 0;

bool got_signal = false;
int rotations = 0;

void draw_char(char c, int digit) {
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);
  digitalWrite(digit, HIGH);

  if (digit == D4) {
    digitalWrite(DOT, LOW);
  } else {
    digitalWrite(DOT, HIGH);
  }
  
  switch(c) {
    case '1':
      digitalWrite(A, HIGH);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      break;

    case '2':
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, HIGH);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, HIGH);
      digitalWrite(G, LOW);
      break;

    case '3':
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, LOW);
      break;

    case '4':
      digitalWrite(A, HIGH);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
      break;

    case '5':
      digitalWrite(A, LOW);
      digitalWrite(B, HIGH);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
      digitalWrite(E, HIGH);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
      break;

    case '6':
      digitalWrite(A, LOW);
      digitalWrite(B, HIGH);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
      break;

    case '7':
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      break;

    case '8':
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
      break;

    case '9':
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
      digitalWrite(E, HIGH);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
      break;

    case '0':
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, LOW);
      digitalWrite(G, HIGH);
      break;
  }
  delay(6);
}

void setup() {
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(DOT, OUTPUT);

  pinMode(SENS, INPUT_PULLUP);

  t.every(WAIT, update_speed);
}

void loop() {
  t.update();

  if (digitalRead(SENS) and !got_signal) {
    got_signal = true;
    rotations++;
  }

  if (!digitalRead(SENS)) {
    got_signal = false;
  }

  draw_char(speedKMH/1000%10 + '0', D1);
  draw_char(speedKMH/100%10 + '0', D2);
  draw_char(speedKMH/10%10 + '0', D3);
  draw_char(speedKMH%10 + '0', D4);
}

void update_speed() {
  /* 
   *  Dividing by two because reed switch gets triggered twice a rotation
   *  You probably won't need that if you opt for a hall sensor
   */
  dist = CIRCUMF * rotations / 2;
  speedKMH = dist * 3.6 / (WAIT / 1000);

  rotations = 0;
}
