/*# include "BluetoothSerial.h"
BluetoothSerial SerialBT;
*/
int button_pin = 13;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
 // SerialBT.begin("Esp32");
  pinMode(button_pin, OUTPUT);
  Serial.println("Bluetooth started! Connecting ...");
}

void loop() {
  // put your main code here, to run repeatedly:
  /*
  if (Serial.available()){
    SerialBT.write(Serial.read());

  }
  if (Serial.available()){
    Serial.write(SerialBT.read());
  }
  */
  digitalWrite(button_pin, HIGH);
  delay(100);
  digitalWrite(button_pin, LOW);
  delay(100);
}
