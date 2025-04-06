#include <SimpleLibrary.h>

SimpleLibrary lib;

void setup() {
    Serial.begin(115200);
}

void loop() {
    lib.printHello();
    delay(1000);
}