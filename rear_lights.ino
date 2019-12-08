#include <Adafruit_NeoPixel.h>
#define PIXEL_COUNT_REAR 12
#define PIXEL_COUNT_FRONT 15
#define PIXEL_PIN_REAR_LEFT 7
#define PIXEL_PIN_REAR_RIGHT 6
#define PIXEL_PIN_FRONT_LEFT 8
#define PIXEL_PIN_FRONT_RIGHT 9

Adafruit_NeoPixel strip_RL = Adafruit_NeoPixel(PIXEL_COUNT_REAR, PIXEL_PIN_REAR_LEFT, NEO_RGB + NEO_KHZ800);
//Adafruit_NeoPixel strip_RR = Adafruit_NeoPixel(PIXEL_COUNT_REAR, PIXEL_PIN_REAR_RIGHT, NEO_RGB + NEO_KHZ800);
//Adafruit_NeoPixel strip_FL = Adafruit_NeoPixel(PIXEL_COUNT_FRONT, PIXEL_PIN_FRONT_LEFT, NEO_RGB + NEO_KHZ800);
//Adafruit_NeoPixel strip_FR = Adafruit_NeoPixel(PIXEL_COUNT_FRONT, PIXEL_PIN_FRONT_RIGHT, NEO_RGB + NEO_KHZ800);

// Lets define some global colors
uint32_t ColorRED;
uint32_t ColorGREEN;
uint32_t ColorBLUE;
uint32_t ColorOFF;
uint32_t ColorFLASH;
uint32_t ColorSTART;

// my strip has GREEN - RED - BLUE setup

void setup() {
 strip_RL.begin();
 strip_RL.clear();
 strip_RL.show();

// Setting brightness - will be later changed automatically by photo element
 strip_RL.setBrightness(100);

// Lest fill the colors here and use them anywhere ;)
 ColorGREEN=strip_RL.Color(255,0,0);
 ColorRED=strip_RL.Color(0,255,0);
 ColorBLUE=strip_RL.Color(0,0,255);
 ColorOFF=strip_RL.Color(0,0,0);
 ColorFLASH=strip_RL.Color(40,255,0);
 ColorSTART=strip_RL.Color(200,50,100);
}

// Filling the whole strip at once
void FullFill(uint32_t PixelColor) {
  for(int i=0; i<PIXEL_COUNT_REAR; i++) {
    strip_RL.setPixelColor(i, PixelColor);
  }
  strip_RL.show();
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
  delay(700);
  }
}

// This is a fancy startup effect
void StartMeUp() {
  FullFill(ColorOFF);
  int ThisDelay = 200;
  for(int j=0; j<3; j++) {
    for(int i=0; i<PIXEL_COUNT_REAR; i++) {
      strip_RL.setPixelColor(i, ColorSTART);
      if (i>0) {
        strip_RL.setPixelColor(i-1, ColorOFF);
      }
      if (i==0) {
        strip_RL.setPixelColor(PIXEL_COUNT_REAR-1, ColorOFF);
      }
      ThisDelay=ThisDelay-5;
      strip_RL.show();
      delay(ThisDelay);
    }
  }
  for(int i=0; i<PIXEL_COUNT_REAR; i++) {
    strip_RL.setPixelColor(i, ColorSTART);
    ThisDelay=ThisDelay-10;
    strip_RL.show();
    delay(50);
  }
  delay(500);
  FullFill(ColorOFF);
}

void loop() {
  // put your main code here, to run repeatedly:

 StartMeUp();

 delay(1000);
 FullFill(ColorBLUE);
 delay(5000);
}
