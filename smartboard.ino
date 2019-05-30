#include "Timer.h"
Timer t;

//Pinout for a pro micro, check schematic
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

int WAIT = 500; //Time between updates
double CIRCUMF = 3.14 * 7; //Circumference of your wheel
int dist = 0;
int speedKMH = 0;

bool got_signal = false;
int rotations = 0;

void draw_char(char c, int digit) {
  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH);
  digitalWrite(digit, LOW);

  if (digit == D4) {
    digitalWrite(DOT, HIGH);
  } else {
    digitalWrite(DOT, LOW);
  }
  
  switch(c) {
    case '1':
      digitalWrite(A, LOW);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
      break;

    case '2':
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, LOW);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, LOW);
      digitalWrite(G, HIGH);
      break;

    case '3':
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, LOW);
      digitalWrite(F, LOW);
      digitalWrite(G, HIGH);
      break;

    case '4':
      digitalWrite(A, LOW);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      break;

    case '5':
      digitalWrite(A, HIGH);
      digitalWrite(B, LOW);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, LOW);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      break;

    case '6':
      digitalWrite(A, HIGH);
      digitalWrite(B, LOW);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      break;

    case '7':
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
      break;

    case '8':
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      break;

    case '9':
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, LOW);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      break;

    case '0':
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, LOW);
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
  if (rotations > 1) {
    dist = CIRCUMF * rotations / 2;
    speedKMH = dist * 3.6 / (WAIT / 1000);
  } else {
    speedKMH = 0;
  }

  got_signal = false;
  rotations = 0;
}
