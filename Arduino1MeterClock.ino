#include <Time.h>
#include <Wire.h>
#include <RTClib.h>

RTC_DS1307 RTC;

const int meterPin = 5; // PWM Pin
// put a 10uf capacitor across meter to smooth out pulses otherwise
// the meter will make noise, and it's probably bad for the meter.

void setup() {
  
  // Hold max pwm modulation for 8 seconds for calibration of meter. 
  analogWrite(meterPin, 255);
  delay(8000);
  // Turn off for 2 second to indicate end of calibration mode.
  analogWrite(meterPin, 0);
  delay(2000);
  
  Wire.begin();
  RTC.begin();
}

void loop() {
  
  // get decimal time, in hours
  DateTime now = RTC.now();
  int timeHour = now.hour();
  int timeMinute = now.minute();
  int timeSecond = now.second();
  float timeDecimal = timeHour+(float)timeMinute/60.0;
  analogWrite(meterPin, map(timeDecimal, 0, 24, 0, 255));
  delay(5000);
  
  // get decimal minutes, including fractional secs as fractional min
  now = RTC.now();
  timeMinute = now.minute();
  timeSecond = now.second();
  float timeDecimalMin = timeMinute+(float)timeSecond/60.0;
  analogWrite(meterPin, map(timeDecimalMin, 0, 60, 0, 255));
  delay(5000);
}
