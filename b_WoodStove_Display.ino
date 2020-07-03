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


// These are 'flexible' lines that can be changed


// This function opens a Windows Bitmap (BMP) file and
// displays it at the given coordinates.  It's sped up
// by reading many pixels worth of data at a time
// (rather than pixel by pixel).  Increasing the buffer
// size takes more of the Arduino's precious RAM but
// makes loading a little faster.  20 pixels seems a
// good balance.

void UpDate_Display() {

/*
  tft.begin();

  tft.setRotation(1);
  //=================
  tft.fillScreen(HX8357_BLACK);



  Serial.print("Initializing SD card...");
  if (!SD.begin(SD_CS)) {
    Serial.println("failed!");
  }

  while (true) {
    delay(10000);
    Serial.print ("fill screen ");
  }
*/
  tft.setFont(&FreeSansBold12pt7b);// tft.setFont() FreeSansBold12pt7b;
  tft.setTextColor(HX8357_WHITE);
  //========= Up Stairs Temp =======
  tft.setCursor(25, 28);
  tft.setTextSize(1);
  tft.println("Up");
  tft.setCursor(7, 60);
  tft.println("Stairs");
  tft.drawRoundRect(Downstairs.x, Downstairs.y, Downstairs.Width, Downstairs.Height , Downstairs.Round, Touch_Line_Color);
  tft.setTextSize(4);
  tft.fillRoundRect(85, 11, 125, 94, 10, HX8357_BLACK);
  tft.setCursor(95, 88);
  tft.println(LivingRoomTemp / 10);

  //========= Down Stairs Temp =======

  tft.setCursor(5, 137);
  tft.setTextSize(1);
  tft.println("Down");
  tft.setCursor(5, 167);
  tft.println("Stairs");
  tft.drawRoundRect(Upstairs.x, Upstairs.y, Upstairs.Width, Upstairs.Height , Upstairs.Round, Touch_Line_Color);
  tft.setCursor(110, 192);
  tft.setTextSize(4);
  tft.fillRoundRect(85, 115, 125, 94, 10, HX8357_BLACK);
  tft.setCursor(95, 192);
  tft.println(BasementRoomTemp / 10);

  //========= Out-Side Temp =======

  tft.setCursor(15, 241);
  tft.setTextSize(1);
  tft.println("Out-");
  tft.setCursor(12, 266);
  tft.println("Side");
  tft.drawRoundRect(Outside.x, Outside.y, Outside.Width, Outside.Height , Outside.Round, Touch_Line_Color);
  tft.setTextSize(4);
  tft.fillRoundRect(85, 219, 125, 94, 10, HX8357_BLACK);
  tft.setCursor(95, 296);
  tft.println(temperature[0] / 10);
  /*
  while (true) {
    delay(10000);
    Serial.print ("end before bitmap weather");
  }
  */
  
  bmpDraw("Partly.bmp", 214, 240);
  
  tft.drawRoundRect(Weather.x, Weather.y, Weather.Width, Weather.Height , Weather.Round, Touch_Line_Color);

  //=========== IGL ============
  bmpDraw("IGL50_75.bmp", 5, 275);
  tft.drawRoundRect(IGL.x, IGL.y, IGL.Width, IGL.Height , IGL.Round, Touch_Line_Color);

  //=========== Up Stairs Set Point ==========
  tft.setCursor(228, 25);
  tft.setTextSize(1);
  tft.println("Set");
  tft.setCursor(220, 48);
  tft.println("Point");
  tft.fillRoundRect(212, 60, 79, 48, 10, HX8357_BLACK);
  tft.drawRoundRect(UpstairsSet.x, UpstairsSet.y, UpstairsSet.Width, UpstairsSet.Height , UpstairsSet.Round, Touch_Line_Color);
  tft.setCursor(224, 99);
  tft.setTextSize(2);
  tft.println(DesiredRoomTemp / 10);

  //=========== Down Stairs Set Point ==========
  tft.fillRoundRect(212, 117, 79, 48, 10, HX8357_BLACK);
  tft.drawRoundRect(DownstairsSet.x, DownstairsSet.y, DownstairsSet.Width, DownstairsSet.Height , DownstairsSet.Round, Touch_Line_Color);
  tft.setCursor(224, 156);
  tft.setTextSize(2);
  tft.println("88");

  //========= Load Timer =======
  tft.setFont();
  tft.setCursor(327, 10);
  tft.setTextColor(HX8357_WHITE);  tft.setTextSize(2);
  tft.println("Load");
  tft.setCursor(322, 30);
  tft.println("Timer");
  tft.drawRoundRect(Timer.x, Timer.y, Timer.Width, Timer.Height , Timer.Round, Touch_Line_Color);
  tft.setCursor(327, 55);
  tft.setTextColor(HX8357_WHITE);  tft.setTextSize(4);
  tft.println("30");

  //========= Stack Temp =======
  tft.setCursor(408, 10);
  tft.setTextColor(HX8357_WHITE);  tft.setTextSize(2);
  tft.println("Stack");
  tft.setCursor(412, 30);
  tft.println("Temp");
  tft.drawRoundRect(Stack.x, Stack.y, Stack.Width, Stack.Height , Stack.Round, Touch_Line_Color);
  tft.setCursor(405, 55);
  tft.setTextColor(HX8357_WHITE);  tft.setTextSize(4);
  tft.println("250");


  //======== Damper Position Graphic ============

  tft.setFont();
  tft.setCursor(315, 150);
  tft.setTextColor(HX8357_WHITE);  tft.setTextSize(2);
  tft.println("Damp");
  tft.setCursor(327, 170);
  tft.println("Pos");
  tft.fillRoundRect(320, 203, 35, 114, 10, HX8357_WHITE);
  tft.drawRoundRect(Damper.x, Damper.y, Damper.Width, Damper.Height , Damper.Round, HX8357_BLACK);

  for (int i = 10; i >= 6 ; i--) {
    tft.fillRect (325, (202 + ((i) * 10)), 25, 8, HX8357_RED);
    delay (5);
  }

  //======== Fan Speed Graphic ============

  tft.setCursor(398, 150);
  tft.setTextColor(HX8357_WHITE);  tft.setTextSize(2);
  tft.println("Fan");
  tft.setCursor(380, 170);
  tft.println("Speed");
  tft.fillRoundRect(392, 203, 35, 114, 10, HX8357_WHITE);
  tft.drawRoundRect(Fan.x, Fan.y, Fan.Width, Fan.Height , Fan.Round, HX8357_BLACK);

  for (int i = 10; i >= 7 ; i--) {
    tft.fillRect (397, (202 + ((i) * 10)), 25, 8, HX8357_RED);
    delay (5);

    //======== Arrows ============

    tft.fillTriangle ((UpArrow.x + UpArrow.Width / 2), UpArrow.y, UpArrow.x, (UpArrow.y + UpArrow.Height), (UpArrow.x + UpArrow.Width), (UpArrow.y + UpArrow.Height), HX8357_WHITE);
    tft.fillRect((UpArrow.x + (UpArrow.Width / 2) - 8), (UpArrow.y + UpArrow.Height), 16, 20 , HX8357_WHITE);
    tft.drawRoundRect(UpArrow.x, UpArrow.y, UpArrow.Width, UpArrow.Height , UpArrow.Round, Touch_Line_Color);


    tft.fillTriangle ((DownArrow.x + DownArrow.Width / 2), (DownArrow.y + DownArrow.Height), DownArrow.x, (DownArrow.y), (DownArrow.x + DownArrow.Width), (DownArrow.y), HX8357_WHITE);
    tft.fillRect((DownArrow.x + (DownArrow.Width / 2) - 8), (DownArrow.y ), 16, -20 , HX8357_WHITE);
    tft.drawRoundRect(UpArrow.x, DownArrow.y, DownArrow.Width, DownArrow.Height , DownArrow.Round, Touch_Line_Color);
  }

}
//========
void bmpDraw(char *filename, uint8_t x, uint16_t y) {

  File     bmpFile;
  int      bmpWidth, bmpHeight;   // W+H in pixels
  uint8_t  bmpDepth;              // Bit depth (currently must be 24)
  uint32_t bmpImageoffset;        // Start of image data in file
  uint32_t rowSize;               // Not always = bmpWidth; may have padding
  uint8_t  sdbuffer[3 * BUFFPIXEL]; // pixel buffer (R+G+B per pixel)
  uint8_t  buffidx = sizeof(sdbuffer); // Current position in sdbuffer
  boolean  goodBmp = false;       // Set to true on valid header parse
  boolean  flip    = true;        // BMP is stored bottom-to-top
  int      w, h, row, col;
  uint8_t  r, g, b;
  uint32_t pos = 0, startTime = millis();

  if ((x >= tft.width()) || (y >= tft.height())) return;
/*
  Serial.println();
  Serial.print(F("Loading image '"));
  Serial.print(filename);
  Serial.println('\'');
*/
  // Open requested file on SD card
  if ((bmpFile = SD.open(filename)) == NULL) {
    Serial.print(F("File not found"));
    return;
  }

  // Parse BMP header
  if (read16(bmpFile) == 0x4D42) { // BMP signature
//   Serial.print(F("File size: ")); Serial.println(read32(bmpFile));
   (read32(bmpFile));
    (void)read32(bmpFile); // Read & ignore creator bytes
    bmpImageoffset = read32(bmpFile); // Start of image data
//    Serial.print(F("Image Offset: ")); Serial.println(bmpImageoffset, DEC);
    // Read DIB header
//   Serial.print(F("Header size: ")); Serial.println(read32(bmpFile));
    (read32(bmpFile));
    bmpWidth  = read32(bmpFile);
    bmpHeight = read32(bmpFile);
    if (read16(bmpFile) == 1) { // # planes -- must be '1'
      bmpDepth = read16(bmpFile); // bits per pixel
 //     Serial.print(F("Bit Depth: ")); Serial.println(bmpDepth);
      if ((bmpDepth == 24) && (read32(bmpFile) == 0)) { // 0 = uncompressed

        goodBmp = true; // Supported BMP format -- proceed!
 //       Serial.print(F("Image size: "));
 //       Serial.print(bmpWidth);
 //      Serial.print('x');
 //       Serial.println(bmpHeight);

        // BMP rows are padded (if needed) to 4-byte boundary
        rowSize = (bmpWidth * 3 + 3) & ~3;

        // If bmpHeight is negative, image is in top-down order.
        // This is not canon but has been observed in the wild.
        if (bmpHeight < 0) {
          bmpHeight = -bmpHeight;
          flip      = false;
        }

        // Crop area to be loaded
        w = bmpWidth;
        h = bmpHeight;
        if ((x + w - 1) >= tft.width())  w = tft.width()  - x;
        if ((y + h - 1) >= tft.height()) h = tft.height() - y;

        // Set TFT address window to clipped image bounds
        tft.startWrite(); // Start TFT transaction
        tft.setAddrWindow(x, y, w, h);

        for (row = 0; row < h; row++) { // For each scanline...

          // Seek to start of scan line.  It might seem labor-
          // intensive to be doing this on every line, but this
          // method covers a lot of gritty details like cropping
          // and scanline padding.  Also, the seek only takes
          // place if the file position actually needs to change
          // (avoids a lot of cluster math in SD library).
          if (flip) // Bitmap is stored bottom-to-top order (normal BMP)
            pos = bmpImageoffset + (bmpHeight - 1 - row) * rowSize;
          else     // Bitmap is stored top-to-bottom
            pos = bmpImageoffset + row * rowSize;
          if (bmpFile.position() != pos) { // Need seek?
            tft.endWrite(); // End TFT transaction
            bmpFile.seek(pos);
            buffidx = sizeof(sdbuffer); // Force buffer reload
            tft.startWrite(); // Start new TFT transaction
          }

          for (col = 0; col < w; col++) { // For each pixel...
            // Time to read more pixel data?
            if (buffidx >= sizeof(sdbuffer)) { // Indeed
              tft.endWrite(); // End TFT transaction
              bmpFile.read(sdbuffer, sizeof(sdbuffer));
              buffidx = 0; // Set index to beginning
              tft.startWrite(); // Start new TFT transaction
            }

            // Convert pixel from BMP to TFT format, push to display
            b = sdbuffer[buffidx++];
            g = sdbuffer[buffidx++];
            r = sdbuffer[buffidx++];
            tft.pushColor(tft.color565(r, g, b));
          } // end pixel
        } // end scanline
        tft.endWrite(); // End last TFT transaction
        /*
        Serial.print(F("Loaded in "));
        Serial.print(millis() - startTime);
        Serial.println(" ms");
        */
      } // end goodBmp
    }
  }

  bmpFile.close();
  if (!goodBmp) Serial.println(F("BMP format not recognized."));
}

// These read 16- and 32-bit types from the SD card file.
// BMP data is stored little-endian, Arduino is little-endian too.
// May need to reverse subscript order if porting elsewhere.

uint16_t read16(File &f) {
  uint16_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read(); // MSB
  return result;
}

uint32_t read32(File &f) {
  uint32_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read();
  ((uint8_t *)&result)[2] = f.read();
  ((uint8_t *)&result)[3] = f.read(); // MSB
  return result;
}
