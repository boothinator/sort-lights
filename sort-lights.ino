/*
 * TODO
 * Press any button to go to selection of algorithms mode
 * Light up different pixel based on the the selection when in select algorithm mode.
 * Press third button run? Wait a few seconds? Press both?
 * Use RoboRIO input to select?
 * use EEPROM to store settings
 */

#include <Adafruit_NeoPixel.h>
#include <limits.h>

#define ARRAY_SIZE 10

#define PIN 7

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
    strip.setPixelColor(i, random(0xFFFFFF));
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
  strip.show();
}

void blink(int i, int j)
{
  uint32_t color_i = strip.getPixelColor(i);
  uint32_t color_j = strip.getPixelColor(j);
  for (int k = 0; k < 5; k++) {
    strip.setPixelColor(i, 0xFFFFFF);
    strip.setPixelColor(j, 0xFFFFFF);
    strip.show();
    delay(100);
    strip.setPixelColor(i, color_i);
    strip.setPixelColor(j, color_j);
    strip.show();
    delay(100);
  }
}

void insertionSort()
{
  randomize();
  strip.show();
  
  for (int i = 1; i < ARRAY_SIZE; i++) {
    for (int j = i; j >= 0; j--){
      if (strip.getPixelColor(j - 1) > strip.getPixelColor(j)) {
        blink(j-1, j);
        uint32_t tmp = strip.getPixelColor(j - 1);
        strip.setPixelColor(j - 1, strip.getPixelColor(j));
        strip.setPixelColor(j, tmp);
        strip.show();
        delay(500);
      }
    }
  }
}

void singlePixel(uint32_t color)
{
  Serial.print(color, HEX);
  strip.setPixelColor(0, color);
  strip.show();
  delay(500);
  for (int i = 1; i < ARRAY_SIZE; i++) {
    strip.setPixelColor(i - 1, 0);
    strip.setPixelColor(i, color);
    strip.show();
    delay(500);
  }
  strip.setPixelColor(ARRAY_SIZE - 1, 0);
  strip.show();
}

void loop() {
  //insertionSort();
  singlePixel(random(0xFFFFFF));
}
