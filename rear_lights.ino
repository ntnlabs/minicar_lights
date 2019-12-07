#include <Adafruit_NeoPixel.h>
#define PIXEL_COUNT 12
#define PIXEL_PIN 7
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_RGB + NEO_KHZ800);

// Lets define some global colors
uint32_t ColorRED;
uint32_t ColorGREEN;
uint32_t ColorBLUE;
uint32_t ColorOFF;
uint32_t ColorFLASH;

// my strip has GREEN - RED - BLUE setup

void setup() {
 strip.begin();
 strip.clear();
 strip.show();

// Setting brightness - will be later changed automatically by photo element
 strip.setBrightness(25);

// Lest fill the colors
 ColorGREEN=strip.Color(255,0,0);
 ColorRED=strip.Color(0,255,0);
 ColorBLUE=strip.Color(0,0,255);
 ColorOFF=strip.Color(0,0,0);
 ColorFLASH=strip.Color(40,255,0);
}

// Filling the whole strip at once
void FullFill(uint32_t PixelColor) {
  for(int i=0; i<PIXEL_COUNT; i++) {
    strip.setPixelColor(i, PixelColor);
  }
  strip.show();
}

// This will make a three fast flashes in orange color. This will be turned on by our hazard lights.
void Flashing_Hazard(int Lenght) {
  FullFill(ColorOFF);
  for(int i=0; i<Lenght; i++) {
    for(int j=0; j<4; j++) {
      FullFill(ColorFLASH);
      delay(60);
      FullFill(ColorOFF);
      delay(40);
    }
  FullFill(ColorOFF);
  delay(550);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

 Flashing_Hazard(10);

 FullFill(ColorBLUE);
 delay(5000);
}
