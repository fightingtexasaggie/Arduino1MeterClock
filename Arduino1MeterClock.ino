#include <Time.h>
#include <Wire.h>
#include <RTClib.h>

RTC_DS1307 RTC;

const int meterPin = 5; // PWM Pin

void setup() {
  
  // Hold max pwm modulation for 5 seconds for calibration of meter. 
  analogWrite(meterPin, 255);
  delay(5000);
  // Turn off for 1 second to indicate end of calibration mode.
  analogWrite(meterPin, 0);
  delay(1000);
  
  Wire.begin();
  RTC.begin();
}

void loop() {
  
  // get decimal time, in hours
  DateTime now = RTC.now();
  int timeHour = now.hour();
  int timeMinute = now.minute();
  int timeSecond = now.second();
  float timeDecimal = timeHour+timeMinute/60+timeSecond/3600;
  analogWrite(meterPin, map(timeDecimal, 0, 24, 0, 255));
  delay(5000);
  
  // get decimal minutes, including fractional secs as fractional min
  now = RTC.now();
  timeMinute = now.minute();
  timeSecond = now.second();
  float timeDecimalMin = timeMinute+timeSecond/60;
  analogWrite(meterPin, map(timeDecimalMin, 0, 60, 0, 255));
  delay(5000);
}
