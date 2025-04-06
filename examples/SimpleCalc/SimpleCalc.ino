#include <SimpleLibrary.h>

SimpleLibrary lib;

void setup() {
    Serial.begin(115200);
    int result = lib.addNumbers(5, 7);
    Serial.print("Result of 5 + 7: ");
    Serial.println(result);
}

void loop() {
    // Do nothing
}