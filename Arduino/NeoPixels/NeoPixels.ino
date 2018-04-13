#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

short PIXEL_PIN = 5;

Adafruit_NeoPixel mPixels = Adafruit_NeoPixel(24, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  mPixels.begin();
  mPixels.show();
}

void loop() {
  for (int i = 0; i < mPixels.numPixels(); i++) {
    mPixels.setPixelColor(i, Wheel(millis() / 10 & 255));
  }
  mPixels.show();
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return mPixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return mPixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return mPixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

