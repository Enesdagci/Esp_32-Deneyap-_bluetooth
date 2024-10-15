# include "BluetoothSerial.h"
BluetoothSerial SerialBT;

int led_pin_14 = 11;
int led_pin_13 = 12;
int led_pin_12 = 13;
int data;

void setup(){
  Serial.begin(9600);
  if (!SerialBT.begin("Deneyap")){
    Serial.println("Hatalı bağlantı Tekrar bağlan ...");
    while(1);
  }
  pinMode(led_pin_14, OUTPUT);
  pinMode(led_pin_13, OUTPUT);
  pinMode(led_pin_12, OUTPUT);
  digitalWrite(led_pin_14, LOW);
  digitalWrite(led_pin_13, LOW);
  digitalWrite(led_pin_12, LOW);
  Serial.println("Hazır, bluetooth bağlanabilir ...");

}

void loop(){
  data = SerialBT.read();
  Serial.print("Data: ");
  Serial.println(data);
  delay(500);
  if (data == 48){
    digitalWrite(led_pin_14, LOW);
    digitalWrite(led_pin_13, LOW);
    digitalWrite(led_pin_12, LOW);
    Serial.println("Ledler Kapandı ...");
    delay(300);
  }
  if (data == 49){
    digitalWrite(led_pin_14, HIGH);
    digitalWrite(led_pin_13, HIGH);
    digitalWrite(led_pin_12, HIGH);
    Serial.println("Ledler açıldı ...");
    delay(300);
  }
}
