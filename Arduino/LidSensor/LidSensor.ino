#include <Servo.h>

enum Lid { OPEN = 110, CLOSED = 170 };

Servo myservo;
Lid mLid = OPEN;

short SERVO_PIN = 3;
short LID_PIN = 2;

long lastCloseMillis = 0;

void setup() {
  myservo.attach(SERVO_PIN);
  pinMode(LID_PIN, INPUT_PULLUP);
  mLid = OPEN;
  myservo.write(OPEN);
  lastCloseMillis = millis();
}

void loop() {
  if (mLid == OPEN) {
    if (digitalRead(LID_PIN) == LOW) {
      mLid = CLOSED;
      myservo.write(CLOSED);
      lastCloseMillis = millis();
    }
  } else {
    if (millis() - lastCloseMillis > 5000) {
      mLid = OPEN;
      myservo.write(OPEN);
      delay(10);
    }
  }
}

