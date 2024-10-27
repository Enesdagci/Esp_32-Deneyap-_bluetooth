#include "BluetoothSerial.h"
BluetoothSerial Serial_BT;

// Motor 1
// D0 - PWM, D1 - IN1, D2 - IN2
#define ENA D2
#define IN1 D0
#define IN2 D1
int data;

void setup() {
  // motor pinlerini ayarlanması
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  // digitalWrite(D0, HIGH);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  // Ekrana yazdırma ile bluetooth aktifliğini kontrolü
  Serial.begin(9600);
  if (!Serial_BT.begin("Hamal")) {
    Serial.println("Kullanım dışı ....");
    while (1)
      ;
  }
  Serial.println("Bağlantı Hazır ....");
}

void loop() {
  if (Serial_BT.available()) {
    data = Serial_BT.read();
    Serial.print("Data: ");
    Serial.println(data);
    switch (data) {
      case 'F':
       // delay(100);
        //digitalWrite(D1,LOW);
        //digitalWrite(D2,LOW);

        //delay(100);
        
        digitalWrite(IN2, HIGH);
        digitalWrite(IN1, LOW);
        Serial.println("İleri ....");
        break;
      case 'B':
       // digitalWrite(D1,LOW);
      //  digitalWrite(D2,LOW);
      //  delay(100);
        digitalWrite(IN2, LOW);
        digitalWrite(IN1, HIGH);
        Serial.println("Geri ....");
        break;
      default:
        Serial.println("Durdu ....");
        digitalWrite(IN2, LOW);
        digitalWrite(IN1, LOW);
        break;
    }
  }
}
