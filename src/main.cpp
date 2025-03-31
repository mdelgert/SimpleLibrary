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

// Read cert.crt from LittleFS and print it to the Serial Monitor
void printCert() {
    File file = LittleFS.open("/cert.crt", "r");
    if (!file) {
        Serial.println("Failed to open /cert.crt");
        return;
    }

    Serial.println("Reading /cert.crt:");

    while (file.available()) {
        String line = file.readStringUntil('\n');
        line.trim(); // Remove any trailing newline or carriage return
        Serial.println(line);
    }

    file.close();
}

// Action to be performed single click of the button
void onButtonPress() {
    Serial.println("Single press detected!");
    keyboard.print("single press detected!");
    keyboard.println();
    printCert();
}

// Action to be performed on double click of the button
void onButtonDoublePress() {
    Serial.println("Double press detected!");
    Serial.print("Device Name: ");
    Serial.println(settings.getDeviceName());
    keyboard.println("double press detected!");
    Serial.print("Max Heap: ");
    Serial.println(ESP.getMaxAllocHeap());
    Serial.print("Free Heap: ");
    Serial.println(ESP.getFreeHeap());
}

// Action to be performed on long press of the button
void onButtonLongPress() {
    Serial.println("Long press detected!");

    // Declare a message to be sent
    const char *message = "long press detected!";

    // Send the message character by character
    for (int i = 0; message[i] != '\0'; i++) {
        //keyboard.print(message[i]);
        keyboard.write(message[i]); // Use write() to send a single character
        Serial.print(message[i]); // Print to the Serial Monitor for debugging
        // Add a small delay to ensure the keyboard can process the input
        // This is especially important for HID devices to avoid overwhelming the buffer
        // You can adjust the delay time based on your needs
        delay(100);
    }
    keyboard.println(); // Move to the next line after sending the message
    Serial.println("Message sent!");
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