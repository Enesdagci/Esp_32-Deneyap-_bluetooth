#include "BluetoothSerial.h"

// Motor pin definitions for Deneyap Kart
// Front Left Motor
#define F_IN1 D1    // D1
#define F_IN2 D2    // D2
#define F_ENA D15   // D15 - PWM pin

// Front Right Motor
#define F_IN3 D5    // D5
#define F_IN4 D6    // D6
#define F_ENB D7    // D7 - PWM pin

// Back Right Motor
#define B_IN1 D10   // D10
#define B_IN2 D9    // D9
#define B_ENA D11   // D11 - PWM pin

// Back Left Motor
#define B_IN3 D14   // D14
#define B_IN4 D13   // D13
#define B_ENB D12   // D12 - PWM pin

// Led Pins for Deneyap Kart
#define Led_Red D0              // D0 - Stop (Kırmızı) Led
#define Led_Left_Orange D4     // D4 - Sol Sinyal (Turuncu)
#define Led_Right_Orange D3   // D3 - Sağ Sinyal (Turuncu)
#define Led_Front_Light 25   // D16 - Ön Far (Beyaz)
#define Led_Foggy_Light 26  // D17 - Sis Farı

// LDR Pin
#define Ldr A0             // A0 - LDR (Sis Farı Sensörü)

// Buzzer Pin 
#define Buzzer D8          // Korna     


// Bluetooth setup
BluetoothSerial SerialBT;

// Motor speed (0-255)
int motorSpeed = 200;

// LED control variables
bool allLedsOn = false;
bool leftSignalOn = false;
bool rightSignalOn = false;
unsigned long lastSignalToggle = 0;
bool signalState = false;
const unsigned long signalInterval = 500; // 500ms yanıp sönme

// LDR threshold for fog light
const int ldrThreshold = 75; // Bu değeri ortam ışığına göre ayarlayın

void setup() {
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

  // Set all led pins as outputs
  pinMode(Led_Red, OUTPUT);
  pinMode(Led_Left_Orange, OUTPUT);
  pinMode(Led_Right_Orange, OUTPUT);
  pinMode(Led_Front_Light, OUTPUT);
  pinMode(Led_Foggy_Light, OUTPUT);
  
  // Set LDR pin as input
  pinMode(Ldr, INPUT);

  // Set Buzzer pin 
  pinMode(Buzzer, OUTPUT);
  
  // Stop all motors initially
  stopMotors();
  
  // All LEDs off initially
  allLedsOff();
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
        turnRight();
        break;
      case 'L':
        turnLeft();
        break;
      case '0':
        stopMotors();
        break;
      case 'X':
        honk();
        break;
      case 'T':
        break;
      case 'A': // Tüm ledler açık (Start)
        allLedsOn = true;
        leftSignalOn = false;
        rightSignalOn = false;
        ledOn();
        break;
      case 'P': // Tüm ledler kapalı
        allLedsOn = false;
        leftSignalOn = false;
        rightSignalOn = false;
        allLedsOff();
        break;
      case 'S': // Sol sinyal (Kare tuşu)
        leftSignalOn = !leftSignalOn;  // Toggle sol sinyal
        rightSignalOn = false;         // Sağ sinyali kapat
        allLedsOn = false;            // Diğer ledleri kapat
        if (!leftSignalOn) {
          digitalWrite(Led_Left_Orange, LOW); // Hemen kapat
        }
        break;
      case 'C': // Sağ sinyal (Daire tuşu)
        rightSignalOn = !rightSignalOn; // Toggle sağ sinyal
        leftSignalOn = false;           // Sol sinyali kapat
        allLedsOn = false;             // Diğer ledleri kapat
        if (!rightSignalOn) {
          digitalWrite(Led_Right_Orange, LOW); // Hemen kapat
        }
        break;
    }
  }
  
  // Handle signal blinking
  handleSignals();
  
  // Handle fog light based on LDR
  handleFogLight();
}

void handleSignals() {
  unsigned long currentTime = millis();
  
  if (leftSignalOn || rightSignalOn) {
    if (currentTime - lastSignalToggle >= signalInterval) {
      signalState = !signalState;
      lastSignalToggle = currentTime;
      
      if (leftSignalOn) {
        digitalWrite(Led_Left_Orange, signalState ? HIGH : LOW);
        digitalWrite(Led_Right_Orange, LOW); // Sağ sinyali kapat
      }
      
      if (rightSignalOn) {
        digitalWrite(Led_Right_Orange, signalState ? HIGH : LOW);
        digitalWrite(Led_Left_Orange, LOW); // Sol sinyali kapat
      }
    }
  } else {
    // Sinyaller kapalıysa LED'leri kapat
    digitalWrite(Led_Left_Orange, LOW);
    digitalWrite(Led_Right_Orange, LOW);
  }
}

void handleFogLight() {
  int ldrValue = analogRead(Ldr);
  int ldrValueMapped = map(ldrValue, 0, 4095, 0, 255);
  
  if (ldrValueMapped < ldrThreshold) {
    digitalWrite(Led_Foggy_Light, HIGH);
  } else {
    digitalWrite(Led_Foggy_Light, LOW);
  }
}

void moveBackward() {
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
  
  // Geri giderken kırmızı LED'i kapat
  digitalWrite(Led_Red, LOW);
}

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
  
  // İleri giderken kırmızı LED'i kapat
  digitalWrite(Led_Red, LOW);
}

void turnRight() {
  // Left motors forward, right motors backward (spot turn)
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

void turnLeft() {
  // Left motors backward, right motors forward (spot turn)
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

  // Motorlar dururken kırmızı LED'i aç
  digitalWrite(Led_Red, HIGH);
}

void ledOn() {
  // Tüm ledler açık (şeffaf ön farlar ve arka kırmızı)
  digitalWrite(Led_Front_Light, HIGH);  // Ön beyaz farlar
  digitalWrite(Led_Red, HIGH);          // Arka kırmızı
  // Sinyal LED'leri ayrı kontrol edildiği için burada açılmıyor
  digitalWrite(Led_Foggy_Light, HIGH);
}

void allLedsOff() {
  // Bütün ledler kapalı
  digitalWrite(Led_Red, LOW);
  digitalWrite(Led_Left_Orange, LOW);
  digitalWrite(Led_Right_Orange, LOW);
  digitalWrite(Led_Front_Light, LOW);
  digitalWrite(Led_Foggy_Light, LOW);
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
