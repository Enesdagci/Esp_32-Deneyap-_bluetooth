#include "BluetoothSerial.h"

BluetoothSerial SerialBT;
String gelenVeri; // Declare gelenVeri at the top

// Function prototype for executeCommand
void executeCommand(String command); 

void setup() {
    Serial.begin(115200);
    SerialBT.begin("DeneyapKart");
    Serial.println("Bluetooth başlatıldı, bağlanmayı bekliyor...");
}

void loop() {
    if (SerialBT.available() > 0) {
        gelenVeri = SerialBT.readString();  // Read the incoming data
        Serial.println(gelenVeri);  // Print it to the Serial Monitor
        executeCommand(gelenVeri);  // Call the function with the received command
    }
}

// Define the executeCommand function
void executeCommand(String command) {
    switch (command.charAt(0)) { // Check the first character of the command
        case '0':
            // Code to turn off the LED
            Serial.println("LED OFF");
            break;
        case '1':
            // Code to turn on the LED
            Serial.println("LED ON");
            break;
        default:
            Serial.println("Invalid command");
            break;
    }
}
