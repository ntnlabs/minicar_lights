#include <Adafruit_NeoPixel.h>
#define PIXEL_COUNT_REAR 12
#define PIXEL_COUNT_FRONT 15
#define PIXEL_PIN_REAR_LEFT 7
#define PIXEL_PIN_REAR_RIGHT 6
#define PIXEL_PIN_FRONT_LEFT 9
#define PIXEL_PIN_FRONT_RIGHT 8

Adafruit_NeoPixel strip_RL = Adafruit_NeoPixel(PIXEL_COUNT_REAR, PIXEL_PIN_REAR_LEFT, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel strip_RR = Adafruit_NeoPixel(PIXEL_COUNT_REAR, PIXEL_PIN_REAR_RIGHT, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel strip_FL = Adafruit_NeoPixel(PIXEL_COUNT_FRONT, PIXEL_PIN_FRONT_LEFT, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel strip_FR = Adafruit_NeoPixel(PIXEL_COUNT_FRONT, PIXEL_PIN_FRONT_RIGHT, NEO_RGB + NEO_KHZ800);

// Lets define some global colors
uint32_t ColorRED;
uint32_t ColorGREEN;
uint32_t ColorBLUE;
uint32_t ColorOFF;
uint32_t ColorFLASH;
uint32_t ColorSTART;
uint32_t ColorTURN;

// my strip has GREEN - RED - BLUE setup

void setup() {
 strip_RL.begin();
 strip_RR.begin();
 strip_RL.clear();
 strip_RR.clear();
 strip_RL.show();
 strip_RR.show();
 strip_FL.begin();
 strip_FR.begin();
 strip_FL.clear();
 strip_FR.clear();
 strip_FL.show();
 strip_FR.show();

// Setting brightness - will be later adjusted automatically by a photo element
 strip_RL.setBrightness(25);
 strip_RR.setBrightness(25);
 strip_FL.setBrightness(25);
 strip_FR.setBrightness(25);

// Lets set the colors here and use them anywhere ;)
 ColorGREEN=strip_RL.Color(255,0,0);
 ColorRED=strip_RL.Color(0,255,0);
 ColorBLUE=strip_RL.Color(0,0,255);
 ColorOFF=strip_RL.Color(0,0,0);
 ColorFLASH=strip_RL.Color(40,255,0);
 ColorSTART=strip_RL.Color(200,50,100);
 ColorTURN=strip_RL.Color(50,250,0);

// Serial.begin(9600);
// Serial.println("Cool");
}

// Filling the whole strip at once
// 0 - both sides
// 1 - left
// 2 - right
// 3 - front+rear
void FullFill_All(int Side, uint32_t PixelColor) {
  switch (Side) {
    case 1:
      for(int i=0; i<PIXEL_COUNT_REAR; i++) {
        strip_RL.setPixelColor(i, PixelColor);
      }
      for(int i=0; i<PIXEL_COUNT_FRONT; i++) {
        strip_FL.setPixelColor(i, PixelColor);
      }
      strip_RL.show();
      strip_FL.show();
    break;
    
    case 2:
      for(int i=0; i<PIXEL_COUNT_REAR; i++) {
        strip_RR.setPixelColor(i, PixelColor);
      }
      for(int i=0; i<PIXEL_COUNT_FRONT; i++) {
        strip_FR.setPixelColor(i, PixelColor);
      }
      strip_RR.show();
      strip_FR.show();
    break;

    case 3:
      for(int i=0; i<PIXEL_COUNT_REAR; i++) {
        strip_RL.setPixelColor(i, PixelColor);
        strip_RR.setPixelColor(i, PixelColor);
      }
      for(int i=0; i<PIXEL_COUNT_FRONT; i++) {
        strip_FL.setPixelColor(i, PixelColor);
        strip_FR.setPixelColor(i, PixelColor);
      }
      strip_RL.show();
      strip_RR.show();
      strip_FL.show();
      strip_FR.show();
    break;

    default:
      for(int i=0; i<PIXEL_COUNT_REAR; i++) {
        strip_RL.setPixelColor(i, PixelColor);
        strip_RR.setPixelColor(i, PixelColor);
      }
      strip_RL.show();
      strip_RR.show();
    break;
  }
}

// This will make a three fast flashes in orange color. This will be turned on by our hazard lights switch, so the Lenght is just for testing
void Flashing_Hazard(int Lenght) {
  FullFill_All(3, ColorOFF);
  for(int i=0; i<Lenght; i++) {
    for(int j=0; j<4; j++) {
      FullFill_All(3, ColorFLASH);
      delay(60);
      FullFill_All(3, ColorOFF);
      delay(40);
    }
  FullFill_All(3, ColorOFF);
  delay(700);
  }
}

// Left turn signal
void Left_Turn() {
  FullFill_All(1, ColorOFF);
  FullFill_All(1, ColorTURN);
  delay(800);
  FullFill_All(1, ColorOFF);
  delay(600);
}

// Right turn signal
void Right_Turn() {
  FullFill_All(2, ColorOFF);
  FullFill_All(2, ColorTURN);
  delay(800);
  FullFill_All(2, ColorOFF);
  delay(600);
}

// This is a fancy startup effect
void StartMeUp() {
  int k;
  FullFill_All(3, ColorOFF);
  int ThisDelay = 250;
  for(int j=0; j<3; j++) {
    for(int i=0; i<PIXEL_COUNT_REAR; i++) {
      if ((j==0) || (j==2)) {
       k=PIXEL_COUNT_REAR-i;
      } else {
        k=i;
      }
      FullFill_All(3, ColorOFF);
      strip_RL.setPixelColor(i, ColorSTART);
      strip_RR.setPixelColor(PIXEL_COUNT_REAR-i-1, ColorSTART);
      strip_FL.setPixelColor(k+2, ColorSTART);
      strip_FR.setPixelColor(PIXEL_COUNT_REAR-k, ColorSTART);
      ThisDelay=ThisDelay-6;
      strip_RL.show();
      strip_RR.show();
      strip_FL.show();
      strip_FR.show();
      delay(ThisDelay);
    }
    FullFill_All(3, ColorOFF);
  }
  for(int i=0; i<PIXEL_COUNT_REAR; i++) {
    strip_RL.setPixelColor(i, ColorSTART);
    strip_RR.setPixelColor(PIXEL_COUNT_REAR-i, ColorSTART);
    strip_FL.setPixelColor(i+2, ColorSTART);
    strip_FR.setPixelColor(PIXEL_COUNT_REAR-i, ColorSTART);
    ThisDelay=ThisDelay-10;
    strip_RL.show();
    strip_RR.show();
    strip_FL.show();
    strip_FR.show();
    delay(50);
  }
  FullFill_All(3, ColorSTART);
  delay(1000);
  FullFill_All(3, ColorOFF);
}

void loop() {
  // put your main code here, to run repeatedly:

// Startup lights
 StartMeUp();
 delay(1000);

// Hazard lights
 Flashing_Hazard(10);

// Left turn signal
 for (int i=0; i<6; i++) {
  Left_Turn();
 }


// just to know it's over here...
 FullFill_All(3,ColorBLUE);
 delay(5000);
}
