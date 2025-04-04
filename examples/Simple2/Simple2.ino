#include <Arduino.h>
#include <SimpleLibrary.h>

SimpleLibrary lib;

TimerHandle_t serialPrintTimer;

void serialPrintCallback(TimerHandle_t xTimer)
{
    lib.printHello();
    int result = lib.addNumbers(10, 20);
    Serial.print("Result of 10 + 20: ");
    Serial.println(result);
}

void setup()
{
    Serial.begin(115200);

    // Create the Serial print timer (period: 1000ms)
    serialPrintTimer = xTimerCreate(
        "Serial Timer",
        pdMS_TO_TICKS(1000), // Timer period in ticks (1000ms)
        pdTRUE,              // Auto-reload (true)
        nullptr,             // Timer ID (optional, nullptr for now)
        serialPrintCallback  // Callback function
    );

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