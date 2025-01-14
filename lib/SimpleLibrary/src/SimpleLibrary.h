#ifndef SIMPLE_LIBRARY_H
#define SIMPLE_LIBRARY_H

#include <Arduino.h>

class SimpleLibrary {
public:
    SimpleLibrary();
    void printHello();
    int addNumbers(int a, int b);
};

#endif // SIMPLE_LIBRARY_H