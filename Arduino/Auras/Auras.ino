#include <Servo.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

enum Lid { OPEN = 110, CLOSED = 170 };

short SERVO_PIN = 3;
short LID_PIN = 2;
short PIXEL_PIN = 6;
short SHUTTER_PIN = A0;
short SHUTTER_THRESHOLD = 500;

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
      // TODO: Turn on lights
      // delay();
      mLid = OPEN;
      myservo.write(OPEN);
      delay(10);
    }
  }
}

