#include "FastLED.h"
#include <elapsedMillis.h>

// Pride2015
// Animated, ever-changing rainbows.
// by Mark Kriegsman

#if FASTLED_VERSION < 3001000
#error "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN    2
//#define CLK_PIN   4
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
#define NUM_LEDS    22
#define BRIGHTNESS  255

CRGBArray<NUM_LEDS> leds;

elapsedMillis timer0;
int runIndex = 0;
int indexMap = 0;
float timerMap = 0;
int loopJump = 0;
elapsedMillis timer1;

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

  indexMap = map(runIndex, 0, NUM_LEDS, 0, 255);
  
  
  timerMap = timer1/2000.00000000;
  Serial.println(abs(255*sin(timerMap)));
  
  leds[runIndex] = CHSV(indexMap+loopJump, abs(255*sin(timerMap)), 255);

  runIndex++;
  loopJump += 10;

  if (runIndex >= NUM_LEDS) {
    runIndex = 0;
  }

  if (timerMap >= 2*3.14*1000) {
    timer1 = 0;
  }

  if (loopJump > 255) {
    loopJump = 0;
  }
  
  FastLED.show();

  while (timer0 < 69) {}
  timer0 = 0;
}
