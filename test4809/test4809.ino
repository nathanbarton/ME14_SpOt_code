 #include <avr/io.h>

#include <Wire.h>

#define BLINKPIN  11
#define BLINKPIN2 12
#define PERIOD    1000

#define PIN_PHASE 4
#define PIN_ENBL  9
#define PIN_DECAY 8
#define PIN_nRESET 7
#define PIN_I4    A0
#define PIN_I3    A1
#define PIN_I2    A2
#define PIN_I1    A3
#define PIN_I0    A4

int count = 0;

void setup() {
  // put your setup code here, to run once:
  
  pinMode(BLINKPIN, OUTPUT);
  pinMode(BLINKPIN2, OUTPUT);
  Serial1.begin(9600);

  pinMode(PIN_PHASE, OUTPUT);
  pinMode(PIN_ENBL, OUTPUT);
  pinMode(PIN_DECAY, OUTPUT);
  pinMode(PIN_nRESET, OUTPUT);
  pinMode(PIN_I4, OUTPUT);
  pinMode(PIN_I3, OUTPUT);
  pinMode(PIN_I2, OUTPUT);
  pinMode(PIN_I1, OUTPUT);
  pinMode(PIN_I0, OUTPUT);

  digitalWrite(PIN_PHASE, HIGH);
  digitalWrite(PIN_ENBL, HIGH);
  digitalWrite(PIN_DECAY, LOW);
  digitalWrite(PIN_nRESET, HIGH);

  digitalWrite(PIN_I0, HIGH);
  
  //Wire.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial1.println(count);
  count++;
  digitalWrite(BLINKPIN,HIGH);
  digitalWrite(BLINKPIN2,LOW);
  digitalWrite(PIN_PHASE, LOW);
  delay(PERIOD);
  digitalWrite(BLINKPIN,LOW);
  digitalWrite(BLINKPIN2,HIGH);
  digitalWrite(PIN_PHASE, HIGH);
  delay(PERIOD);

  
}
