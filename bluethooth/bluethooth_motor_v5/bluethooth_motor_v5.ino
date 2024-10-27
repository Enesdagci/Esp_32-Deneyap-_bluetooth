#include "BluetoothSerial.h"
BluetoothSerial Serial_BT;

//Motor - 1
#define PWM_1 D0
#define LPWM_1 D1
#define RPWM_1 D2

// Motor - 2
#define PWM_2 D3
#define LPWM_2 D4
#define RPWM_2 D5

// Motor - 3
#define PWM_3 D6
#define LPWM_3 D7
#define RPWM_3 D8

// Motor - 4
#define PWM_4 D9
#define LPWM_4 D10
#define RPWM_4 D11

int data;
void setup() {
  // Motor - 1
  pinMode(PWM_1, OUTPUT);
  pinMode(LPWM_1, OUTPUT);
  pinMode(RPWM_1, OUTPUT);

  digitalWrite(PWM_1, HIGH);
  digitalWrite(LPWM_1, LOW);
  digitalWrite(RPWM_1, LOW);

  // MOTOR - 2
  pinMode(PWM_2, OUTPUT);
  pinMode(LPWM_2, OUTPUT);
  pinMode(RPWM_2, OUTPUT);

  digitalWrite(PWM_2, HIGH);
  digitalWrite(LPWM_2, LOW);
  digitalWrite(RPWM_2, LOW);

  // Motor - 3
  pinMode(PWM_3, OUTPUT);
  pinMode(LPWM_3, OUTPUT);
  pinMode(RPWM_3, OUTPUT);

  digitalWrite(PWM_3, HIGH);
  digitalWrite(LPWM_3, LOW);
  digitalWrite(RPWM_3, LOW);

  // Motor - 4
  pinMode(PWM_4, OUTPUT);
  pinMode(LPWM_4, OUTPUT);
  pinMode(RPWM_4, OUTPUT);

  digitalWrite(PWM_4, HIGH);
  digitalWrite(LPWM_4, LOW);
  digitalWrite(RPWM_4, LOW);

  Serial_BT.begin("Hamal");
}

void loop() {

  // Bluetooth bağlantısının kontrolü
  if (Serial_BT.available()) {
    // Bluetooth dan gelen verinin okunması
    data = Serial_BT.read();

    // İleri yönlü
    if (data == 'F') {
      // MOTOR - 1
      digitalWrite(PWM_1, HIGH);
      digitalWrite(LPWM_1, LOW);
      digitalWrite(RPWM_1, HIGH);

      // MOTOR - 2
      digitalWrite(PWM_2, HIGH);
      digitalWrite(LPWM_2, LOW);
      digitalWrite(RPWM_2, HIGH);

      // MOTOR - 3
      digitalWrite(PWM_3, HIGH);
      digitalWrite(LPWM_3, HIGH);
      digitalWrite(RPWM_3, LOW);

      // MOTOR - 4
      digitalWrite(PWM_4, HIGH);
      digitalWrite(LPWM_4, HIGH);
      digitalWrite(RPWM_4, LOW);
    }
    // Geri yönlü
    if (data == 'B') {
      // MOTOR - 1
      digitalWrite(PWM_1, HIGH);
      digitalWrite(LPWM_1, HIGH);
      digitalWrite(RPWM_1, LOW);

      // MOTOR - 2
      digitalWrite(PWM_2, HIGH);
      digitalWrite(LPWM_2, HIGH);
      digitalWrite(RPWM_2, LOW);

      // MOTOR - 3
      digitalWrite(PWM_3, HIGH);
      digitalWrite(LPWM_3, LOW);
      digitalWrite(RPWM_3, HIGH);

      // MOTOR - 4
      digitalWrite(PWM_4, HIGH);
      digitalWrite(LPWM_4, LOW);
      digitalWrite(RPWM_4, HIGH);
    }

    // Sola dönme
    if (data == 'L'){
      // MOTOR - 1
      digitalWrite(PWM_1, HIGH);
      digitalWrite(LPWM_1, HIGH);
      digitalWrite(RPWM_1, LOW);

      // MOTOR - 2
      digitalWrite(PWM_2, HIGH);
      digitalWrite(LPWM_2, LOW);
      digitalWrite(RPWM_2, HIGH);

      // MOTOR - 3
      digitalWrite(PWM_3, HIGH);
      digitalWrite(LPWM_3, LOW);
      digitalWrite(RPWM_3, HIGH);

      // MOTOR - 4
      digitalWrite(PWM_4, HIGH);
      digitalWrite(LPWM_4, HIGH);
      digitalWrite(RPWM_4, LOW);
    }

    // Sağa dönme
    if (data == 'R'){
      // MOTOR - 1
      digitalWrite(PWM_1, HIGH);
      digitalWrite(LPWM_1, LOW);
      digitalWrite(RPWM_1, HIGH);

      // MOTOR - 2
      digitalWrite(PWM_2, HIGH);
      digitalWrite(LPWM_2, HIGH);
      digitalWrite(RPWM_2, LOW);

      // MOTOR - 3
      digitalWrite(PWM_3, HIGH);
      digitalWrite(LPWM_3, HIGH);
      digitalWrite(RPWM_3, LOW);

      // MOTOR - 4
      digitalWrite(PWM_4, HIGH);
      digitalWrite(LPWM_4, LOW);
      digitalWrite(RPWM_4, HIGH);
    }
    // Sağa gitme
    if (data == 'S'){
      // MOTOR - 1
      digitalWrite(PWM_1, HIGH);
      digitalWrite(LPWM_1, LOW);
      digitalWrite(RPWM_1, HIGH);

      // MOTOR - 2 
      digitalWrite(PWM_2, HIGH);
      digitalWrite(LPWM_2, LOW);
      digitalWrite(RPWM_2, HIGH);

      // MOTOR - 3
      digitalWrite(PWM_3, HIGH);
      digitalWrite(LPWM_3, HIGH);
      digitalWrite(RPWM_3, LOW);

      // MOTOR - 4 
      digitalWrite(PWM_4, HIGH);
      digitalWrite(LPWM_4, HIGH);
      digitalWrite(RPWM_4, LOW);
    }
    
    // Sola gitme
    if (data == 'C'){
      // MOTOR - 1
      digitalWrite(PWM_1, HIGH);
      digitalWrite(LPWM_1, HIGH);
      digitalWrite(RPWM_1, LOW);

      // MOTOR - 2
      digitalWrite(PWM_2, HIGH);
      digitalWrite(LPWM_2, HIGH);
      digitalWrite(RPWM_2, LOW);

      // MOTOR - 3
      digitalWrite(PWM_3, HIGH);
      digitalWrite(LPWM_3, LOW);
      digitalWrite(RPWM_3, HIGH);

      // MOTOR - 4
      digitalWrite(PWM_4, HIGH);
      digitalWrite(LPWM_4, LOW);
      digitalWrite(RPWM_4, HIGH);
    }

    // Durdurma
    if (data == '0') {
      // MOTOR - 1
      digitalWrite(PWM_1, HIGH);
      digitalWrite(LPWM_1, LOW);
      digitalWrite(RPWM_1, LOW);

      // MOTOR - 2
      digitalWrite(PWM_2, HIGH);
      digitalWrite(LPWM_2, LOW);
      digitalWrite(RPWM_2, LOW);

      // MOTOR - 3
      digitalWrite(PWM_3, HIGH);
      digitalWrite(LPWM_3, LOW);
      digitalWrite(RPWM_3, LOW);

      // MOTOR - 4
      digitalWrite(PWM_4, HIGH);
      digitalWrite(LPWM_4, LOW);
      digitalWrite(RPWM_4, LOW);
    }
  }
}
