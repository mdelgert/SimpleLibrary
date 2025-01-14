#include <SimpleLibrary.h>

SimpleLibrary lib;

void setup() {
    Serial.begin(115200);
    lib.printHello();
}

void loop() {
    // Do nothing
}