#include "FastLED.h"

/*
 * This program linearly maps the range of possible hues (0-255) 
 * onto your neopixel strip.
 */

#if FASTLED_VERSION < 3001000
#error "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN    17      // Set this to whatever Arduino pin DIN is connected to
//#define CLK_PIN   4
#define LED_TYPE    WS2812  // This is the type of chip inside of our addressable LED Strip
#define COLOR_ORDER GRB     // Neopixels apparently like commands sent in "GRB" order, so we specify this so we can still write in "RGB" order
#define NUM_LEDS    240     // Set this to the number of LED "pixels" in your strip
#define BRIGHTNESS  100      // This is the initial brightness (max value is 255)


CRGB leds[NUM_LEDS]; // this initializes the array containing all of the LEDs

elapsedMillis timer0; // declare timer variable for loop timing
int i = 0; // indexing variable

void setup() { // setup code should be the same for nearly every FastLED program
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
  timer0 = 0;
  FastLED.clear(); // clears any previous values written to the pixels
  
  leds[i] = CHSV((i * 255 / NUM_LEDS), 255, 255);
  
  FastLED.show();  // turns on all of the pixels with whatever settings you instructed
  i++;
  if (i>NUM_LEDS) {
    i = 0;
  }
  while(timer0 < 10) {} // different way of doing a 50 ms delay
}
