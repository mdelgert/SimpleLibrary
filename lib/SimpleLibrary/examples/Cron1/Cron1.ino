//https://registry.platformio.org/libraries/hollosi/CronTab

#include "Arduino.h"
#include <WiFi.h>
#include "time.h"
#include "esp_sntp.h"
#include "Secure.h"
#include "crontab.h"

/**
 * A proper way to handle TimeZones with daylightOffset
 * would be to specify an environment variable with TimeZone definition including daylight adjustmnet rules.
 * A list of rules for your zone could be obtained from https://github.com/nayarsystems/posix_tz_db/blob/master/zones.csv
 */
const char *time_zone = "EST5EDT,M3.2.0,M11.1.0";    // TimeZone rule
const char *ntpServer1 = "pool.ntp.org";
const char *ntpServer2 = "time.nist.gov";

CronTab cron;

// this function prints local time
void printLocalTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("No time available (yet)");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}

// Callback function (gets called when time adjusts via NTP)
void timeavailable(struct timeval *t) {
  Serial.println("Got time adjustment from NTP!");
  printLocalTime();
}

void callback() {
    Serial.println("Callback called");
}

void setup() {
    Serial.begin(115200);

    // First step is to configure WiFi STA and connect in order to get the current time and date.
    Serial.printf("Connecting to %s ", ssid);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println(" CONNECTED");

    /**
     * Set NTP and timezone
     */
    configTzTime(time_zone, ntpServer1, ntpServer2);

    struct tm timeinfo;

    if (!getLocalTime(&timeinfo))
    {
        Serial.println("Failed to obtain time");
    }

    // std::variant<CronID,CronError> ret = cron.add("0 10 * * * *", callback);  // 10th minute of every hours (e.g. 2:10,2:10,...)
    // if(std::holds_alternative<CronError>(ret))
    // {
    //     Serial.printf("Error code: %d\n",std::get<CronError>(ret));
    //     //...
    // }

}

void loop() {
    //printLocalTime();
    delay(1000);
}