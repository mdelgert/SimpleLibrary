#include <Arduino.h>
#include <LittleFS.h>
#include <SimpleLibrary.h>
#include "Settings.h"
#include "OneButton.h"
#include "SecureExample.h"
#include <USB.h>
#include <USBHIDKeyboard.h>

USBHIDKeyboard keyboard;
OneButton button(PIN_INPUT, true);
SimpleLibrary lib;

void printFile(const char *filePath) {
    File file = LittleFS.open(filePath, "r");
    if (!file) {
        // Serial.println("Failed to open filePath for reading");
        return;
    }

    // Ensure USB HID is fully initialized
    delay(500); // Increased delay to give USB more time
    keyboard.begin(); // Reinitialize keyboard to ensure buffer is clear

    // Reset file pointer to start
    file.seek(0);

    while (file.available()) {
        char c = file.read();
        if (c != '\r') { // Skip carriage returns, if any
            keyboard.write(c);
            // Serial.print(c); // Commented out to test without Serial interference
            //delay(5); // Too fast can overwhelm the keyboard buffer
            //delay(10); // Seems almost right in most cases
            delay(25);
            //delay(50);       
        }
    }

    file.close();
    keyboard.write('\n'); // Ensure final newline
    // Serial.println();
}

// Action to be performed single click of the button
void onButtonPress() {
    Serial.println("Single press detected!");
    printFile("/cert.crt"); // Call the function to print the certificate
}

// Action to be performed on double click of the button
void onButtonDoublePress() {
    Serial.println("Double press detected!");
    printFile("/description.md");
    //Serial.print("Device Name: ");
    //Serial.println(settings.getDeviceName());
    // keyboard.println("double press detected!");
    // Serial.print("Max Heap: ");
    // Serial.println(ESP.getMaxAllocHeap());
    // Serial.print("Free Heap: ");
    // Serial.println(ESP.getFreeHeap());
}

// Action to be performed on long press of the button
void onButtonLongPress() {
    Serial.println("Long press detected!");
    printFile("/readme.md");
}

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("Begin Setup:");

    // Once enabled, the USBHIDKeyboard will take control of the USB connection
    // To upload code again will need to hold the button
    USB.begin();            // Initialize USB communication
    keyboard.begin();       // Initialize the keyboard
    delay(1000);           // Wait for the USB connection to establish
    //settings.setDeviceName("MyESP32");
    //settings.setWifiSSID("HomeNetwork");
    button.attachClick(onButtonPress);
    button.attachDoubleClick(onButtonDoublePress);
    button.attachLongPressStart(onButtonLongPress);

    if (!LittleFS.begin(true)) {
        Serial.println("LittleFS mount failed");
        return;
    }

    Serial.println("End Setup:");
}

void loop() {
    //lib.printHello();
    button.tick();
    //delay(10);
}
