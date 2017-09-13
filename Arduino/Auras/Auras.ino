#include <Servo.h>

enum Lid { OPEN = 110, CLOSED = 170 };

Servo myservo;
Lid mLid = OPEN;

short SERVO_PIN = 3;
short LID_PIN = 2;
short SHUTTER_PIN = A0;
short SHUTTER_THRESHOLD = 500;

void setup() {
  myservo.attach(SERVO_PIN);
  pinMode(LID_PIN, INPUT_PULLUP);
  mLid = OPEN;
  myservo.write(OPEN);
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

