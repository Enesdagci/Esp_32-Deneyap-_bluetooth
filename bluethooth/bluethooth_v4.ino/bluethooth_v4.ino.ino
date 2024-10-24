#include "BluetoothSerial.h"
#include "ledc.h"
BluetoothSerial Serial_BT;      
  
    // Motor 1
int Pwm = 31,Left_pwm = 30,Right_pwm = 29;
int data;

void setup(){
  // motor pinlerini ayarlanması
  pinMode(Pwm, OUTPUT);
  pinMode(Left_pwm, OUTPUT);
  pinMode(Right_pwm, OUTPUT);

  // ledcwrite kullanımı (motor ve ledler için kullanılır.)
  ledcSetup(0, 1000, 8);
  ledcAttachPin(Left_pwm, 0);   // LPwm
  // Motorlara bağlama

  ledcSetup(1, 1000, 8);
  ledcAttachPin(Right_pwm, 1);  // RPwm

 
  digitalWrite(Pwm, HIGH);

  // Ekrana yazdırma ile bluetooth aktifliğini kontrolü
  Serial.begin(9600);
  if (!Serial_BT.begin("Hamal")){
    Serial.println("Kullanım dışı ....");
    while(1);
  }
  Serial.println("Bağlantı Hazır ....");
}

void loop(){
  if (Serial_BT.available()){
    data = Serial_BT.read();
    if (data == 'F'){
      ledcWrite(0, 255);   // LPWM
      ledcWrite(1, 0);   // RPWM
      Serial.println("İleri gidiyor ....");

    }
    if (data == 'B'){
      ledcWrite(0, 0);
      ledcWrite(1, 255);
      Serial.println("Geriye gidiyor ....");
    }
    if (data == 'R'){
      ledcWrite(0, 0);
      ledcWrite(1, 255);
      Serial.println("Sağa Doğru gidiyor ....");
    }
    if (data == '0'){
      ledcWrite(0, 0);  //LPwm
      ledcWrite(1, 0);  //RPwm
      Serial.println("Durdu ....");
    }
    // if 'S' kare, 'C' daire
  }
}
