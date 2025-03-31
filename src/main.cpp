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
void printCert(bool keyWrite = false) {
    File file = LittleFS.open(filePath, "r");
    if (!file) {
        Serial.println("Failed to open filePath for reading");
        return;
    }

    Serial.println("Reading file.");

    while (file.available()) {
        String line = file.readStringUntil('\n');
        line.trim(); // Remove any trailing newline or carriage return

        if(keyWrite) {
            // If keyWrite is true, write each character to the keyboard individually
            for (size_t i = 0; i < line.length(); i++) {
                keyboard.write(line[i]); // Use write() to send a single character
                keyboard.write('\n'); // Simulate pressing Enter after each line
                delay(10); // Delay to ensure the keyboard can process the input
                Serial.print(line[i]); // Print to the Serial Monitor for debugging
            }
        }
        else {
            keyboard.println(line); // Send the line to the keyboard
            // Add a small delay to ensure the keyboard can process the input
            // This is especially important for HID devices to avoid overwhelming the buffer
            // You can adjust the delay time based on your needs
            delay(100); // Adjust this delay as needed
            // Note: If you're sending a lot of data, consider increasing the delay
            // to prevent overwhelming the keyboard buffer and ensure reliable transmission.
            // If you find that the keyboard is not sending all the data correctly,
            // you may need to experiment with longer delays or implement a more robust
            // mechanism to handle larger data transfers.
            Serial.println(line); // Print to the Serial Monitor for debugging
        }
    }

    file.close();
}

// Action to be performed single click of the button
void onButtonPress() {
    Serial.println("Single press detected!");
    //keyboard.print("single press detected!");
    //keyboard.println();
    printCert(false);
}

// Action to be performed on double click of the button
void onButtonDoublePress() {
    Serial.println("Double press detected!");
    printCert(true); // Call printCert with keyWrite = true to write each character
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