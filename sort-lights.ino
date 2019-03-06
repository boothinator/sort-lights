/*
 * TODO
 * Press any button to go to selection of algorithms mode
 * Light up different pixel based on the the selection when in select algorithm mode.
 * Press third button run? Wait a few seconds? Press both?
 * Use RoboRIO input to select?
 * use EEPROM to store settings
 */
#include "FastLED.h"

#define ARRAY_SIZE 10
CRGB leds[ARRAY_SIZE];
#define PIN 7

#define SORT_BRIGHTNESS 0x10

void randomize() {
  for (int i = 0; i < ARRAY_SIZE; i++) {
    uint8_t hue = (random(ARRAY_SIZE)/(double)ARRAY_SIZE)*0xFF;
    leds[i].setHSV(hue, 255, SORT_BRIGHTNESS);
  }
}

void setup() {
  Serial.begin(9600);

  // if analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  randomSeed(analogRead(0));
  
  FastLED.addLeds<NEOPIXEL, PIN>(leds, ARRAY_SIZE);
  FastLED.show();
}

void blink(int i, int j, int times)
{
  CRGB color_i = leds[i];
  CRGB color_j = leds[j];
  for (int k = 0; k < times; k++) {
    leds[i] = 0x000000;
    leds[j] = 0x000000;
    FastLED.show();
    delay(100);
    leds[i] = color_i;
    leds[j] = color_j;
    FastLED.show();
    delay(100);
  }
}

void insertionSort()
{
  randomize();
  FastLED.show();
  
  for (int i = 1; i < ARRAY_SIZE; i++) {
    for (int j = i; j >= 0; j--){
      blink(j-1, j, 1);
      
      if (rgb2hsv_approximate(leds[j - 1]).hue > rgb2hsv_approximate(leds[j]).hue) {
        //blink(j-1, j, 5);
        CRGB tmp = leds[j - 1];
        leds[j - 1] = leds[j];
        leds[j] = tmp;
        FastLED.show();
      }
      delay(1000);
    }
    delay(1000);
  }
}

void singlePixel(CRGB color)
{
  Serial.print(color, HEX);
  leds[0] = color;
  FastLED.show();
  delay(500);
  for (int i = 1; i < ARRAY_SIZE; i++) {
    leds[i - 1] = 0;
    leds[i] = color;
    FastLED.show();
    delay(500);
  }
  leds[ARRAY_SIZE - 1] = 0;
  FastLED.show();
}

void loop() {
  insertionSort();
  delay(5000);
  //singlePixel(CHSV(random(0xFF), 255, 255));
}
