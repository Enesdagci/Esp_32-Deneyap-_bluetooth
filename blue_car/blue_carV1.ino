#include "BluetoothSerial.h"

// Motor pin definitions
// Front Left Motor
#define F_IN1 D1
#define F_IN2 D2
#define F_ENA D15

// Front Right Motor
#define F_IN3 D5
#define F_IN4 D6
#define F_ENB D7

// Back Right Motor
#define B_IN1 D10
#define B_IN2 D9
#define B_ENA D11

// Back Left Motor
#define B_IN3 D14  // Added missing pin
#define B_IN4 D13  
#define B_ENB D12  

// Led Pins
// Stop(Red) Led Pins
#define Led_Red D0

// Right(Orange) Led Pin d3
// Left(Orange) Led Pin d4
// Light(White) Led Pin d8

// Ldr Pins A0 

// Buzzer Pin
#define Buzzer D8

// Bluetooth setup
BluetoothSerial SerialBT;

// Motor speed (0-255)
int motorSpeed = 200;

void setup() {
  // Initialize serial communication
  
  // Initialize Bluetooth
  SerialBT.begin("Lamis_car"); // Bluetooth device name

  // Set all motor pins as outputs
  pinMode(F_IN1, OUTPUT);
  pinMode(F_IN2, OUTPUT);
  pinMode(F_ENA, OUTPUT);
  
  pinMode(F_IN3, OUTPUT);
  pinMode(F_IN4, OUTPUT);
  pinMode(F_ENB, OUTPUT);
  
  pinMode(B_IN1, OUTPUT);
  pinMode(B_IN2, OUTPUT);
  pinMode(B_ENA, OUTPUT);
  
  pinMode(B_IN3, OUTPUT);
  pinMode(B_IN4, OUTPUT);
  pinMode(B_ENB, OUTPUT);

  // Set all led pins 
  pinMode(Led_Red, OUTPUT);

  // Set Buzzer pin
  pinMode(Buzzer, OUTPUT);
  
  // Stop all motors initially
  stopMotors();
  
  // Motor stops initially
  digitalWrite(F_IN1, LOW);
  digitalWrite(F_IN2, LOW);
  digitalWrite(F_IN3, LOW);
  digitalWrite(F_IN4, LOW);

  digitalWrite(B_IN1, LOW);
  digitalWrite(B_IN2, LOW);
  digitalWrite(B_IN3, LOW);
  digitalWrite(B_IN4, LOW);
  
  // Led offs initially
  digitalWrite(Led_Red, LOW);

  tone(Buzzer, 0);
}

void loop() {
  // Check for Bluetooth commands
  if (SerialBT.available()) {
    char command = SerialBT.read();
    // Execute movement based on command
    switch (command) {
      case 'F':
        moveForward();
        break;
      case 'B':
        moveBackward();
        break;
      case 'R':
        turnLeft();
        break;
      case 'L':
        turnRight();
        break;
      case '0':
        stopMotors();
        tone(Buzzer, 0);
        break;
      case 'X':
        honk();
        break;
      case 'T':
        break;
      case 'C':
        ledOff();
        break;
      case 'S':
        ledOn();
        break;
    }
  }
}

void moveBackward() {
  // Front Left Motor - Front
  digitalWrite(F_IN1, LOW);
  digitalWrite(F_IN2, HIGH);
  analogWrite(F_ENA, motorSpeed);  

  // Front Right Motor - Front
  digitalWrite(F_IN3, LOW);
  digitalWrite(F_IN4, HIGH);
  analogWrite(F_ENB, motorSpeed);  

  // Back Left Motor - Backward
  digitalWrite(B_IN1, LOW);
  digitalWrite(B_IN2, HIGH);
  analogWrite(B_ENA, motorSpeed);
  
  // Back Right Motor - Backward
  digitalWrite(B_IN3, LOW);
  digitalWrite(B_IN4, HIGH);
  analogWrite(B_ENB, motorSpeed);
  
  digitalWrite(Led_Red, LOW);
  
}

// Movement functions
void moveForward() {
  // Front Left Motor - Forward
  digitalWrite(F_IN1, HIGH);
  digitalWrite(F_IN2, LOW);
  analogWrite(F_ENA, motorSpeed);
  
  // Front Right Motor - Forward
  digitalWrite(F_IN3, HIGH);
  digitalWrite(F_IN4, LOW);
  analogWrite(F_ENB, motorSpeed);
  
  // Back Left Motor - Forward
  digitalWrite(B_IN1, HIGH);
  digitalWrite(B_IN2, LOW);
  analogWrite(B_ENA, motorSpeed);
  
  // Back Right Motor - Forward
  digitalWrite(B_IN3, HIGH);
  digitalWrite(B_IN4, LOW);
  analogWrite(B_ENB, motorSpeed);
  
  digitalWrite(Led_Red, LOW);
  
}

void turnRight() {
  // Left motors backward, right motors forward
  // Front Left Motor - Backward
  digitalWrite(F_IN1, LOW);
  digitalWrite(F_IN2, HIGH);
  analogWrite(F_ENA, motorSpeed);
  
  // Front Right Motor - Forward
  digitalWrite(F_IN3, HIGH);
  digitalWrite(F_IN4, LOW);
  analogWrite(F_ENB, motorSpeed);
  
  // Back Left Motor - Backward
  digitalWrite(B_IN1, HIGH);
  digitalWrite(B_IN2, LOW);
  analogWrite(B_ENA, motorSpeed);
  
  // Back Right Motor - Forward
  digitalWrite(B_IN3, LOW);
  digitalWrite(B_IN4, HIGH);
  analogWrite(B_ENB, motorSpeed);

  digitalWrite(Led_Red, LOW);   
}

void turnLeft() {
  // Left motors forward, right motors backward
  // Front Left Motor - Forward
  digitalWrite(F_IN1, HIGH);
  digitalWrite(F_IN2, LOW);
  analogWrite(F_ENA, motorSpeed);
  
  // Front Right Motor - Backward
  digitalWrite(F_IN3, LOW);
  digitalWrite(F_IN4, HIGH);
  analogWrite(F_ENB, motorSpeed);
  
  // Back Left Motor - Forward
  digitalWrite(B_IN1, LOW);
  digitalWrite(B_IN2, HIGH);
  analogWrite(B_ENA, motorSpeed);
  
  // Back Right Motor - Backward
  digitalWrite(B_IN3, HIGH);
  digitalWrite(B_IN4, LOW);
  analogWrite(B_ENB, motorSpeed);  

  digitalWrite(Led_Red, LOW);
  
}

void stopMotors() {
  // Stop all motors
  analogWrite(F_ENA, 0);
  analogWrite(F_ENB, 0);
  analogWrite(B_ENA, 0);
  analogWrite(B_ENB, 0);

  digitalWrite(F_IN1, LOW);
  digitalWrite(F_IN2, LOW);
  digitalWrite(F_IN3, LOW);
  digitalWrite(F_IN4, LOW);

  digitalWrite(B_IN1, LOW);
  digitalWrite(B_IN2, LOW);
  digitalWrite(B_IN3, LOW);
  digitalWrite(B_IN4, LOW);

  digitalWrite(Led_Red, HIGH);
  
}

void ledOn(){
  // şeffaflar açılacak 
}

void ledOff(){
  // Bütün ledler kapanacak

}

void honk(){
  tone(Buzzer, 660); delay(100);
  noTone(Buzzer); delay(50);
  tone(Buzzer, 660); delay(100);
  noTone(Buzzer); delay(50);
  tone(Buzzer, 660); delay(100);
  noTone(Buzzer); delay(50);
  tone(Buzzer, 510); delay(100);
  noTone(Buzzer); delay(50);
  tone(Buzzer, 660); delay(100);
  noTone(Buzzer); delay(50);
  tone(Buzzer, 770); delay(100);
  noTone(Buzzer); delay(50);
  tone(Buzzer, 380); delay(100);
  noTone(Buzzer); delay(300);

  tone(Buzzer, 510); delay(100);
  noTone(Buzzer); delay(100);
  tone(Buzzer, 380); delay(100);
  noTone(Buzzer); delay(100);
  tone(Buzzer, 320); delay(100);
  noTone(Buzzer); delay(300);

  tone(Buzzer, 440); delay(100);
  noTone(Buzzer); delay(50);
  tone(Buzzer, 480); delay(80);
  noTone(Buzzer); delay(50);
  tone(Buzzer, 450); delay(100);
  noTone(Buzzer); delay(50);
  tone(Buzzer, 430); delay(100);
  noTone(Buzzer); delay(50);
  tone(Buzzer, 380); delay(100);
  noTone(Buzzer); delay(50);
  tone(Buzzer, 660); delay(80);
  noTone(Buzzer); delay(80);
  tone(Buzzer, 760); delay(80);
  noTone(Buzzer); delay(80);
  tone(Buzzer, 860); delay(80);
  noTone(Buzzer); delay(100);
  tone(Buzzer, 700); delay(80);
  noTone(Buzzer); delay(50);
  tone(Buzzer, 760); delay(80);
  noTone(Buzzer); delay(50);
  tone(Buzzer, 660); delay(80);
  noTone(Buzzer); delay(100);
  tone(Buzzer, 520); delay(80);
  noTone(Buzzer); delay(50);
  tone(Buzzer, 580); delay(80);
  noTone(Buzzer); delay(50);
  tone(Buzzer, 480); delay(80);
  noTone(Buzzer); delay(100);

  // Durdur
  noTone(Buzzer);
}