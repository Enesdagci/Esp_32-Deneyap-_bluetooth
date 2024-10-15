#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

// Fonksiyon prototipi
void processJoystickInput(char input);

void setup() {
    Serial.begin(115200);
    Serial.println("Bluetooth başlatıldı, bağlanmayı bekliyor...");
    SerialBT.begin("DeneyapKart"); // Bluetooth cihaz adı
    Serial.println("Bluetooth başlatıldı, bağlanmayı bekliyor...");
}

void loop() {
    if (SerialBT.available() > 0) {
        char input = SerialBT.read(); // Bluetooth üzerinden gelen veriyi oku
        processJoystickInput(input); // Gelen veriyi işle
    }
}

// Joystick girişini işleyen fonksiyon
void processJoystickInput(char input) {
    switch (input) {
        case 'U': // Yukarı tuşu
            digitalWrite(D0, HIGH);
            digitalWrite(D1, LOW);
            digitalWrite(D2, HIGH);
            digitalWrite(D3, LOW);
            Serial.println("Go Forward");
            break;
        case 'D': // Aşağı tuşu
            digitalWrite(D0,LOW);
            digitalWrite(D1,HIGH);
            digitalWrite(D2,LOW);
            digitalWrite(D3,HIGH);
            Serial.println("Go Backward");
            break;
        case 'L': // Sol tuşu
            
            break;
        case 'R': // Sağ tuşu
            Serial.println("Sağa");
            break;
        default:
            Serial.println("Geçersiz komut");
            break;
    }
}
