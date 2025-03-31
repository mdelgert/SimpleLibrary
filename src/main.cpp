#include <Arduino.h>
#include <SimpleLibrary.h>
#include "Settings.h"
#include "OneButton.h"

#define PIN_INPUT 0

OneButton button(PIN_INPUT, true);
SimpleLibrary lib;

// Action to be performed when the button is pressed
void onButtonPress() {
    Serial.println("Button Pressed!");
}

void setup() {
    Serial.begin(115200);
    settings.setDeviceName("MyESP32");
    settings.setWifiSSID("HomeNetwork");
    // Attach single click event to the button
    button.attachClick(onButtonPress);
}

void loop() {
    //lib.printHello();
    //Serial.print("Device Name: ");
    //Serial.println(settings.getDeviceName());
    //delay(1000); // Wait for 1 second
    button.tick();
}