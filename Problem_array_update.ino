void setup() {
  // put your setup code here, to run once:
 
  char *dateTime_Str[8] = {"2020-06-30 06:00:0A", "2020-06-30 06:00:0B", "2020-06-30 06:00:0C", "2020-06-30 06:00:0D", "2020-06-30 06:00:00", "2020-06-30 06:00:00", "2020-06-30 06:00:00", "2020-06-30 06:00:00"};
  char buffer_string_char[30];

  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  
  Serial.println ("=======");
  String Test_Str;

  // ======== Get Weather Time Stamp =================



  for (int i = 0; i <= 8 ; i++) {

    //=============== Get dateTime ======================

    //    StartOf = response.indexOf ("dateTime", StartOf);
    //    test_Str = (response.substring((StartOf + 12), StartOf + (12 + 19)) ); // "dateTime": "2020-06-29 12:00:00"

    Test_Str = "sketch_jul03c";
    Test_Str = Test_Str + i;

    Test_Str.toCharArray(buffer_string_char, Test_Str.length() + 1);

    dateTime_Str[i] = buffer_string_char; //buffer_string_char;
    Serial.println (dateTime_Str[0]);
    Serial.println (dateTime_Str[1]);
    Serial.println (dateTime_Str[2]);
    Serial.println (dateTime_Str[3]);
    Serial.println (dateTime_Str[4]);
    Serial.println (dateTime_Str[5]);
    Serial.println (dateTime_Str[6]);
    Serial.println (dateTime_Str[7]);
    Serial.println (dateTime_Str[8]);


    Serial.print(i); Serial.print (" : "); Serial.println (dateTime_Str[i]);
  }

  Serial.println ("==============");
  for (int i = 5; i <= 8; i++) {
    Serial.print(i); Serial.print (" : "); Serial.println (dateTime_Str[i]);

  }

}

void loop() {
  // put your main code here, to run repeatedly:

}
