#include <Adafruit_NeoPixel.h>
#define PIXEL_COUNT_REAR 12
#define PIXEL_COUNT_FRONT 15
#define PIXEL_PIN_REAR_LEFT 7
#define PIXEL_PIN_REAR_RIGHT 6
#define PIXEL_PIN_FRONT_LEFT 9
#define PIXEL_PIN_FRONT_RIGHT 8
#define TOUCH01_VCC_PIN 13
#define TOUCH01_PIN 12
#define TOUCH02_VCC_PIN 11
#define TOUCH02_PIN 10

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
uint32_t ColorHEADLIGHTS;
uint32_t ColorTAILLIGHTS;
uint32_t ColorBRAKELIGHT;
int DayTimeBrightness;
int NightTimeBrightness;
int touch01_value;
int touch02_value;
int running_lights;

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
 DayTimeBrightness=50;
 NightTimeBrightness=200;
 
 strip_RL.setBrightness(DayTimeBrightness);
 strip_RR.setBrightness(DayTimeBrightness);
 strip_FL.setBrightness(DayTimeBrightness);
 strip_FR.setBrightness(DayTimeBrightness);

// Lets set the colors here and use them anywhere ;)
// my strip has GREEN - RED - BLUE setup
 ColorGREEN=strip_RL.Color(255,0,0);
 ColorRED=strip_RL.Color(0,255,0);
 ColorBLUE=strip_RL.Color(0,0,255);
 ColorOFF=strip_RL.Color(0,0,0);
 ColorFLASH=strip_RL.Color(40,255,0);
 ColorSTART=strip_RL.Color(200,50,100);
 ColorTURN=strip_RL.Color(50,250,0);
 ColorHEADLIGHTS=strip_RL.Color(250,250,250);
 ColorTAILLIGHTS=strip_RL.Color(10,180,10);
 ColorBRAKELIGHT=strip_RL.Color(0,250,0);

 pinMode(TOUCH01_VCC_PIN, OUTPUT);
 pinMode(TOUCH01_PIN, INPUT);
 digitalWrite(TOUCH01_VCC_PIN, HIGH); // power ON touch 01 button

 pinMode(TOUCH02_VCC_PIN, OUTPUT);
 pinMode(TOUCH02_PIN, INPUT);
 digitalWrite(TOUCH02_VCC_PIN, HIGH); // power ON touch 02 button

 running_lights=0;

// Startup lights
 StartMeUp();
}

void SetBrightness(int Value) {
 if (Value>0) {
  strip_RL.setBrightness(Value);
  strip_RR.setBrightness(Value);
  strip_FL.setBrightness(Value);
  strip_FR.setBrightness(Value);  
 }
}

// Filling the whole strip at once
// 0 - rear (default)
// 1 - left
// 2 - right
// 3 - front+rear
// 4 - front
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

    case 4:
      for(int i=0; i<PIXEL_COUNT_FRONT; i++) {
        strip_FL.setPixelColor(i, PixelColor);
        strip_FR.setPixelColor(i, PixelColor);
      }
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

// Brake signal, three fast blinks, no pause
void Brake_Light() {
  FullFill_All(0, ColorOFF);
  for(int i=0; i<3; i++) {
    FullFill_All(0, ColorBRAKELIGHT);
    delay(100);
    FullFill_All(0, ColorOFF);
    delay(80);
  FullFill_All(0, ColorOFF);
  }
}

// Left turn signal, one blink with pause
void Left_Turn() {
  FullFill_All(1, ColorOFF);
  FullFill_All(1, ColorTURN);
  delay(800);
  FullFill_All(1, ColorOFF);
  delay(600);
}

// Right turn signal, one blink with pause
void Right_Turn() {
  FullFill_All(2, ColorOFF);
  FullFill_All(2, ColorTURN);
  delay(800);
  FullFill_All(2, ColorOFF);
  delay(600);
}

// This is a fancy startup effect, will be played everytime Arduino boots up
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
      strip_FL.setPixelColor(k, ColorSTART);
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
    strip_FL.setPixelColor(i, ColorSTART);
    strip_FR.setPixelColor(PIXEL_COUNT_REAR-i+2, ColorSTART);
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
int prepare_light;

// Lets read both buttons
 touch01_value = digitalRead(TOUCH01_PIN);
 touch02_value = digitalRead(TOUCH02_PIN);

// We will put both values in single variable for easier evaluation
 prepare_light=touch01_value+(10*touch02_value);

// Lets switch the lights on...
 switch (prepare_light) {
  case 0:
  break;

// If button 1 is pressed, and button 2 was active we turn off button 2 (just
// because of the backlight) and turn on button 1 lights
  case 1:
   if (running_lights==10) {
    digitalWrite(TOUCH02_VCC_PIN, LOW); // power OFF touch 01 button
   }
   running_lights=1;
   Left_Turn();
   digitalWrite(TOUCH02_VCC_PIN, HIGH); // power ON touch 01 button
  break;

// If button 2 is pressed, and button 1 was active we turn off button 1 (just
// because of the backlight) and turn on button 2 lights
  case 10:
   if (running_lights==1) {
    digitalWrite(TOUCH01_VCC_PIN, LOW); // power OFF touch 01 button
   }
   running_lights=10;
   Right_Turn();
   digitalWrite(TOUCH01_VCC_PIN, HIGH); // power ON touch 01 button
  break;


// In case we pressed second button while the first one was active we will
// turn off the first button and activate the routine that will light the
// second action (the other turn signal)
  default:
  case 11:
   switch (running_lights) {
    case 1:
     digitalWrite(TOUCH01_VCC_PIN, LOW); // power OFF touch 01 button
     running_lights=10;
     Right_Turn();
     digitalWrite(TOUCH01_VCC_PIN, HIGH); // power ON touch 01 button
    break;
    
    case 10:
     digitalWrite(TOUCH02_VCC_PIN, LOW); // power OFF touch 01 button
     running_lights=1;
     Left_Turn();
     digitalWrite(TOUCH02_VCC_PIN, HIGH); // power ON touch 01 button
    break;
    
    default:
    break;
   }
  break;
 }

// Hazard lights
// Flashing_Hazard(3);

// Left turn signal
// for (int i=0; i<4; i++) {
//  Left_Turn();
// }

// Right turn signal
// for (int i=0; i<4; i++) {
//  Right_Turn();
// }

// Turn on driving lights - daytime
// SetBrightness(DayTimeBrightness);
// FullFill_All(0,ColorTAILLIGHTS);
// FullFill_All(4,ColorHEADLIGHTS);
// delay(5000);
 
// Turn on driving lights - nighttime
// SetBrightness(NightTimeBrightness);
// FullFill_All(0,ColorTAILLIGHTS);
// FullFill_All(4,ColorHEADLIGHTS);
// delay(5000);

// Brake light
// for (int i=0; i<4; i++) {
//  Brake_Light();
// }

// just to know it's over here -> turn on calm blue color for 5 secs...
// SetBrightness(25);
// FullFill_All(3,ColorBLUE);
// digitalWrite(TOUCH01_VCC_PIN, LOW); // power OFF touch 01 button
// delay(5000);
}
