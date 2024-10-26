#include "BluetoothSerial.h"
BluetoothSerial Serial_BT;      
  
    // Motor 1
#define ENA 31 //D0
#define IN1 13 //D12
#define IN2 12 //D13

int data;

void setup(){
  // motor pinlerini ayarlanması

  digitalWrite(ENA, HIGH);
  digitalWrite(IN1, LOW);   
  digitalWrite(IN2, LOW);

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
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(ENA, HIGH);
    Serial.println("İleriye gidiyor ....");
    }

    if (data == 'B'){
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(ENA, HIGH);
      Serial.println("Geriye gidiyor ....");
    }
    if (data == '0'){
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(ENA, LOW);
      Serial.println("Durdu ....");
    }
    // if 'S' kare, 'C' daire
  }
}
