/*
  Edited by AndrewJohnsen31 02/13/2020

*/

#include "Resources.h"

//========= Global Variables ============

int LivingRoomTemp = 777;
int BasementRoomTemp = 767;
int DesiredRoomTemp = 888;
int OutSideRoomTemp = 999;
String Weather_Location = "Sanborntonn New Hampshire"; 
String Weather_TimeStamp = "2020-07-02 21:03:22"; //""timestamp": 
int weatherSymbol[8];
char *dateTime_Str[8] = {"2020-06-30 06:00:0A", "2020-06-30 06:00:0B", "2020-06-30 06:00:0C", "2020-06-30 06:00:0D", "2020-06-30 06:00:00", "2020-06-30 06:00:00", "2020-06-30 06:00:00", "2020-06-30 06:00:00"};

int temperature[9];

char buffer_string_char[30] = "";

/*
            "dateTime": "2020-06-29 12:00:00",
            "condition": "Possible Drizzle",
            "temperature": 663,
            "pressure": 1009,
            "relativeHumidity": 97,
            "dewpoint": 656,
            "visibility": 16000,
            "windSpeed": 7,
            "windGust": -5002,
            "windDirection": "NE",
            "windBearing": 36,
            "pop": 40,
            "tempHigh": -5002,
            "tempLow": -5002,
            "sky": 5
            no_symbol = -2
  sunny = 0
  few_clouds = 1
  partly_cloudy = 2
  mostly_cloudy = 3
  overcast = 4
  drizzle = 5
  rain = 6
  freezing_rain = 7
  showers = 8
  hail = 9
  snow = 10
  flurries = 11
  freezing_snow = 12
  blizzard = 13
  pellets = 14
  thunderstorm = 15
  windy = 16
  tornado = 17
  fog = 18
  haze = 19
  smoke = 20
  dust = 21
*/

//========= Debug Items =================
#define Touch_Line_Color HX8357_BLACK

boolean Switch_Pressed = false;

int Pixel_Y = 0;
int Pixel_X = 0;
#define BUFFPIXEL 20

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Adafruit_HX8357 tft = Adafruit_HX8357(TFT_CS, TFT_DC, TFT_RST);

// End Paste from Arduino

Button_Class Upstairs;
Button_Class Downstairs;
Button_Class Outside;
Button_Class UpstairsSet;
Button_Class DownstairsSet;
Button_Class IGL;
Button_Class Weather;
Button_Class Fan;
Button_Class Damper;
Button_Class Timer;
Button_Class Stack;
Button_Class UpArrow;
Button_Class DownArrow;

File SD_Refresh_File;

void setup() {
  //Initialize serial and wait for port to open:

  delay(1000);
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


// trying to avoid SD card hanging, requiring Power cycle...... let see if it works 07/01/2020
  pinMode (SD_CS, OUTPUT);
  delay (100);
  digitalWrite(SD_CS, HIGH);
  delay (500);

  // ============Setup Display ============
  tft.begin();

  tft.setRotation(1);
  //=================
  tft.fillScreen(HX8357_BLACK);



  Serial.print("Initializing SD card...");
  if (!SD.begin(SD_CS)) {
    Serial.println("failed!");
  }


  Downstairs.x = 83;
  Downstairs.y = 113;
  Downstairs.Width = 129;
  Downstairs.Height = 98;
  Downstairs.Round = 10;

  Upstairs.x = 83;
  Upstairs.y = 9;
  Upstairs.Width = 129;
  Upstairs.Height = 98;
  Upstairs.Round = 10;

  Outside.x = 83;
  Outside.y = 217;
  Outside.Width = 129;
  Outside.Height = 98;
  Outside.Round = 10;

  IGL.x = 0;
  IGL.y = 275;
  IGL.Width = 80;
  IGL.Height = 44;
  IGL.Round = 10;

  Weather.x = 212;
  Weather.y = 230;
  Weather.Width = 79;
  Weather.Height = 75;
  Weather.Round = 10;

  UpstairsSet.x = 212;
  UpstairsSet.y = 60;
  UpstairsSet.Width = 79;
  UpstairsSet.Height = 48;
  UpstairsSet.Round = 10;

  DownstairsSet.x = 212;
  DownstairsSet.y = 117;
  DownstairsSet.Width = 79;
  DownstairsSet.Height = 48;
  DownstairsSet.Round = 10;

  Fan.x = 390;
  Fan.y = 200;
  Fan.Width = 45;
  Fan.Height = 119;
  Fan.Round = 10;

  Damper.x = 315;
  Damper.y = 200;
  Damper.Width = 45;
  Damper.Height = 119;
  Damper.Round = 10;

  Timer.x = 320;
  Timer.y = 50;
  Timer.Width = 60;
  Timer.Height = 40;
  Timer.Round = 10;

  Stack.x = 395;
  Stack.y = 50;
  Stack.Width = 84;
  Stack.Height = 40;
  Stack.Round = 10;

  UpArrow.x = 440;
  UpArrow.y = 175;
  UpArrow.Width = 40;
  UpArrow.Height = 45;
  UpArrow.Round = 10;

  DownArrow.x = 440;
  DownArrow.y = 275;
  DownArrow.Width = 40;
  DownArrow.Height = 45;
  DownArrow.Round = 10;
  /*
    String test_Str = "tst0-06-29 12:00:0x";
    char buffer_string_char[] = "Bufe-06-29 12:00:00";
    dateTime_Str[3] = "date-06-29 12:00:00";



    for (int i = 0; i <= 3 ; i++) {


      //Serial.print (test_Str.length());
      //Serial.print (dateTime_Str[1].length())
      //test_Str.toCharArray(dateTime_Str[i], 19);
      test_Str.toCharArray(buffer_string_char,test_Str.length()+1);
      dateTime_Str[i] = buffer_string_char ;

      Serial.print(i); Serial.print (" String : "); Serial.println (test_Str);
      Serial.print(i); Serial.print (" Array  : "); Serial.println (dateTime_Str[i]);
    //   Serial.print(i); Serial.print (" buf    : "); Serial.println (buffer_string_char);
    }
  */

  UpDate_Temperatures();
  Display_Today_Weather();
  //   UpDate_Display() ;
}

void loop() {

  delay (500);
  Update_TouchScreen();

}
