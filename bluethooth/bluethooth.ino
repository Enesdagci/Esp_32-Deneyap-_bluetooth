#include "BluetoothSerial.h"

BluetoothSerial SerialBT;
string gelenVeri;

void setup() {
  // Seri iletişimi başlat
  Serial.begin(115200);
  SerialBT.begin("DeneyapKart"); // Bluetooth cihaz adı
  Serial.println("Bluetooth başlatıldı, bağlanmayı bekliyor...");
}



void loop() {
  // Eğer Bluetooth üzerinden veri gelirse bu bloğa girer
  if (SerialBT.available()) {
    char command = Serial.read();
    executeCommand(gelenVeri);
    String gelenVeri = SerialBT.readString(); // Gelen veriyi oku
    Serial.print("Gelen veri: ");
    Serial.println(gelenVeri); // Seri monitörde göster
  }

  void executeCommand(char command)
  switch (command){
    case 'FORWARD':
      digitalWrite(D1, HIGH);
      digitalWrite(D4, HIGH);
      digitalWrite(D7, HIGH);
      digitalWrite(D10,HIGH);
      Serial.println("Go Forward")
      break;
    case 'START':
      break;
    case 'PAUSE':
      digitalWrite(D1,LOW);
      digitalWrite(D4,LOW);
      digitalWrite(D7,LOW);
      digitalWrite(D10,LOW);
      Serial.println("PAUSED");
      break;
    default:
      Serial.println("İNvalid command recived")
      break;
  }
  
  
  
  // Seri monitörden gelen veri Bluetooth üzerinden gönderilir
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
}
