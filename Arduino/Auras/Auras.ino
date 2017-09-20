#include <Servo.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

enum Lid { OPEN = 110, CLOSED = 171 };

short SERVO_PIN = 3;
short LID_PIN = 2;
short PIXEL_PIN = 6;
short SHUTTER_PIN = A0;
short SHUTTER_THRESHOLD = 300;

Servo myservo;
Adafruit_NeoPixel mPixels = Adafruit_NeoPixel(16, PIXEL_PIN, NEO_GRB + NEO_KHZ800);
Lid mLid = OPEN;

void setup() {
  myservo.attach(SERVO_PIN);
  pinMode(LID_PIN, INPUT_PULLUP);
  digitalWrite(A0, INPUT_PULLUP);
  mLid = OPEN;
  myservo.write(OPEN);
  mPixels.begin();
  mPixels.setBrightness(255);
  mPixels.show();
}

void loop() {
  if (mLid == OPEN) {
    if (digitalRead(LID_PIN) == LOW) {
      mLid = CLOSED;
      myservo.write(CLOSED);
    }
  } else {
    if (analogRead(SHUTTER_PIN) < SHUTTER_THRESHOLD) {
      delay(100);

      showQuarterPixels(mPixels, 0, 30, mPixels.Color(0, 0, 255));
      clearPixels(mPixels, 100);
      showQuarterPixels(mPixels, 2, 30, mPixels.Color(0, 255, 0));

      clearPixels(mPixels, 1800);

      mLid = OPEN;
      myservo.write(OPEN);
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

