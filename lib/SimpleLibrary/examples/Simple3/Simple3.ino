#include <Arduino.h>
#include <SimpleLibrary.h>

SimpleLibrary lib;
TimerHandle_t serialPrintTimer;

void serialPrintCallback(TimerHandle_t xTimer)
{
    lib.printHello();
}

void setup()
{
    Serial.begin(115200);

    serialPrintTimer = xTimerCreate("Serial Timer", pdMS_TO_TICKS(1000), pdTRUE, nullptr, serialPrintCallback);

    if (serialPrintTimer != nullptr)
    {
        xTimerStart(serialPrintTimer, 0);
    }
    else
    {
        Serial.println("Failed to create Serial timer");
    }
}

void loop(){ }