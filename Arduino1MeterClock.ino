#include <Time.h>
#include <Wire.h>
#include <RTClib.h>

RTC_DS1307 RTC;

const int meterPin = 6; // PWM Pin

void setup() {
  Wire.begin();
  RTC.begin();  
}

void loop() {
  DateTime now = RTC.now();
  int timeHour = now.hour();
  int timeMinute = now.minute();
  int timeSecond = now.second();
  float timeDecimal = timeHour+timeMinute/60+timeSecond/3600;
  analogWrite(meterPin, map(timeDecimal, 0, 24, 0, 255));
  delay(1000);
}
