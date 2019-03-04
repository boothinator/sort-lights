/*
 * TODO
 * Press any button to go to selection of algorithms mode
 * Light up different pixel based on the the selection when in select algorithm mode.
 * Press third button run? Wait a few seconds? Press both?
 * Use RoboRIO input to select?
 */

#include <Adafruit_NeoPixel.h>
#include <limits.h>

#define ARRAY_SIZE 144

#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(ARRAY_SIZE, PIN, NEO_GRB + NEO_KHZ800);

void randomize() {
  for (int i = 0; i < ARRAY_SIZE; i++) {
    strip.setPixelColor(i, random(UINT_MAX));
  }  
}

void setup() {
  Serial.begin(9600);

  // if analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  randomSeed(analogRead(0));
  
  strip.begin();
}

void insertionSort()
{
  randomize();
  strip.display();
  
  for (int i = 1; i < ARRAY_SIZE; i++) {
    for (int j = i; j >= 0; j--){
      if (strip.getPixelColor(j - 1) > strip.getPixelColor(j)) {
        uint32_t tmp = strip.getPixelColor(j - 1);
        strip.setPixelColor(j - 1, strip.getPixelColor(j));
        strip.setPixelColor(j, tmp);
        strip.display();
      }
    }
  }
}

void loop() {
  while (true) {
    insertionSort();
  }
}
