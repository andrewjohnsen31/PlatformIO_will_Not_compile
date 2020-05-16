/***************************************************
  This is our library for the Adafruit HX8357D Breakout
  ----> http://www.adafruit.com/products/2050

  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/
#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

//#include <mallox.h>
#include "Adafruit_GFX.h"
#include "Adafruit_HX8357.h"


void setup() {
  Serial.begin(9600);
  Serial.println("HX8357D Test!"); 

 
  Serial.println(F("Done!"));
}


void loop(void) {
  
  
}

