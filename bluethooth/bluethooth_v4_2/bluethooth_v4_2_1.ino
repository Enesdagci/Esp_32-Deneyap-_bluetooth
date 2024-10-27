#include "BluetoothSerial.h"
BluetoothSerial Serial_BT;   
#define IN1 D1 //D1
#define IN2 D2 //D2

   
  
    // Motor 1
//#define ENA 31 //D0


int data;
        
void setup(){
  // motor pinlerini ayarlanması
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

 // digitalWrite(ENA, HIGH);
  digitalWrite(IN1, HIGH);
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
    Serial.print("Data: ");
    Serial.println(data);
    switch(data){
      case 'F':
        delay(300);
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        break;
      case 'B':
        delay(300);
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        break;
      default:
        delay(300);
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        break;

    }
  }
}
