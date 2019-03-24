/*
 * TODO
 * Press any button to go to selection of algorithms mode
 * Light up different pixel based on the the selection when in select algorithm mode.
 * Press third button run? Wait a few seconds? Press both?
 * Use RoboRIO input to select?
 * use EEPROM to store settings
 */
#include "FastLED.h"

#define ARRAY_SIZE 25
CRGB leds[ARRAY_SIZE];
#define PIN 7

#define SORT_BRIGHTNESS 0x10
#define SINGLE_PIXEL_BRIGHTNESS 0x10
#define RAINBOW_BRIGHTNESS 0x10

uint8_t getRandomHue(int numberOfColors)
{
  return (random(numberOfColors)/(double)numberOfColors)*0xFF;
}

CRGB getRandomColor(int numberOfColors, int saturation, int value)
{
  return CHSV(getRandomHue(numberOfColors), saturation, value);
}

void randomize() {
  for (int i = 0; i < ARRAY_SIZE; i++) {
    uint8_t hue = getRandomHue(ARRAY_SIZE);
    leds[i].setHSV(hue, 255, SORT_BRIGHTNESS);
  }
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
  delay(5000);
}

void shift()
{
  CRGB tmpColor = leds[ARRAY_SIZE - 1];
  for (int i = ARRAY_SIZE - 1; i > 0; i--) {
    leds[i] = leds[i-1];
  }
  leds[0] = tmpColor;
  FastLED.show();
}

void rainbow(int rainbowPixels)
{
  for (int i = 0; i < ARRAY_SIZE; i++) {
    leds[i].setHSV((i%rainbowPixels/(double)rainbowPixels)*0xFF, 0xFF, RAINBOW_BRIGHTNESS);
    FastLED.show();
  }
}

void marquee(CRGB color, int onPixels, int offPixels)
{
  for (int i = 0; i < ARRAY_SIZE; i += onPixels + offPixels) {
    for (int j = 0; j < onPixels; j++)
    {
      leds[i+j] = color;
    }
  }
  FastLED.show();
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

  //rainbow(4);
  //leds[0] = getRandomColor(16, 255, SINGLE_PIXEL_BRIGHTNESS);
  marquee(CHSV(0, 0x00, SINGLE_PIXEL_BRIGHTNESS), 2, 1);
}

void loop() {
  //insertionSort();
  shift();
  delay(500);
}
