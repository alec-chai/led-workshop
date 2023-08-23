#include "FastLED.h"
#include <elapsedMillis.h>

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

const int trigPin = 7;
const int echoPin = 6;
long duration1;
int distance1;
//
int potR;
int potG;
int potB;
//
int potMapR;
int potMapG;
int potMapB;

int sonarMap;
elapsedMillis timer0 = 0;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  
  delay(3000); // 3 second delay for recovery
  
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS)
    .setCorrection(TypicalLEDStrip)
    .setDither(BRIGHTNESS < 255);

  FastLED.clear();

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
}


void loop()
{
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration1 = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance1 = duration1 * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance1);
  
    potR = analogRead(A0);
    potG = analogRead(A1);
    potB = analogRead(A2);

    potMapR = map(potR, 0, 1027, 40, 100);
    potMapG = map(potG, 0, 1027, 0, 255);
    potMapB = map(potB, 0, 1027, 0, 255);

  sonarMap = map(distance1, 0, 100, 0, 255);

  for(int i=0; i<(NUM_LEDS); i++) {
    leds[NUM_LEDS-i] = leds[NUM_LEDS-i-1];
  }
  
  leds[0] = CHSV(sonarMap, potMapG, potMapB);

  FastLED.show();
  while (timer0 < potMapR) {}
  timer0 = 0;
}
