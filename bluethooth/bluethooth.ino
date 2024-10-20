#include "BluetoothSerial.h"
BluetoothSerial Serial_BT;

int data,d1 = 30,d4 = 27,d7 = 24,d10 = 21;
void setup(){
  //Pinlerin hazılanması ve yazdırılması
  pinMode(d1,OUTPUT);
  digitalWrite(d1,LOW);

  pinMode(d4,OUTPUT);
  digitalWrite(d4,LOW);

  pinMode(d7,OUTPUT);
  digitalWrite(d7,LOW);
  
  pinMode(d10, OUTPUT);
  digitalWrite(d10, LOW);

  // Seri monitörün ayarlanması
  Serial.begin(9600);
  if (!Serial_BT.begin("Esp32")){
    Serial.println("Hatalı bağlantı ....");
    while(1);
  }
  Serial.println("Bluetooth hazırlanıyor ....");

}

void loop(){

  // Bluetooth bağlantısının kontrolü
  if (Serial_BT.available()){
    Serial.println("Bluetooht bağlı ....");

    // Bluetooth dan gelen verinin okunması
    data = Serial_BT.read();
    Serial.print("Data: ");
    Serial.println(data);

    // İleri yönlü 
    if (data == 'F'){
      digitalWrite(d1, HIGH);
      digitalWrite(d4, HIGH);
      digitalWrite(d7, HIGH);
      digitalWrite(d10, HIGH);
      Serial.println("İleri gidiyor ....");
    }
      // Geri yönlü
    if (data == 'B'){
      digitalWrite(d1, HIGH);
      digitalWrite(d4, LOW);
      digitalWrite(d7,LOW);
      digitalWrite(d10, LOW);
      Serial.println("Geri gidiyor ....");
    }
      // Sağ yönlü
    if (data == 'R'){
      digitalWrite(d1,HIGH);
      digitalWrite(d4,HIGH);
      digitalWrite(d7,LOW);
      digitalWrite(d10,LOW);
      Serial.println("Sağa gidiyor ....");
    }
      // Durdurma
    if (data == '0'){
      digitalWrite(d1,LOW);
      digitalWrite(d4, LOW);
      digitalWrite(d7, LOW);
      digitalWrite(d10, LOW);
      Serial.println("Durdu ....");
    }
  }
}