#include "BluetoothSerial.h"
BluetoothSerial Serial_BT;

// Motor 1
// D0 - PWM, D1 - IN1, D2 - IN2
#define ENA D0
#define IN1 D1
#define IN2 D2
int data;

void setup() {
  // motor pinlerini ayarlanması
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  // digitalWrite(D0, HIGH);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  Serial_BT.begin("Hamal");

void loop() {
  if (Serial_BT.available()) {
    data = Serial_BT.read();
    switch (data) {
      case 'F':
        digitalWrite(IN2, HIGH);
        digitalWrite(IN1, LOW);
        break;
      case 'B':
        digitalWrite(IN2, LOW);
        digitalWrite(IN1, HIGH);
        break;
      default:
        digitalWrite(IN2, LOW);
        digitalWrite(IN1, LOW);
        break;
    }
  }
}
