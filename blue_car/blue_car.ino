#include "BluetoothSerial.h"

// Motor pin definitions
// Front Left Motor
#define F_IN1 D13
#define F_IN2 D14
#define F_ENA D12

// Front Right Motor
#define F_IN3 D1
#define F_IN4 D2
#define F_ENB D0

// Back Left Motor
#define B_IN1 D5
#define B_IN2 D6
#define B_ENA D4

// Back Right Motor
#define B_IN3 D9  // Added missing pin
#define B_IN4 D10  
#define B_ENB D8  

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
  
  // Stop all motors initially
  stopMotors();
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
        break;
      case 'X':
        increaseSpeed();
        break;
      case 'T':
        decreaseSpeed();
        break;
    }
  }
}

// Movement functions
void moveBackward() {
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
  
}

void moveForward() {
  // Front Left Motor - Backward
  digitalWrite(F_IN1, LOW);
  digitalWrite(F_IN2, HIGH);
  analogWrite(F_ENA, motorSpeed);
  
  // Front Right Motor - Backward
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
  
}

void turnLeft() {
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
  digitalWrite(B_IN1, LOW);
  digitalWrite(B_IN2, HIGH);
  analogWrite(B_ENA, motorSpeed);
  
  // Back Right Motor - Forward
  digitalWrite(B_IN3, HIGH);
  digitalWrite(B_IN4, LOW);
  analogWrite(B_ENB, motorSpeed);
  
  Serial.println("Turning Left");
}

void turnRight() {
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
  digitalWrite(B_IN1, HIGH);
  digitalWrite(B_IN2, LOW);
  analogWrite(B_ENA, motorSpeed);
  
  // Back Right Motor - Backward
  digitalWrite(B_IN3, LOW);
  digitalWrite(B_IN4, HIGH);
  analogWrite(B_ENB, motorSpeed);
  
  Serial.println("Turning Right");
}

void stopMotors() {
  // Stop all motors
  analogWrite(F_ENA, 0);
  analogWrite(F_ENB, 0);
  analogWrite(B_ENA, 0);
  analogWrite(B_ENB, 0);
  
}

void increaseSpeed() {
  if (motorSpeed < 255) {
    motorSpeed += 25;
    if (motorSpeed > 255) motorSpeed = 255;
  }
}

void decreaseSpeed() {
  if (motorSpeed > 0) {
    motorSpeed -= 25;
    if (motorSpeed < 0) motorSpeed = 0;
  }
}