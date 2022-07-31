#ifndef LED_H
#define LED_H

#include <Adafruit_NeoPixel.h>
#include <string>

using namespace std;

class LedStrip
{
// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.
public:
    LedStrip() = default;
    void init(uint8_t LED_COUNT, uint8_t PIN);
    void init(Adafruit_NeoPixel& strip);
    void setMode(string new_mode);
    void lightLedStrip();
    void defaultCombo();
    // Fill the dots one after the other with a color
    void colorWipe(uint32_t c, uint8_t wait);
    // rainbow light effects
    void rainbow(uint8_t wait);
    // Slightly different, this makes the rainbow equally distributed throughout
    void rainbowCycle(uint8_t wait);
    //Theatre-style crawling lights.
    void theaterChase(uint32_t c, uint8_t wait);
    //Theatre-style crawling lights with rainbow effect
    void theaterChaseRainbow(uint8_t wait);
    uint32_t configureColor(uint8_t red, uint8_t green, uint8_t blue);
    // Input a value 0 to 255 to get a color value.
    // The colours are a transition r - g - b - back to r.
    uint32_t Wheel(byte WheelPos);
private:
    Adafruit_NeoPixel strip;
    string mode = "off";
};

#endif