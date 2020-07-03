/***************************************************
  This is our touchscreen painting example for the Adafruit HX8357 Breakout
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


// These are the four touchscreen analog pins
#define YP A2  // must be an analog pin, use "An" notation!
#define XM A3  // must be an analog pin, use "An" notation!
#define YM 7   // can be a digital pin
#define XP 8   // can be a digital pin

// This is calibration data for the raw touch data to the screen coordinates
// Calibrated within +/- 10 pixals 05/25/2020
#define TS_MINX 400
#define TS_MINY 182
#define TS_MAXX 827
#define TS_MAXY 836

#define MINPRESSURE 10
#define MAXPRESSURE 1000

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 292);

void Update_TouchScreen() {
 // Serial.print("in touch screen");
  TSPoint p = ts.getPoint();
  if (p.z < MINPRESSURE || (p.z > MAXPRESSURE) || (p.y == 1023)) {
    return;
  }

  Switch_Pressed = true;
  //Serial.print("Xraw = "); Serial.print(p.x);
  //Serial.print("\tYraw = "); Serial.print(p.y);
  //Serial.print("\tPressureraw = "); Serial.println(p.z);

  // Scale from ~0->1000 to tft.width using the calibration #'s
  Pixel_Y = map(p.x, TS_MINX, TS_MAXX, 320, 0); //inverted to get Draw Pixal in same orientation with Touch screen
  Pixel_X = map(p.y, TS_MINY, TS_MAXY, 0, 480);

 //   Serial.print("X = "); Serial.print(Pixel_X);
 //   Serial.print("\tY = "); Serial.print(Pixel_Y);
//    Serial.print("\tPressure = "); Serial.println(p.z);

  // Check pressed Zone

  // Upstairs
  /*
    Serial.println (Upstairs.x);
    Serial.println ((Upstairs.x + Upstairs.Width));
    Serial.println (Upstairs.y);
    Serial.println ((Upstairs.y + Upstairs.Height));
  */

  if ((Pixel_X >= Upstairs.x) && (Pixel_X <= (Upstairs.x + Upstairs.Width)) && (Pixel_Y >= Upstairs.y) && (Pixel_Y <= (Upstairs.y + Upstairs.Height))) {
    Serial.println ("Upstairs");
  }

  else if ((Pixel_X >= Downstairs.x) && (Pixel_X <= (Downstairs.x + Downstairs.Width)) && (Pixel_Y >= Downstairs.y) && (Pixel_Y <= (Downstairs.y + Downstairs.Height))) {
    Serial.println ("Downstairs");
  }

  else if ((Pixel_X >= Outside.x) && (Pixel_X <= (Outside.x + Outside.Width)) && (Pixel_Y >= Outside.y) && (Pixel_Y <= (Outside.y + Outside.Height))) {
    Serial.println ("Outside");
  }
  else if ((Pixel_X >= IGL.x) && (Pixel_X <= (IGL.x + IGL.Width)) && (Pixel_Y >= IGL.y) && (Pixel_Y <= (IGL.y + IGL.Height))) {
    Serial.println ("IGL");
  }
  else if ((Pixel_X >= Weather.x) && (Pixel_X <= (Weather.x + Weather.Width)) && (Pixel_Y >= Weather.y) && (Pixel_Y <= (Weather.y + Weather.Height))) {
    Serial.println ("Weather");
  }

  else if ((Pixel_X >= UpstairsSet.x) && (Pixel_X <= (UpstairsSet.x + UpstairsSet.Width)) && (Pixel_Y >= UpstairsSet.y) && (Pixel_Y <= (UpstairsSet.y + UpstairsSet.Height))) {
    Serial.println ("Up Stairs Set");
  }

  else if ((Pixel_X >= DownstairsSet.x) && (Pixel_X <= (DownstairsSet.x + DownstairsSet.Width)) && (Pixel_Y >= DownstairsSet.y) && (Pixel_Y <= (DownstairsSet.y + DownstairsSet.Height))) {
    Serial.println ("Down Stairs Set");
  }
  else if ((Pixel_X >= Timer.x) && (Pixel_X <= (Timer.x + Timer.Width)) && (Pixel_Y >= Timer.y) && (Pixel_Y <= (Timer.y + Timer.Height))) {
    Serial.println ("Timer");
  }

  else if ((Pixel_X >= Stack.x) && (Pixel_X <= (Stack.x + Stack.Width)) && (Pixel_Y >= Stack.y) && (Pixel_Y <= (Stack.y + Stack.Height))) {
    Serial.println ("Stack");
  }
  else if ((Pixel_X >= Fan.x) && (Pixel_X <= (Fan.x + Fan.Width)) && (Pixel_Y >= Fan.y) && (Pixel_Y <= (Fan.y + Fan.Height))) {
    Serial.println ("Fan");
  }

  else if ((Pixel_X >= Damper.x) && (Pixel_X <= (Damper.x + Damper.Width)) && (Pixel_Y >= Damper.y) && (Pixel_Y <= (Damper.y + Damper.Height))) {
    Serial.println ("Damper");
  }
    else if ((Pixel_X >= DownArrow.x) && (Pixel_X <= (DownArrow.x + DownArrow.Width)) && (Pixel_Y >= DownArrow.y) && (Pixel_Y <= (DownArrow.y + DownArrow.Height))) {
    Serial.println ("DownArrow");
  }
    else if ((Pixel_X >= UpArrow.x) && (Pixel_X <= (UpArrow.x + UpArrow.Width)) && (Pixel_Y >= UpArrow.y) && (Pixel_Y <= (UpArrow.y + UpArrow.Height))) {
    Serial.println ("UpArrow");
  }
  else {
    Serial.println ("missed button");
  }

  while (Switch_Pressed == true) {
    TSPoint p = ts.getPoint();
    if (p.z < MINPRESSURE  ) Switch_Pressed = false;
    delay (200);
  }

}
