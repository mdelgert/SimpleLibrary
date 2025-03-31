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

// Action to be performed single click of the button
void onButtonPress() {
    Serial.println("Single press detected!");
    //keyboard.print("single press detected!");
    //keyboard.println();
}

// Action to be performed on double click of the button
void onButtonDoublePress() {
    Serial.println("Double press detected!");
    keyboard.println("double press detected!");
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
    //USB.begin();            // Initialize USB communication
    //keyboard.begin();       // Initialize the keyboard
    //delay(1000);           // Wait for the USB connection to establish

    Serial.begin(115200);

    settings.setDeviceName("MyESP32");
    settings.setWifiSSID("HomeNetwork");

    // Attach single click event to the button
    button.attachClick(onButtonPress);
    
    // Attach double click event to the button
    button.attachDoubleClick(onButtonDoublePress);
    
    // Attach long press event to the button
    button.attachLongPressStart(onButtonLongPress);
}

void loop() {
    //lib.printHello();
    //Serial.print("Device Name: ");
    //Serial.println(settings.getDeviceName());
    //delay(1000); // Wait for 1 second
    button.tick();
}