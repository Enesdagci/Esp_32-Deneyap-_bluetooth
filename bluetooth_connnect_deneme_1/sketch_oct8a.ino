#include "BluetoothSerial.h"
#define ledPin 14
int state = 0;

BluetoothSerial SerialBT;

void setup() {
  // Seri iletişimi başlat
  Serial.begin(115200);
  SerialBT.begin("DeneyapKart"); // Bluetooth cihaz adı
  Serial.println("Bluetooth başlatıldı, bağlanmayı bekliyor...");
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  
}

void loop() {
  if (SerialBT.available() > 0) {  // Bluetooth üzerinden veri kontrolü
    state = SerialBT.read();       // Bluetooth verisini oku
    Serial.print(state);
    if (state == '0') {  // '0' gelirse LED söner
      digitalWrite(ledPin, LOW);
      Serial.println("LED Kapalı");
    } 
    else if (state == '1') {  // '1' gelirse LED yanar
      digitalWrite(ledPin, HIGH);
      Serial.println("LED Açık");
    }
  }
}

