#include <Arduino.h>
#include <Servo.h>
#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <ESP8266HTTPClient.h>
#include "Auras.h"

enum Lid { OPEN_LID = 110, CLOSED_LID = 171 };

short SERVO_PIN = 4;
short LID_PIN = 10;
short PIXEL_PIN = 5;
short SHUTTER_PIN = A0;
short SHUTTER_THRESHOLD = 300;

short TOTAL_EXPOSURE_MILLIS = 1700;
short PAUSE_EXPOSURE_MILLIS = 100;
short COLOR_EXPOSURE_MILLIS = 100;

Servo myservo;
Adafruit_NeoPixel mPixels = Adafruit_NeoPixel(16, PIXEL_PIN, NEO_GRB + NEO_KHZ800);
Lid mLid = OPEN_LID;

void setup() {
  myservo.attach(SERVO_PIN);
  pinMode(LID_PIN, INPUT_PULLUP);
  digitalWrite(SHUTTER_PIN, INPUT_PULLUP);
  mLid = OPEN_LID;
  myservo.write(OPEN_LID);
  mPixels.begin();
  mPixels.setBrightness(255);
  mPixels.show();
}

void loop() {
  if (mLid == OPEN_LID) {
    if (digitalRead(LID_PIN) == LOW) {
      mLid = CLOSED_LID;
      myservo.write(CLOSED_LID);
    }
  } else {
    if (analogRead(SHUTTER_PIN) < SHUTTER_THRESHOLD) {
      clearPixels(mPixels, PAUSE_EXPOSURE_MILLIS);
      showQuarterPixels(mPixels, 0, COLOR_EXPOSURE_MILLIS, mPixels.Color(0, 0, 255));

      clearPixels(mPixels, PAUSE_EXPOSURE_MILLIS);
      showQuarterPixels(mPixels, 2, COLOR_EXPOSURE_MILLIS, mPixels.Color(0, 255, 0));

      clearPixels(mPixels, PAUSE_EXPOSURE_MILLIS);
      showQuarterPixels(mPixels, 3, COLOR_EXPOSURE_MILLIS, mPixels.Color(255, 0, 0));

      clearPixels(mPixels, TOTAL_EXPOSURE_MILLIS - 3 * (PAUSE_EXPOSURE_MILLIS + COLOR_EXPOSURE_MILLIS));

      mLid = OPEN_LID;
      myservo.write(OPEN_LID);
      delay(10);
    }
  }
}

void clearPixels(Adafruit_NeoPixel &mPixels, short mDelay) {
  clearPixels(mPixels);
  delay(mDelay);
}

void clearPixels(Adafruit_NeoPixel &mPixels) {
  for (short i = 0; i < 4; i++) {
    showQuarterPixels(mPixels, i, 0, mPixels.Color(0, 0, 0));
  }
}

void showQuarterPixels(Adafruit_NeoPixel &mPixels, short mQuarter, short mDelay, uint32_t mColor) {
  short numPixels = mPixels.numPixels();
  for (int i = 0; i < numPixels; i++) {
    if (i / (numPixels / 4) == mQuarter) {
      mPixels.setPixelColor(i, mColor);
    }
  }
  mPixels.show();
  delay(mDelay);
}

short randomColor() {
  return random(32, 255);
}

