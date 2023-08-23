#include "FastLED.h"

// Pride2015
// Animated, ever-changing rainbows.
// by Mark Kriegsman

#if FASTLED_VERSION < 3001000
#error "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN    3
//#define CLK_PIN   4
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
#define NUM_LEDS    40
#define BRIGHTNESS  255

CRGBArray<NUM_LEDS> leds;

int potR;
int potG;
int potB;

int potMapR;
int potMapG;
int potMapB;

void setup() {
  Serial.begin(9600);
  delay(3000); // 3 second delay for recovery
  
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS)
    .setCorrection(TypicalLEDStrip)
    .setDither(BRIGHTNESS < 255);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
}


void loop()
{
  FastLED.clear();
  
  potR = analogRead(A0);
  potG = analogRead(A1);
  potB = analogRead(A2);

  potMapR = map(potR, 0, 1027, 0, 255);
  potMapG = map(potG, 0, 1027, 0, 255);
  potMapB = map(potB, 0, 1027, 0, 255);

  for(int i=0; i<NUM_LEDS; i++) {
    leds[i] = CRGB(potMapR, potMapG, potMapB);
  }

  Serial.print(potMapR);
  Serial.print("\t");
  Serial.print(potMapG);
  Serial.print("\t");
  Serial.println(potMapB); 
  
  FastLED.show();

  delay(33);
}
