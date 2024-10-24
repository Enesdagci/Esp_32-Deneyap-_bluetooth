#include "BluetoothSerial.h"
BluetoothSerial Serial_BT;      
  
    // Motor 1
int d0 = 31,d1 = 30,d2 = 29;
int data;

void setup(){
  // motor pinlerini ayarlanması
  pinMode(d0, OUTPUT);
  pinMode(d1, OUTPUT);
  pinMode(d2, OUTPUT);

  digitalWrite(d0, HIGH);
  digitalWrite(d1, LOW);   
  digitalWrite(d2, LOW);


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
    digitalWrite(d1, LOW);
    digitalWrite(d2, HIGH);
    digitalWrite(d0, HIGH);
    Serial.println("İleriye gidiyor ....");
    }

    if (data == 'B'){
      digitalWrite(d1, HIGH);
      digitalWrite(d2, LOW);
      digitalWrite(d0, HIGH);
      Serial.println("Geriye gidiyor ....");
    }
    if (data == 'R'){
      digitalWrite(d1, LOW);
      digitalWrite(d2, HIGH);
      digitalWrite(d0, HIGH);
      Serial.println("Sağa Doğru gidiyor ....");
    }
    if (data == '0'){
      digitalWrite(d1, LOW);
      digitalWrite(d2, LOW);
      digitalWrite(d0, LOW);
      Serial.println("Durdu ....");
    }
    // if 'S' kare, 'C' daire
  }
}
