# include "BluetoothSerial.h"
BluetoothSerial SerialBT;

int state = 0;
int led_pin = 12;
int data;

void setup() {
  Serial.begin(9600);
  if (!SerialBT.begin("Deneyap")){
    Serial.println("Bluetooth bağlantısı hatalı...");
    while(1);
  }
  pinMode(led_pin , OUTPUT);

  digitalWrite(led_pin , LOW);
  
  Serial.println("Hazır, bluetooth'a bağlanabilir ...");
}

void loop() {
  data = SerialBT.read();
  Serial.print("Data: ");
  Serial.println(data);
  delay(500);
  
  if (data == 48){
    digitalWrite(led_pin, LOW);
    Serial.println("Led kapandı ...");
    delay(300);
    
  }
  else if (data == 49){
    digitalWrite(led_pin,HIGH);
    Serial.println("Led Açıldı ...");
    delay(300);
  }
  
}
