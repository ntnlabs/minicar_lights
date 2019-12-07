#include <Adafruit_NeoPixel.h>
#define PIXEL_COUNT 12
#define PIXEL_PIN 7
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_RGB + NEO_KHZ800);


void setup() {
  // put your setup code here, to run once:
 strip.begin();
 strip.clear();
 strip.show();
}

void loop() {
  // put your main code here, to run repeatedly:
 strip.setPixelColor(0, 255, 0, 0);
 strip.show();
 delay(500);
 strip.setPixelColor(0, 0, 255, 0);
 strip.show();
 delay(500);
 strip.setPixelColor(0, 0, 0, 255);
 strip.show();
 delay(500);
}
