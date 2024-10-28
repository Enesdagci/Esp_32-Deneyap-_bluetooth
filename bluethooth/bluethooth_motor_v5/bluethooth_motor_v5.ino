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
  // Pinlerin tanumlanması ve başlangıç için hazırlık
  // Motor - 1
  pin_outputs(PWM_1, LPWM_1, RPWM_1);
  movement_setup(PWM_1, LPWM_1, RPWM_1);

  // MOTOR - 2
  pin_outputs(PWM_2, LPWM_2, RPWM_2);
  movement_setup(PWM_2, LPWM_2, RPWM_2);

  // Motor - 3
  pin_outputs(PWM_3, LPWM_3, RPWM_3);
  movement_setup(PWM_3, LPWM_3, RPWM_3);

  // Motor - 4
  pin_outputs(PWM_4, LPWM_4, RPWM_4);
  movement_setup(PWM_4, LPWM_4, RPWM_4);

  Serial_BT.begin("Hamal");
}

// Hareket Fonksiyonları

void moveForward() {
  // MOTOR - 1
  movement_cw(PWM_1, LPWM_1, RPWM_1);

  // MOTOR - 2
  movement_cw(PWM_2, LPWM_2, RPWM_2);

  // MOTOR - 3
  movement_ccw(PWM_3, LPWM_3, RPWM_3);

  // MOTOR - 4
  movement_ccw(PWM_4, LPWM_4, RPWM_4);
}

void moveBackward() {
  // MOTOR - 1
  movement_ccw(PWM_1, LPWM_1, RPWM_1);

  // MOTOR - 2
  movement_ccw(PWM_2, LPWM_2, RPWM_2);

  // MOTOR - 3
  movement_cw(PWM_3, LPWM_3, RPWM_3);

  // MOTOR - 4
  movement_cw(PWM_4, LPWM_4, RPWM_4);
}

void moveRight() {
  // MOTOR - 1
  movement_ccw(PWM_1, LPWM_1, RPWM_1);

  // MOTOR - 2
  movement_cw(PWM_2, LPWM_2, RPWM_2);

  // MOTOR - 3
  movement_ccw(PWM_3, LPWM_3, RPWM_3);

  // MOTOR - 4
  movement_cw(PWM_4, LPWM_4, RPWM_4);
}

void moveLeft() {
  // MOTOR - 1
  movement_cw(PWM_1, LPWM_1, RPWM_1);

  // MOTOR - 2
  movement_ccw(PWM_2, LPWM_2, RPWM_2);

  // MOTOR - 3
  movement_cw(PWM_3, LPWM_3, RPWM_3);

  // MOTOR - 4
  movement_ccw(PWM_4, LPWM_4, RPWM_4);
}

void spinRight() {
  // MOTOR - 1
  movement_cw(PWM_1, LPWM_1, RPWM_1);

  // MOTOR - 2
  movement_ccw(PWM_2, LPWM_2, RPWM_2);

  // MOTOR - 3
  movement_ccw(PWM_3, LPWM_3, RPWM_3);

  // MOTOR - 4
  movement_cw(PWM_4, LPWM_4, RPWM_4);
}

void spinLeft() {
  // MOTOR - 1
  movement_ccw(PWM_1, LPWM_1, RPWM_1);

  // MOTOR - 2
  movement_cw(PWM_2, LPWM_2, RPWM_2);

  // MOTOR - 3
  movement_cw(PWM_3, LPWM_3, RPWM_3);

  // MOTOR - 4
  movement_ccw(PWM_4, LPWM_4, LPWM_4);
}

void stopMotor() {
  // MOTOR - 1
  movement_stop(PWM_1, LPWM_1, LPWM_1);

  // MOTOR - 2
  movement_stop(PWM_2, LPWM_2, LPWM_2);

  // MOTOR - 3
  movement_stop(PWM_3, LPWM_3, RPWM_3);

  // MOTOR - 4
  movement_stop(PWM_4, LPWM_4, RPWM_4);
}

void dance_1() {
  moveLeft();
  delay(1000);
  moveRight();
  delay(2000);
  moveLeft();
  delay(1000);
  moveForward();
  delay(1000);
  moveBackward();
  delay(2000);
  moveForward();
  delay(1000);
}

void dance_2() {
  spinRight();
  delay(500);
  spinLeft();
  delay(1000);
  spinRight();
  delay(500);
  moveForward();
  delay(1000);
  moveBackward();
  delay(1000);
}

// Kumandadan kontrol noktası.
void loop() {

  // Bluetooth bağlantısının kontrolü.
  if (Serial_BT.available()) {
    
  // Bluetooth dan gelen verinin okunması.
    data = Serial_BT.read();
    switch (data) {
        // İleri Gitme
      case 'F':
        moveForward();
        break;

        // Geri Gitme
      case 'B':
        moveBackward();
        break;

        // Sağa Dönme
      case 'R':
        spinRight();
        break;

        // Sola Dönme
      case 'L':
        spinLeft();
        break;

        // Sağa Gitme
      case 'C':
        moveRight();
        break;

        // Sola Gitme
      case 'S':
        moveLeft();
        break;

        // Dance - 1
      case 'X':
        dance_1();
        break;

        // Dance - 2
      case 'T':
        dance_2();
        break;

        // Stop
      default:
        stopMotor();
        break;
    }
  }
}
// Pinler için hazırlanan fonksiyon ve dönme yönlerini ayarlamayı sağlayan fonksiyonlar.
void pin_outputs(int pwm, int lpwm, int rpwm) {
  pinMode(pwm, OUTPUT);
  pinMode(lpwm, OUTPUT);
  pinMode(rpwm, OUTPUT);
}

void movement_setup(int pwm, int lpwm, int rpwm) {
  digitalWrite(pwm, HIGH);
  digitalWrite(lpwm, LOW);
  digitalWrite(rpwm, LOW);
}

void movement_stop(int pwm, int lpwm, int rpwm) {
  digitalWrite(pwm, LOW);
  digitalWrite(lpwm, LOW);
  digitalWrite(rpwm, LOW);
}

void movement_cw(int pwm, int lpwm, int rpwm) {
  digitalWrite(pwm, HIGH);
  digitalWrite(lpwm, LOW);
  digitalWrite(rpwm, HIGH);
}

void movement_ccw(int pwm, int lpwm, int rpwm) {
  digitalWrite(pwm, HIGH);
  digitalWrite(lpwm, HIGH);
  digitalWrite(rpwm, LOW);
}  
