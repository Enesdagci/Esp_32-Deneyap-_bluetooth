# include "BluetoothSerial.h"

BluetoothSerial Serial_bt;

int red_pin = 11, yellow_pin = 12, green_pin = 13;
int data;

void setup(){
  pinMode(red_pin, OUTPUT);
  pinMode(yellow_pin, OUTPUT);
  pinMode(green_pin, OUTPUT);
  
  digitalWrite(red_pin, LOW);
  digitalWrite(yellow_pin, LOW);
  digitalWrite(green_pin, LOW);

  Serial.begin(9600);
  if (!Serial_bt.begin("Esp32")){
    Serial.println("Bluetooth aktif değil ....");
    while(1);
  }
  Serial.println("Bluetooth aktifleşti ....");

}

void loop(){
    data = Serial_bt.read();
    Serial.print("Data:");
    Serial.println((char)data );
    Serial.println("Bluetooth çalışıyor ....");
  // Yukarı yönlü 
  if (data == 'F'){
    digitalWrite(red_pin, HIGH);
    Serial.println("İleri gidiyor ....");

  }
  if (data == 'B'){
    digitalWrite(yellow_pin, HIGH);
    Serial.println("Geriye gidiyor ....");
  }
  if (data == 'R'){
    digitalWrite(green_pin, HIGH);
    Serial.println("Sağa gidiyor ....");
  }
  
}