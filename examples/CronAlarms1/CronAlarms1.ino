//https://registry.platformio.org/libraries/martin-laclaustra/CronAlarms/examples/CronAlarms_example/CronAlarms_example.ino


#include <time.h>                       // time() ctime()
#include "CronAlarms.h"

CronId id;

// functions to be called when an alarm triggers:
void MorningAlarm() {
  Serial.println("Alarm: - turn lights off");
}

void EveningAlarm() {
  Serial.println("Alarm: - turn lights on");
}

void WeeklyAlarm() {
  Serial.println("Alarm: - its Saturday Morning");
}

void ExplicitAlarm() {
  Serial.println("Alarm: - this triggers only at the given date and time");
}

void Repeats() {
  Serial.println("15 second timer");
}

void Repeats1() {
  Serial.println("1 second timer");
}

void Repeats2() {
  Serial.println("2 second timer");
}

void OnceOnly() {
  Serial.println("This timer only triggers once, stop the 2 second timer");
  // use Cron.free(id) to disable a timer and recycle its memory.
  Cron.free(id);
  // optional, but safest to "forget" the ID after memory recycled
  id = dtINVALID_ALARM_ID;
  // you can also use Cron.disable() to turn the timer off, but keep
  // it in memory, to turn back on later with Alarm.enable().
}

void setup() {
  Serial.begin(9600);
  while (!Serial) ; // wait for Arduino Serial Monitor
  Serial.println("Starting setup...");

  struct tm tm_newtime; // set time to Saturday 8:29:00am Jan 1 2011
  tm_newtime.tm_year = 2011 - 1900;
  tm_newtime.tm_mon = 1 - 1;
  tm_newtime.tm_mday = 1;
  tm_newtime.tm_hour = 8;
  tm_newtime.tm_min = 29;
  tm_newtime.tm_sec = 0;
  tm_newtime.tm_isdst = 0;

  
  // create the alarms, to trigger at specific times
//   Cron.create("0 30 8 * * *", MorningAlarm, false);  // 8:30am every day
//   Cron.create("0 45 17 * * *", EveningAlarm, false); // 5:45pm every day
//   Cron.create("30 30 8 * * 6", WeeklyAlarm, false);  // 8:30:30 every Saturday

  // create timers, to trigger relative to when they're created
//   Cron.create("*/15 * * * * *", Repeats, false);           // timer for every 15 seconds
//   id = Cron.create("*/2 * * * * *", Repeats2, false);      // timer for every 2 seconds
//   Cron.create("*/10 * * * * *", OnceOnly, true);           // called once after 10 seconds


  Cron.create("1-30 * * * * *", Repeats1, false); 

  Serial.println("Ending setup...");
}

void loop() {
  time_t tnow = time(nullptr);
  Serial.println(asctime(gmtime(&tnow)));
  Cron.delay();// if the loop has nothing else to do, delay in ms
               // should be provided as argument to ensure immediate
               // trigger when the time is reached
  delay(1000);// do other things... like waiting one second between clock display
}