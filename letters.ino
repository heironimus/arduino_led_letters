#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(50, PIN, NEO_RGB + NEO_KHZ800);

#define NUM_LETTERS 26
#define POINTS_PER_LETTER 20
uint8_t Alphabet[NUM_LETTERS][POINTS_PER_LETTER] = {
  { 3, 4, 5, 9,13,16,20,23,24,25,26,27,30,34,37,41,44,48, 0, 0}, // A
  { 3, 4, 5, 6, 9,13,16,20,23,24,25,26,30,34,37,41,45,46,47,48}, // B
  { 3, 4, 5, 9,13,20,23,34,37,41,45,46,47, 0, 0, 0, 0, 0, 0, 0}, // C
  { 3, 4, 5, 6, 9,13,16,20,23,27,30,34,30,37,41,45,46,47,48, 0}, // D
  { 2, 3, 4, 5, 6, 9,20,23,24,25,26,34,37,44,45,46,47,48, 0, 0}, // E
  { 2, 3, 4, 5, 6, 9,20,23,24,25,26,34,37,48, 0, 0, 0, 0, 0, 0}, // F
  { 3, 4, 5, 9,13,20,23,26,25,27,30,34,30,37,41,45,46,47, 0, 0}, // G
  { 2, 6, 9,13,16,20,23,24,25,26,27,30,34,37,41,44,48, 0, 0, 0}, // H
  { 3, 4, 5,11,18,25,32,39,45,46,47, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // I
  { 2,13,16,27,30,34,30,37,41,45,46,47, 0, 0, 0, 0, 0, 0, 0, 0}, // J
  { 6, 9,20,23,34,39,48,19,11, 3,33,37,45, 0, 0, 0, 0, 0, 0, 0}, // K
  { 6, 9,20,23,34,37,44,45,46,47,48, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // L
  { 3, 5, 9,11,13,16,18,20,23,25,27,30,32,34,37,39,41,44,48, 0}, // M
  { 2, 6, 9,10,13,16,18,20,23,25,27,30,32,34,37,40,41,44,48, 0}, // N
  { 3, 4, 5, 9,13,16,20,23,27,30,34,37,41,45,46,47, 0, 0, 0, 0}, // O
  { 3, 4, 5, 6, 9,13,16,20,23,24,25,26,34,37,48, 0, 0, 0, 0, 0}, // P
  { 3, 4, 5, 9,13,16,20,23,27,30,34,30,32,37,40,41,43,45,46,47}, // Q
  { 3, 4, 5, 6, 9,13,16,20,23,24,25,26,31,34,37,41,44,48, 0, 0}, // R
  { 3, 4, 5, 9,13,20,24,25,26,30,37,41,45,46,47, 0, 0, 0, 0, 0}, // S
  { 3, 4, 5, 9,13,16,20,23,24,25,26,27,30,34,37,41,44,48, 0, 0}, // A
  { 2, 6, 9,13,16,20,23,27,30,34,30,37,41,45,46,47, 0, 0, 0, 0}, // U
  { 3, 4, 5, 9,13,16,20,23,24,25,26,27,30,34,37,41,44,48, 0, 0}, // A
  { 9,13,16,18,20,23,25,27,30,32,34,37,39,41,45,47, 0, 0, 0, 0}, // W
  { 3, 4, 5, 9,13,16,20,23,24,25,26,27,30,34,37,41,44,48, 0, 0}, // A
  { 3, 4, 5, 9,13,16,20,23,24,25,26,27,30,34,37,41,44,48, 0, 0}, // A
  { 3, 4, 5, 9,13,16,20,23,24,25,26,27,30,34,37,41,44,48, 0, 0}  // A
};

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  Serial.begin(115200);  
  Serial.println("--- Start Serial Monitor SEND_RCVE ---");
  Serial.println(); 
}

void loop() {
  if (Serial.available() > 0)
  {
    //showLetter(Serial.read());
    letterRainbowCycle(Serial.read(), 5);
  }
}

void showLetter(uint8_t letter)
{
  uint8_t letterOffset = getLetterOffset(letter);
  // clear all pixels
  for(uint16_t i=0; i<strip.numPixels(); i++) {    
    strip.setPixelColor(i, strip.Color(0, 0, 50));
  }
  strip.show();
  delay(10);

  if(letterOffset != 255)
  {
    for(uint16_t i=0; i<POINTS_PER_LETTER; i++) {    
      strip.setPixelColor(Alphabet[letterOffset][i], strip.Color(255, 0, 0));
    }
  }
  strip.show();
}

uint8_t getLetterOffset(uint8_t letter)
{
  if (letter <= 'z' && letter >= 'a')
  {
    return letter - 'a';
  }
  if (letter <= 'Z' && letter >= 'A')
  {
    return letter - 'A';
  }  
  return 255;
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
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
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) { //  all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

void letterRainbowCycle(uint8_t letter, uint8_t wait) {
  uint16_t i, j;


  uint8_t letterOffset = getLetterOffset(letter);
  uint8_t brightness;
  // clear all pixels
  strip.clear();

  if(letterOffset != 255)
  {
    for(j=0; j<256; j++) { //  all colors on wheel
      for(uint16_t i=0; i<POINTS_PER_LETTER; i++) {    
        strip.setPixelColor(Alphabet[letterOffset][i], Wheel(((i * 256 / strip.numPixels()) + j) & 255));
      }
      if(j < 128)
      {
        brightness = j;
      }
      else
      {
        brightness = 255 - j;
      }
      strip.setBrightness(brightness);
      strip.show();
      delay(wait);
    }

  }
  strip.show();

}

// Slightly different, this makes the rainbow equally distributed throughout
void grayCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) { //  all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, GrayWheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
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
void theaterChaseRainbow(uint8_t wait) {
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

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
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

// Input a value 0 to 255 to get a grayscale value.
uint32_t GrayWheel(byte WheelPos) {
  WheelPos /= 16;
  WheelPos *= WheelPos;
  if(WheelPos < 128) {
    return strip.Color(WheelPos, WheelPos, WheelPos);
  }
  return strip.Color(255 - WheelPos, 255 - WheelPos, 255 - WheelPos);
}
