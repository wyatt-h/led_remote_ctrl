#include <string>
#include "led_strip.hpp"
#ifdef __AVR__
  #include <avr/power.h>
#endif

using namespace std;

void LedStrip::init(Adafruit_NeoPixel& strip) {
  // // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  // #if defined (__AVR_ATtiny85__)
  //   if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  // #endif
  // // End of trinket special code

  this->strip = strip;
  this->strip.begin();
  this->strip.setBrightness(50);
  this->strip.show(); // Initialize all pixels to 'off'
}

void LedStrip::init(uint8_t LED_COUNT, uint8_t PIN) {
  // // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  // #if defined (__AVR_ATtiny85__)
  //   if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  // #endif
  // // End of trinket special code

  this->strip = Adafruit_NeoPixel(LED_COUNT, PIN, NEO_GRB + NEO_KHZ800);
  this->strip.begin();
  this->strip.setBrightness(50);
  this->strip.show(); // Initialize all pixels to 'off'
}

void LedStrip::setMode(string new_mode) {
  mode = new_mode;
}

void LedStrip::lightLedStrip() {
  if (mode.compare("wheel") == 0) {
    colorWipe(strip.Color(255, 0, 0), 50);
  } else if (mode.compare("rainbow") == 0) {
    rainbow(20);
  } else if (mode.compare("single") == 0) {
    theaterChase(strip.Color(127,127,127), 50);
  }
}

void LedStrip::defaultCombo() {
  colorWipe(strip.Color(255, 0, 0), 50); // Red
  colorWipe(strip.Color(0, 255, 0), 50); // Green
  colorWipe(strip.Color(0, 0, 255), 50); // Blue
  colorWipe(strip.Color(0, 0, 0, 255), 50); // White RGBW
  // Send a theater pixel chase in...
  theaterChase(strip.Color(127, 127, 127), 50); // White
  theaterChase(strip.Color(127, 0, 0), 50); // Red
  theaterChase(strip.Color(0, 0, 127), 50); // Blue

  rainbow(20);
  rainbowCycle(20);
  theaterChaseRainbow(50);
}

// Fill the dots one after the other with a color
void LedStrip::colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

// rainbow light effects
void LedStrip::rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void LedStrip::rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void LedStrip::theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void LedStrip::theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

uint32_t LedStrip::configureColor(uint8_t red, uint8_t green, uint8_t blue) {
    return strip.Color(red, green, blue);
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t LedStrip::Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}