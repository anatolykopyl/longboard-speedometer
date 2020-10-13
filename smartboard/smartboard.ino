#include "Timer.h"

#define DOUBLE_TRIGGER false
#define MODEL "nano"

Timer t;

int D1, D2, D3, D4;
int A, B, C, D, E, F, G, DOT;
int SENS = 10;

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

  if (digit == D3) {
    digitalWrite(DOT, LOW);
  } else {
    digitalWrite(DOT, HIGH);
  }

  switch (c) {
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
  if (MODEL == "pro micro") {
    D1 = 2;
    D2 = 5;
    D3 = 6;
    D4 = 12;
  
    A = 3;
    B = 7;
    C = 14;
    D = 16;
    E = 17;
    F = 4;
    G = 13;
    DOT = 15;
  
    SENS = 10;
  } else if (MODEL == "nano") {
    D1 = 4;
    D2 = 7;
    D3 = 8;
    D4 = 14;
  
    A = 5;
    B = 9;
    C = 16;
    D = 18;
    E = 19;
    F = 6;
    G = 15;
    DOT = 17;
  
    SENS = 12;
  }
  
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

  draw_char(speedKMH / 1000 % 10 + '0', D1);
  draw_char(speedKMH / 100 % 10 + '0', D2);
  draw_char(speedKMH / 10 % 10 + '0', D3);
  draw_char(speedKMH % 10 + '0', D4);
}

void update_speed() {
  /*
      Dividing by two because reed switch gets triggered twice a rotation
      You probably won't need that if you opt for a hall sensor
  */

  if (DOUBLE_TRIGGER) {
    dist = CIRCUMF * rotations / 2;
  } else {
    dist = CIRCUMF * rotations;
  }

  speedKMH = dist * 3.6 / (WAIT / 1000);

  rotations = 0;
}
