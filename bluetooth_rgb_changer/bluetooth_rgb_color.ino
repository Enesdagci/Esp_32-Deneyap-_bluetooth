# include "BluetoothSerial.h"
BluetoothSerial SerialBT;
int rgb_red_pin = 11 ;
int rgb_blue_pin = 12 ;
int rgb_green_pin = 13 ;
int data ;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //SerialBT.begin("Esp32");

  pinMode(rgb_red_pin, OUTPUT);
  pinMode(rgb_blue_pin, OUTPUT);
  pinMode(rgb_green_pin, OUTPUT);

  digitalWrite(rgb_red_pin, LOW);
  digitalWrite(rgb_blue_pin, LOW);
  digitalWrite(rgb_green_pin, LOW);

  Serial.println("Bluetooth hazır bağlanabilir ...");


}

void loop() {
  // put your main code here, to run repeatedly:
  if (SerialBT.available()){
  data = SerialBT.read();
  Serial.print("Data: ");
  Serial.println(data);
  delay(300);
  }

}
  