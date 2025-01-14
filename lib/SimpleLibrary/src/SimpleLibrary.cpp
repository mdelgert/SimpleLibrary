#include "SimpleLibrary.h"

SimpleLibrary::SimpleLibrary() {
    // Constructor
}

void SimpleLibrary::printHello() {
    Serial.println("Hello, World 1.0");
}

int SimpleLibrary::addNumbers(int a, int b) {
    return a + b;
}