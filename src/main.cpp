#include <Arduino.h>
#include <SimpleLibrary.h>

SimpleLibrary lib;

void setup() {
    Serial.begin(115200);
}

void loop() {
    lib.printHello();
    int result = lib.addNumbers(10, 20);
    Serial.print("Result of 10 + 20: ");
    Serial.println(result);
    delay(1000);
}