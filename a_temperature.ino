
//===== load array from Resources.h ==========
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;        // your network password (use for WPA)

//===== SD Seek address in refresh.txt =========
// A token refresh immediately expires the previously issued access and refresh tokens and issues brand new tokens.
// SD card is used to store refresh_token in "refresh.txt"
//addr 0-31 refresh_token
const int address_refresh_token = 0;
const int address_null_termination = 32;        // used to check if EEProm is initialized

//===== Strings used to build Post string requests =============
String access_token = "";
String refresh_token = "";
String ecobeePin = "";
String code = "";



int status = WL_IDLE_STATUS;

//===== JSON max content size
const size_t MAX_CONTENT_SIZE = 1600;

//===== client response info ===========
int statuscode = 0;
String response = "";

char server[] = "api.ecobee.com";

WiFiSSLClient wifiClient;
HttpClient client = HttpClient(wifiClient, server, 443);

void writeEEstring(String file_name, String data) {

  SD.remove("refresh.txt");  // always start with a new file (some day could add history)

  SD_Refresh_File = SD.open(file_name, FILE_WRITE);

  // if the file opened okay, write to it:

  if (SD_Refresh_File) {    // If File created and opened succesfuly

    SD_Refresh_File.println(data);   // Write new refresh code
    SD_Refresh_File.close();         // all done, close file
  } else {
    // if the file didn't open, print an error:
    Serial.println("SD card problem opening file");
  }
}

String readEEstring(String file_name) {
  char data[32];

  SD_Refresh_File = SD.open(file_name, FILE_WRITE); // Open file to read

  SD_Refresh_File.seek(0);                          // Set Pointer at first byte in file
  for (int len = 0; len <= 31; len++) {             // Read on byte at a time filling array
    data[len] = SD_Refresh_File.read();
  }
  data[32] = '\0';                                  // used to identify end of char string to convert to string
  SD_Refresh_File.close();

  return String(data);                              // pass string back to function
}

void Extract_Json_Strings (String data, String & Var_1, String Var_1_json, String & Var_2, String Var_2_json) { // use of ampersand passes pointers
  StaticJsonDocument <500> jsonDoc; // changed from 500 to 1500 6/28 Nano 33 test
  auto error = deserializeJson(jsonDoc, data);
  if (error) {
    Serial.print(F("deserializeJson() failed with code "));
    Serial.println(error.c_str());
  }
  else {
    String tmp1 = jsonDoc[Var_1_json];
    Var_1 = tmp1 ;                            // this is the only way I could get this access_token updated
    String tmp2 = jsonDoc[Var_2_json];
    Var_2 = tmp2 ;                            // this is the only way I could get this access_token updated
    /*
      Serial.print (Var_1_json);
      Serial.print (": ");
      Serial.println (Var_1);
      Serial.print (Var_2_json);
      Serial.print (": ");
      Serial.println (Var_2);
    */
  }
}

void create_new_refresh_keys (String & refresh_token_loc, String & access_token_loc) {
  client.beginRequest();

  //======= get ecobeePin ===================
  // converted from JavaScript: https://www.ecobee.com/home/developer/api/examples/ex1.shtml
  client.get("https://api.ecobee.com/authorize?response_type=ecobeePin&client_id=dRc7CqSwIxKI7pNp3ZMDqJGPY7aT9akm&scope=smartWrite");
  client.endRequest();
  // read the status code and body of the response
  int statusCode = client.responseStatusCode();
  String response = client.responseBody();

  Serial.print("ecobeePin Status code: ");
  Serial.println(statusCode);
  Serial.print("Refresh Response: ");
  Serial.println(response);

  Extract_Json_Strings(response, ecobeePin, "ecobeePin", code, "code");
  writeEEstring ("refresh.txt", refresh_token);       // Save for next running of Setup/Refresh

  Serial.print ("Aurthorization code: ");
  Serial.println (code );
  Serial.print ("ecobeePin: ");
  Serial.println (ecobeePin );
  Serial.println ("go to ecobee.com MY APPS");
  Serial.println ("click add appliaction & paste ecobeePin into autorization code");
  Serial.println ("click add app in lower right corner");

  //======= get ecobee Aurthorization code, final step to get Access and Refresh codes ===================
  // converted from JavaScript: https://www.ecobee.com/home/developer/api/examples/ex1.shtml
  refresh_token = "null";
  delay (20000);
  int i = 0;
  while (refresh_token == "null" || i == 6) {
    client.post("https://api.ecobee.com/token?grant_type=ecobeePin&code=" + code + "&client_id=" + SECRET_Client_ID);
    client.endRequest();
    // read the status code and body of the response
    statusCode = client.responseStatusCode();
    response = client.responseBody();

    Serial.print("Aurthorization Status code: ");
    Serial.println(statusCode);
    Serial.print("Refresh Response: ");
    Serial.println(response);

    Extract_Json_Strings(response, access_token_loc, "access_token", refresh_token_loc, "refresh_token");
    writeEEstring ("refresh.txt", refresh_token_loc);       // Save for next running of Setup/Refresh

    Serial.print ("refresh_token: ");
    Serial.println (refresh_token_loc );
    Serial.print ("access_token: ");
    Serial.println (access_token_loc );
    delay (10000);                          //10 Second Delay
    if (i == 6) {
      Serial.println("Time out error > 1 minute");
      Serial.println("press reset to retry");
      while (true);
    }
  }

}



void UpDate_Temperatures() {

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }


  //==========

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < "1.0.0") {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {                        // Connect to WPA/WPA2 network:
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    delay(10000);                                         // wait 10 seconds for connection:
  }

  Serial.println("You're connected to the network");
  //printCurrentNet();    Leave for Debug
  //printWifiData();

  Serial.println("Starting connection to server...");     // if you get a connection, report back via serial:
  client.beginRequest();

  //======= get latest refresh code from EEProm to use for refresh tokens ===================
  refresh_token = readEEstring("refresh.txt");
  client.post("https://api.ecobee.com/token?grant_type=refresh_token&refresh_token=" + refresh_token + "&client_id=" + SECRET_Client_ID);
  client.endRequest();
  // read the status code and body of the response
  int statusCode = client.responseStatusCode();
  if (statusCode == 200)
  {
    String response = client.responseBody();
    Serial.print("Refresh Status code: ");
    Serial.println(statusCode);
    Serial.print("Refresh Response: ");
    Serial.println(response);

    Extract_Json_Strings(response, access_token, "access_token", refresh_token, "refresh_token");
    writeEEstring ("refresh.txt", refresh_token);       // Save for next running of Setup/Refresh

    Serial.print ("refresh_token: ");
    Serial.println (refresh_token );
    Serial.print ("access_token/Bearer: ");
    Serial.println (access_token );
    Serial.println ();
  } else {
    Serial.println ("Error in obtaining access code, need to run create_new_refresh_keys ()");
    create_new_refresh_keys (refresh_token, access_token);
  }


  //======= Send Request for Ecobee rooom temperature & Desired temperature ===================
  String postData = "{\"selection\":{\"selectionType\":\"registered\",\"selectionMatch\":\"\",\"includeRuntime\":true,\"includeWeather\":false}}";
  client.beginRequest();
  client.get("https://api.ecobee.com/1/thermostat?format=json&body=" + postData);   //moved postData here & changed to a GET
  client.sendHeader("Authorization", ("Bearer " + access_token));
  client.sendHeader("Content-Type", "text/json");
  client.endRequest();

  // ========  read the status code and body of the response  ===========
  statusCode = client.responseStatusCode();
  response = client.responseBody();
  // Serial.print("StatusCode: ");
  // Serial.println(statusCode);
  Serial.print("Response: ");
  Serial.println(response);


  //String test1, test2;


  Serial.print ("FreeMemory: ");
  Serial.println( freeMemory());


  // ======= Extract temperature and desired temperature ========= Using String functions, easier than ArduinoJSON calls.
  int StartOf = response.indexOf ("actualTemperature");
  String actual_Temperature_Str (response.substring((StartOf + 20), StartOf + 23));
  LivingRoomTemp = actual_Temperature_Str.toInt();
  float x = LivingRoomTemp;
  x = x / 10;
  Serial.print("LivingRoomTemp: ");
  Serial.println (x, 1);

  StartOf = response.indexOf ("desiredHeat");
  String Disired_Heat_Str = (response.substring((StartOf + 14), StartOf + 17));
  DesiredRoomTemp = Disired_Heat_Str.toInt();
  x = DesiredRoomTemp;
  x = x / 10;
  Serial.print("Disired Temp: ");
  Serial.println (x, 1);



  //======= Send Request for Ecobee rooom temperature & Desired temperature ===================
  postData = "{\"selection\":{\"selectionType\":\"registered\",\"selectionMatch\":\"\",\"includeRuntime\":false,\"includeWeather\":true}}";
  client.beginRequest();
  client.get("https://api.ecobee.com/1/thermostat?format=json&body=" + postData);   //moved postData here & changed to a GET
  client.sendHeader("Authorization", ("Bearer " + access_token));
  client.sendHeader("Content-Type", "text/json");
  client.endRequest();

  // ========  read the status code and body of the response  ===========
  statusCode = client.responseStatusCode();
  response = client.responseBody();
  // Serial.print("StatusCode: ");
  // Serial.println(statusCode);
  Serial.print("Response: ");
  Serial.println(response);

  Serial.println ("=======");
  String test_Str;

  // ======== Get Weather Time Stamp =================
  StartOf = response.indexOf ("timestamp");
  Weather_TimeStamp = (response.substring((StartOf + 13), StartOf + (13 + 19)) ); // "dateTime": "2020-06-29 12:00:00"
  Serial.print ("time stamp :"); Serial.println(Weather_TimeStamp);


  StartOf = response.indexOf ("weatherSymbol");                   // Find First temperature (1 of 9)
  
  for (int i = 0; i <= 8 ; i++) {

    //=============== Get weatherSymbol =================
    test_Str = (response.substring((StartOf + 16), StartOf + (16 + 2)) );
    //   Serial.println (test_Str);
    weatherSymbol[i] = test_Str.toInt();



    //=============== Get dateTime ======================

    StartOf = response.indexOf ("dateTime", StartOf);
    test_Str = (response.substring((StartOf + 12), StartOf + (12 + 19)) ); // "dateTime": "2020-06-29 12:00:00"
    test_Str.toCharArray(buffer_string_char, test_Str.length() + 1);

    dateTime_Str[i] = buffer_string_char ;
Serial.println (dateTime_Str[0]);
Serial.println (dateTime_Str[1]);
Serial.println (dateTime_Str[2]);
Serial.println (dateTime_Str[3]);
Serial.println (dateTime_Str[4]);
Serial.println (dateTime_Str[5]);
Serial.println (dateTime_Str[6]);
Serial.println (dateTime_Str[7]);
Serial.println (dateTime_Str[8]);

    //=============== Get Temperature ===================
    StartOf = response.indexOf ("temperature", StartOf);    // Find First temperature (1 of 9)
    test_Str = (response.substring((StartOf + 14), StartOf + 17));
    //    Serial.println (test_Str);
    temperature[i] = test_Str.toInt();

    StartOf = response.indexOf ("weatherSymbol", StartOf + 1);                 // move to next weather group


    Serial.print(i); Serial.print (" : "); Serial.print (dateTime_Str[i]); Serial.print ("  "); Serial.print (weatherSymbol[i]); Serial.print ("  "); Serial.println( temperature[i]);
  }

    Serial.println ("==============");
  for (int i=5; i<=8; i++){
       Serial.print(i); Serial.print (" : "); Serial.print (dateTime_Str[i]); Serial.print ("  "); Serial.print (weatherSymbol[i]); Serial.print ("  "); Serial.println( temperature[i]);

  }

  /*
    StartOf = response.indexOf ("temperature");     // Find First temperature (1 of 9)
    String OutSide_Heat_Str = (response.substring((StartOf + 14), StartOf + 17));
    StartOf = response.indexOf ("temperature", StartOf + 1);


    x = OutSideRoomTemp;
    x = x / 10;
    Serial.print("Outside Temp: ");
    Serial.println (x, 1);
  */

}
