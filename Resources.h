//#include <EEPROM.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <ArduinoHttpClient.h>
#include <WiFiNINA.h>
#include <MemoryFree.h>
#include <Adafruit_GFX.h>
#include <Adafruit_HX8357.h>
#include <SD.h>    // testing out switching from SD.h to SdFat.h says it is better
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSansBold12pt7b.h>
#include <TouchScreen.h>
//#include <FlashAsEEPROM.h>    for nano 33


class Button_Class {
public:
  int16_t x, y, Width, Height, Round; 
    
};

//========== Network Secrets =================
#define SECRET_SSID "160BayRd"
#define SECRET_PASS "31Winthrop"
#define SECRET_Client_ID "dRc7CqSwIxKI7pNp3ZMDqJGPY7aT9akm"
#define SECRET_Seed_Refresh_Token "gffJWyj7Yo6onePq60IoTeGzJGvN4Ew1" 

//========== Hardware Pins ===================
#define TFT_CS 10
#define TFT_DC 9
#define TFT_RST 8 // RST can be set to -1 if you tie it to Arduino's reset
#define SD_CS 4   // SD card Chip Select

// These are the four touchscreen analog pins
#define YP A2  // must be an analog pin, use "An" notation!
#define XM A3  // must be an analog pin, use "An" notation!
#define YM 7   // can be a digital pin
#define XP 8   // can be a digital pin

//============ Color palate ===================
#define HX8357_BLACK       0x0000  ///<   0,   0,   0
#define HX8357_NAVY        0x000F  ///<   0,   0, 123
#define HX8357_DARKGREEN   0x03E0  ///<   0, 125,   0
#define HX8357_DARKCYAN    0x03EF  ///<   0, 125, 123
#define HX8357_MAROON      0x7800  ///< 123,   0,   0
#define HX8357_PURPLE      0x780F  ///< 123,   0, 123
#define HX8357_OLIVE       0x7BE0  ///< 123, 125,   0
#define HX8357_LIGHTGREY   0xC618  ///< 198, 195, 198
#define HX8357_DARKGREY    0x7BEF  ///< 123, 125, 123
#define HX8357_BLUE        0x001F  ///<   0,   0, 255
#define HX8357_GREEN       0x07E0  ///<   0, 255,   0
#define HX8357_CYAN        0x07FF  ///<   0, 255, 255
#define HX8357_RED         0xF800  ///< 255,   0,   0
#define HX8357_MAGENTA     0xF81F  ///< 255,   0, 255
#define HX8357_YELLOW      0xFFE0  ///< 255, 255,   0
#define HX8357_WHITE       0xFFFF  ///< 255, 255, 255
#define HX8357_ORANGE      0xFD20  ///< 255, 165,   0
#define HX8357_GREENYELLOW 0xAFE5  ///< 173, 255,  41
#define HX8357_PINK        0xFC18  ///< 255, 130, 198
