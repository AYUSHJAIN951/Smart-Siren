#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include "FirebaseESP8266.h"
//Variables
int i = 0;
int statusCode;
String st;
String content;


//Function Decalration
bool testWifi(void);
void launchWeb(void);
void setupAP(void);

//Establishing Local server at port 80 whenever required

//Firebase setup
#define FIREBASE_HOST "smart-bell-5cfeb.firebaseio.com" //Without http:// or https:// schemes
#define FIREBASE_AUTH "fSkI4XslIVKHnsec1KnrLLksHJwlpWLokJHGr8cU"
//Define FirebaseESP8266 data object
FirebaseData firebaseData;
FirebaseJson json;
void printResult(FirebaseData &data);

ESP8266WebServer server(80);
WiFiServer ESPserver(80);//Service Port


///////////////////////////////////////////////////////
#include <Wire.h>       //I2C library
#include <RtcDS3231.h>  //RTC library


//RtcDS3231 rtcObject;              //Uncomment for version 1.0.1 of the rtc library
RtcDS3231<TwoWire> rtcObject(Wire); //Uncomment for version 2.0.0 of the rtc library
 int Relay=D6;



const int OnHourIST = 8; //SET TIME TO ON RELAY (24 HOUR FORMAT)
const int OnMinIST = 30;


const int OnHourIIND = 9; //SET TIME TO ON RELAY (24 HOUR FORMAT)
const int OnMinIIND = 30;

const int OnHourBREAK = 10; //SET TIME TO ON RELAY (24 HOUR FORMAT)
const int OnMinBREAK = 30;

const int OnHourIIIRD = 10; //SET TIME TO ON RELAY (24 HOUR FORMAT)
const int OnMinIIIRD = 50;


const int OnHourIVTH = 11; //SET TIME TO ON RELAY (24 HOUR FORMAT)
const int OnMinIVTH = 50;

const int OnHourLUNCH = 12; //SET TIME TO ON RELAY (24 HOUR FORMAT)
const int OnMinLUNCH = 50;

const int OnHourVTH = 13; //SET TIME TO ON RELAY (24 HOUR FORMAT)
const int OnMinVTH = 50;

const int OnHourVITH = 14; //SET TIME TO ON RELAY (24 HOUR FORMAT)
  const int OnMinVITH = 40;

  const int OnHourVIITH = 15; //SET TIME TO ON RELAY (24 HOUR FORMAT)
const int OnMinVIITH = 35;

const int OnHourEND = 16; //SET TIME TO ON RELAY (24 HOUR FORMAT)
const int OnMinEND = 30;


const int IOnHourmrng = 9; //SET TIME TO ON RELAY (24 HOUR FORMAT)
const int IOnMinmrng = 30;


const int IOnHourmrngalert = 9; //SET TIME TO ON RELAY (24 HOUR FORMAT)
const int IOnMinmrngalert = 20;


const int IOnHourmrnghalftime = 10; //SET TIME TO ON RELAY (24 HOUR FORMAT)
const int IOnMinmrnghalftime = 15;

const int IOnHourmrnglastalert = 10; //SET TIME TO ON RELAY (24 HOUR FORMAT)
const int IOnMinmrnglastalert = 50;


const int IOnHourmrngend = 11; //SET TIME TO ON RELAY (24 HOUR FORMAT)
const int IOnMinmrngend = 00;

const int IOnHouraft = 13; //SET TIME TO ON RELAY (24 HOUR FORMAT)
const int IOnMinaft = 30;


const int IOnHouraftalert = 13; //SET TIME TO ON RELAY (24 HOUR FORMAT)
const int IOnMinaftalert = 20;



const int IOnHourafthalftime = 14; //SET TIME TO ON RELAY (24 HOUR FORMAT)
const int IOnMinafthalftime = 15;

const int IOnHouraftlastalert = 14; //SET TIME TO ON RELAY (24 HOUR FORMAT)
const int IOnMinaftlastalert = 50;

const int IOnHouraftend = 15; //SET TIME TO ON RELAY (24 HOUR FORMAT)
const int IOnMinaftend = 00;


/////////////////////////////external



const int EOnHourmrng = 9; //SET TIME TO ON RELAY (24 HOUR FORMAT)
const int EOnMinmrng = 30;


const int EOnHourmrngalert = 9; //SET TIME TO ON RELAY (24 HOUR FORMAT)
const int EOnMinmrngalert = 00;


const int EOnHourmrnghalftime = 11; //SET TIME TO ON RELAY (24 HOUR FORMAT)
const int EOnMinmrnghalftime = 00;

const int EOnHourmrnglastalert = 12; //SET TIME TO ON RELAY (24 HOUR FORMAT)
const int EOnMinmrnglastalert =20;


const int EOnHourmrngend = 12; //SET TIME TO ON RELAY (24 HOUR FORMAT)
const int EOnMinmrngend = 30;

const int EOnHouraft = 14; //SET TIME TO ON RELAY (24 HOUR FORMAT)
const int EOnMinaft = 00;


const int EOnHouraftalert = 13; //SET TIME TO ON RELAY (24 HOUR FORMAT)
const int EOnMinaftalert = 30;



const int EOnHourafthalftime = 15; //SET TIME TO ON RELAY (24 HOUR FORMAT)
const int EOnMinafthalftime = 30;

const int EOnHouraftlastalert = 16; //SET TIME TO ON RELAY (24 HOUR FORMAT)
const int EOnMinaftlastalert = 50;

const int EOnHouraftend = 17; //SET TIME TO ON RELAY (24 HOUR FORMAT)
const int EOnMinaftend = 00;



int OnHouronRequest=25;           //some junk is given in those values as 25 for now in hour and min
int OnMinonRequest=25;

int OnHouronRequest1=25;           //some junk is given in those values as 25 for now in hour and min
int OnMinonRequest1=25;

int OnHouronRequest2=25;           //some junk is given in those values as 25 for now in hour and min
int OnMinonRequest2=25;

int OnHouronRequest3=25;           //some junk is given in those values as 25 for now in hour and min
int OnMinonRequest3=25;

int OnHouronRequest4=25;           //some junk is given in those values as 25 for now in hour and min
int OnMinonRequest4=25;

int OnHouronRequest5=25;           //some junk is given in those values as 25 for now in hour and min
int OnMinonRequest5=25;

int OnHouronRequest6=25;           //some junk is given in those values as 25 for now in hour and min
int OnMinonRequest6=25;


int OnHouronRequestE1=25;           //some junk is given in those values as 25 for now in hour and min
int OnMinonRequestE1=25;

int OnHouronRequestE2=25;           //some junk is given in those values as 25 for now in hour and min
int OnMinonRequestE2=25;

int OnHouronRequestE3=25;           //some junk is given in those values as 25 for now in hour and min
int OnMinonRequestE3=25;

int OnHouronRequestE4=25;           //some junk is given in those values as 25 for now in hour and min
int OnMinonRequestE4=25;

int OnHouronRequestE5=25;           //some junk is given in those values as 25 for now in hour and min
int OnMinonRequestE5=25;

int OnHouronRequestE6=25;           //some junk is given in those values as 25 for now in hour and min
int OnMinonRequestE6=25;

int value; 

void setup() 
{
    //Starts serial connection
 rtcObject.Begin();     //Starts I2C
 pinMode(Relay,OUTPUT);
 RtcDateTime currentTime;
 RtcDateTime currentTime = RtcDateTime(20, 3, 8,23,36, 0); //define date and time object
 rtcObject.SetDateTime(currentTime); //configure the RTC with object
 digitalWrite(Relay,HIGH);

 ///////////////////////////////////////////////////
  

  Serial.begin(115200); //Initialising if(DEBUG)Serial Monitor
  Serial.println();
  Serial.println("Disconnecting previously connected WiFi");
  WiFi.disconnect();
  EEPROM.begin(512); //Initialasing EEPROM
  delay(10);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println();
  Serial.println();
  Serial.println("Startup");

  //---------------------------------------- Read eeprom for ssid and pass
  Serial.println("Reading EEPROM ssid");

  String esid;
  for (int i = 0; i < 32; ++i)
  {
    esid += char(EEPROM.read(i));
  }
  Serial.println();
  Serial.print("SSID: ");
  Serial.println(esid);
  Serial.println("Reading EEPROM pass");

  String epass = "";
  for (int i = 32; i < 96; ++i)
  {
    epass += char(EEPROM.read(i));
  }
  Serial.print("PASS: ");
  Serial.println(epass);


  WiFi.begin(esid.c_str(), epass.c_str());
  if (testWifi())
  {
    Serial.println("Succesfully Connected!!!");
    WiFi.mode(WIFI_STA);


    //


  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  //Set the size of WiFi rx/tx buffers in the case where we want to work with large data.
  firebaseData.setBSSLBufferSize(1024, 1024);

  //Set the size of HTTP response buffers in the case where we want to work with large data.
  firebaseData.setResponseSize(1024);

  //Set database read timeout to 1 minute (max 15 minutes)
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  //tiny, small, medium, large and unlimited.
  //Size and its write timeout e.g. tiny (1s), small (10s), medium (30s) and large (60s).
  Firebase.setwriteSizeLimit(firebaseData, "tiny");

  //optional, set the decimal places for float and double data to be stored in database
  Firebase.setFloatDigits(2);
  Firebase.setDoubleDigits(6);

  /*
  This option allows get and delete functions (PUT and DELETE HTTP requests) works for device connected behind the
  Firewall that allows only GET and POST requests.
  
  Firebase.enableClassicRequest(firebaseData, true);
  */

  String path = "/SIRENBELL2_checkpoint1";

  Serial.println("------------------------------------");
  Serial.println("Set double test...");
  IPAddress broadCast = WiFi.localIP();
  
  Serial.println(broadCast);
  int ip= broadCast[3];
  int ipp= broadCast[2];
  
    //Also can use Firebase.set instead of Firebase.setDouble
    if (Firebase.set(firebaseData, path + "/IP1/SIRENBELL2_checkpoint1/IP1",ip))  ///IP"1/2/3"/SIRENBELL2_checkpoint1/IP"1/2/3"
    {
      Serial.println("PASSED");
      Serial.println("PATH: " + firebaseData.dataPath());
      Serial.println("TYPE: " + firebaseData.dataType());
      Serial.println("ETag: " + firebaseData.ETag());
      Serial.print("VALUE: ");
      printResult(firebaseData);
      Serial.println("------------------------------------");
      Serial.println();
    }
    else
    {
      Serial.println("FAILED");
      Serial.println("REASON: " + firebaseData.errorReason());
      Serial.println("------------------------------------");
      Serial.println();
    }
  if (Firebase.set(firebaseData, path + "/IP11/SIRENBELL2_checkpoint1/IP11",ipp)) //set this  /IP"1/2/3"1/SIRENBELL2_checkpoint1/IP"1/2/3"1
    {
      Serial.println("PASSED");
      Serial.println("PATH: " + firebaseData.dataPath());
      Serial.println("TYPE: " + firebaseData.dataType());
      Serial.println("ETag: " + firebaseData.ETag());
      Serial.print("VALUE: ");
      printResult(firebaseData);
      Serial.println("------------------------------------");
      Serial.println();
    }
    else
    {
      Serial.println("FAILED");
      Serial.println("REASON: " + firebaseData.errorReason());
      Serial.println("------------------------------------");
      Serial.println();
    }
  

    //
      ESPserver.begin();
      Serial.println("Server Started");
      // Print the IP address
      Serial.print("The URL to control ESP8266: ");
      Serial.print("http://");
      Serial.print(WiFi.localIP());
      value=0;



    return;
  }
  else
  {
    Serial.println("Turning the HotSpot On");
    launchWeb();
    setupAP();// Setup HotSpot
  }

  Serial.println();
  Serial.println("Waiting.");
  
  while ((WiFi.status() != WL_CONNECTED))
  {
    Serial.print(".");
    delay(100);
    server.handleClient();
  }
  

}


//void setup() {
//  // initialize serial communication:
//  Serial.begin(9600);
//  // initialize the LED pins:
//  for (int thisPin = 2; thisPin < 7; thisPin++) {
//    pinMode(thisPin, OUTPUT);
//  }
//}

void loop() 
{
  RtcDateTime currentTime = rtcObject.GetDateTime(); //get the time from the RTC
  
 
  char str[20];   //declare a string as an array of chars
 
  sprintf(str, "%d:%d:%d",     //%d allows to print an integer to the string
          
          currentTime.Hour(),   //get hour method
          currentTime.Minute(), //get minute method
          currentTime.Second()  //get second method
         );

                  if(currentTime.Hour() == OnHouronRequest && currentTime.Minute() == OnMinonRequest && value==0)
                     {
                              digitalWrite(Relay,LOW);
                              Serial.println("ALARM ON");
                              Serial.println(str);
                              delay(20000);
                              digitalWrite(Relay,HIGH);
                              Serial.println("ALARM OFF");
                             OnHouronRequest=25;
                              OnMinonRequest=25;
                             
                             
                      }
                  
                     else if(currentTime.Hour() == OnHourIST && currentTime.Minute() == OnMinIST && value==0){
                                digitalWrite(Relay,LOW);
                                Serial.println("ALARM ON");
                                Serial.println(str);
                                
                                delay(20000);
                                digitalWrite(Relay,HIGH);
                                Serial.println("ALARM OFF");
                                delay(40000);
                                
                      }


                  else if(currentTime.Hour() == OnHouronRequest1 && currentTime.Minute() == OnMinonRequest1 && value==1)
                     {
                              digitalWrite(Relay,LOW);
                              Serial.println("ALARM ON");
                              Serial.println(str);
                              delay(20000);
                              digitalWrite(Relay,HIGH);
                              Serial.println("ALARM OFF");
                               OnHouronRequest1=25;           //some junk is given in those values as 25 for now in hour and min
                               OnMinonRequest1=25;
                     }                              
              
                  
                      
                    else if(currentTime.Hour() == OnHourIIND && currentTime.Minute() == OnMinIIND && value==0){
                              digitalWrite(Relay,LOW);
                              Serial.println("ALARM ON");
                              Serial.println(str);
                              delay(20000);
                              digitalWrite(Relay,HIGH);
                              Serial.println("ALARM OFF");
                              delay(40000);
                              
                      }
                  
                  
                      
                      else if(currentTime.Hour() == OnHourBREAK && currentTime.Minute() == OnMinBREAK && value==0){
                                digitalWrite(Relay,LOW);
                                Serial.println("ALARM ON");
                                Serial.println(str);
                                delay(20000);
                                digitalWrite(Relay,HIGH);
                                Serial.println("ALARM OFF");
                                delay(40000);
                      }
                  
                      else if(currentTime.Hour() == OnHourIVTH && currentTime.Minute() == OnMinIVTH && value==0){
                                    digitalWrite(Relay,LOW);
                                    Serial.println("ALARM ON");
                                    Serial.println(str);
                                    delay(20000);
                                    digitalWrite(Relay,HIGH);
                                    Serial.println("ALARM OFF");
                                    delay(40000);
                                  
                      }
                  
                      else if(currentTime.Hour() == OnHourVTH && currentTime.Minute() == OnMinVTH && value==0){
                                      digitalWrite(Relay,LOW);
                                      Serial.println("ALARM ON");
                                      Serial.println(str);
                                      delay(20000);
                                      digitalWrite(Relay,HIGH);
                                      Serial.println("ALARM OFF");
                                      delay(40000);
                                      
                      }
                  
                  
                  
                      
                      else if(currentTime.Hour() == OnHourVITH && currentTime.Minute() == OnMinVITH && value==0){
                                  digitalWrite(Relay,LOW);
                                  Serial.println("ALARM ON");
                                  Serial.println(str);
                                  delay(20000);
                                  digitalWrite(Relay,HIGH);
                                  Serial.println("ALARM OFF");
                                  delay(40000);
                               
                      }
                  
                  
                      else if(currentTime.Hour() == OnHourVIITH && currentTime.Minute() == OnMinVIITH && value==0){
                                digitalWrite(Relay,LOW);
                                Serial.println("ALARM ON");
                                Serial.println(str);
                                delay(20000);
                                digitalWrite(Relay,HIGH);
                                Serial.println("ALARM OFF");
                                delay(40000);
                                
                      }
                  
                  
                      else if(currentTime.Hour() == OnHourLUNCH && currentTime.Minute() == OnMinLUNCH && value==0){
                                digitalWrite(Relay,LOW);
                                Serial.println("ALARM ON");
                                Serial.println(str);
                                delay(20000);
                                digitalWrite(Relay,HIGH);
                                Serial.println("ALARM OFF");
                                delay(40000);
                                
                      }
                  
                        if(currentTime.Hour() == OnHourEND && currentTime.Minute() == OnMinEND && value==0){
                                digitalWrite(Relay,LOW);
                                Serial.println("ALARM ON");
                                Serial.println(str);
                                delay(20000);
                                digitalWrite(Relay,HIGH);
                                Serial.println("ALARM OFF");
                                delay(40000);
                              
                      }

                      //////////////////////

                        if(currentTime.Hour() == OnHouronRequest1 && currentTime.Minute() == OnMinonRequest1 && value==1)
                     {
                              digitalWrite(Relay,LOW);
                              Serial.println("ALARM ON");
                              Serial.println(str);
                              delay(20000);
                              digitalWrite(Relay,HIGH);
                              Serial.println("ALARM OFF");
                              OnHouronRequest2=25;           //some junk is given in those values as 25 for now in hour and min
                              OnMinonRequest2=25;
                              
                      }

                      if(currentTime.Hour() == OnHouronRequest2 && currentTime.Minute() == OnMinonRequest2 && value==1)
                     {
                              digitalWrite(Relay,LOW);
                              Serial.println("ALARM ON");
                              Serial.println(str);
                              delay(20000);
                              digitalWrite(Relay,HIGH);
                              Serial.println("ALARM OFF");
                             OnHouronRequest3=25;           //some junk is given in those values as 25 for now in hour and min
                             OnMinonRequest3=25;
                              
                      }

                           if(currentTime.Hour() == OnHouronRequest3 && currentTime.Minute() == OnMinonRequest3 && value==1)
                     {
                              digitalWrite(Relay,LOW);
                              Serial.println("ALARM ON");
                              Serial.println(str);
                              delay(20000);
                              digitalWrite(Relay,HIGH);
                              Serial.println("ALARM OFF");
                             OnHouronRequest3=25;           //some junk is given in those values as 25 for now in hour and min
                             OnMinonRequest3=25;
                             
                      }

                           if(currentTime.Hour() == OnHouronRequest4 && currentTime.Minute() == OnMinonRequest4 && value==1)
                     {
                              digitalWrite(Relay,LOW);
                              Serial.println("ALARM ON");
                              Serial.println(str);
                              delay(20000);
                              digitalWrite(Relay,HIGH);
                              Serial.println("ALARM OFF");
                              OnHouronRequest4=25;           //some junk is given in those values as 25 for now in hour and min
                              OnMinonRequest4=25;
                           
                      }

                            if(currentTime.Hour() == OnHouronRequest5 && currentTime.Minute() == OnMinonRequest5 && value==1)
                     {
                              digitalWrite(Relay,LOW);
                              Serial.println("ALARM ON");
                              Serial.println(str);
                              delay(20000);
                              digitalWrite(Relay,HIGH);
                              Serial.println("ALARM OFF");
                               OnHouronRequest5=25;           //some junk is given in those values as 25 for now in hour and min
                              OnMinonRequest5=25;
                             
                      }

                          if(currentTime.Hour() == OnHouronRequest6 && currentTime.Minute() == OnMinonRequest6 && value==1)
                     {
                              digitalWrite(Relay,LOW);
                              Serial.println("ALARM ON");
                              Serial.println(str);
                              delay(20000);
                              digitalWrite(Relay,HIGH);
                              Serial.println("ALARM OFF");
                              
                              OnHouronRequest6=25;           //some junk is given in those values as 25 for now in hour and min
                               OnMinonRequest6=25;
                             
                      }

                      if(currentTime.Hour() == IOnHourmrng && currentTime.Minute() == IOnMinmrng && value==1){
                                digitalWrite(Relay,LOW);
                                Serial.println("ALARM ON");
                                Serial.println(str);
                                
                                delay(20000);
                                digitalWrite(Relay,HIGH);
                                Serial.println("ALARM OFF");
                                delay(40000);
                                Serial.println(str);
                      }



                      if(currentTime.Hour() == IOnHourmrngalert && currentTime.Minute() == IOnMinmrngalert && value==1){
                                digitalWrite(Relay,LOW);
                                Serial.println("ALARM ON");
                                Serial.println(str);
                                
                                delay(20000);
                                digitalWrite(Relay,HIGH);
                                Serial.println("ALARM OFF");
                                delay(40000);
                                
                      }

                      if(currentTime.Hour() == IOnHourmrnghalftime && currentTime.Minute() == IOnMinmrnghalftime && value==1){
                                digitalWrite(Relay,LOW);
                                Serial.println("ALARM ON");
                                Serial.println(str);
                                
                                delay(20000);
                                digitalWrite(Relay,HIGH);
                                Serial.println("ALARM OFF");
                                delay(40000);
                                
                      }



                      if(currentTime.Hour() == IOnHourmrnglastalert && currentTime.Minute() == IOnMinmrnglastalert && value==1){
                                digitalWrite(Relay,LOW);
                                Serial.println("ALARM ON");
                                Serial.println(str);
                                
                                delay(20000);
                                digitalWrite(Relay,HIGH);
                                Serial.println("ALARM OFF");
                                delay(40000);
                             
                      }



                        if(currentTime.Hour() == IOnHourmrngend && currentTime.Minute() == IOnMinmrngend && value==1){
                                digitalWrite(Relay,LOW);
                                Serial.println("ALARM ON");
                                Serial.println(str);
                                
                                delay(20000);
                                digitalWrite(Relay,HIGH);
                                Serial.println("ALARM OFF");
                                delay(40000);
                               
                      }


                               if(currentTime.Hour() == IOnHouraft && currentTime.Minute() == IOnMinaft && value==1){
                                digitalWrite(Relay,LOW);
                                Serial.println("ALARM ON");
                                Serial.println(str);
                                
                                delay(20000);
                                digitalWrite(Relay,HIGH);
                                Serial.println("ALARM OFF");
                                delay(40000);
                               
                      }



                      if(currentTime.Hour() == IOnHouraftalert && currentTime.Minute() == IOnMinaftalert && value==1){
                                digitalWrite(Relay,LOW);
                                Serial.println("ALARM ON");
                                Serial.println(str);
                                
                                delay(20000);
                                digitalWrite(Relay,HIGH);
                                Serial.println("ALARM OFF");
                                delay(40000);
                               
                      }

                      if(currentTime.Hour() == IOnHourafthalftime && currentTime.Minute() == IOnMinafthalftime && value==1){
                                digitalWrite(Relay,LOW);
                                Serial.println("ALARM ON");
                                Serial.println(str);
                                
                                delay(20000);
                                digitalWrite(Relay,HIGH);
                                Serial.println("ALARM OFF");
                                delay(40000);
                                
                      }



                      if(currentTime.Hour() == IOnHouraftlastalert && currentTime.Minute() == IOnMinaftlastalert && value==1){
                                digitalWrite(Relay,LOW);
                                Serial.println("ALARM ON");
                                Serial.println(str);
                                
                                delay(20000);
                                digitalWrite(Relay,HIGH);
                                Serial.println("ALARM OFF");
                                delay(40000);
                                
                      }



                        if(currentTime.Hour() == IOnHouraftend && currentTime.Minute() == IOnMinaftend && value==1){
                                digitalWrite(Relay,LOW);
                                Serial.println("ALARM ON");
                                Serial.println(str);
                                
                                delay(20000);
                                digitalWrite(Relay,HIGH);
                                Serial.println("ALARM OFF");
                                delay(40000);
                                
                      }
  
                       if(currentTime.Hour() == OnHouronRequestE1 && currentTime.Minute() == OnMinonRequestE1 && value==2)
                     {
                              digitalWrite(Relay,LOW);
                              Serial.println("ALARM ON");
                              Serial.println(str);
                              delay(20000);
                              digitalWrite(Relay,HIGH);
                              Serial.println("ALARM OFF");
                               OnHouronRequest1=25;           //some junk is given in those values as 25 for now in hour and min
                               OnMinonRequest1=25;

                              Serial.println(str);
                     }

                         if(currentTime.Hour() == OnHouronRequestE2 && currentTime.Minute() == OnMinonRequestE2 && value==2)
                     {
                              digitalWrite(Relay,LOW);
                              Serial.println("ALARM ON");
                              Serial.println(str);
                              delay(20000);
                              digitalWrite(Relay,HIGH);
                              Serial.println("ALARM OFF");
                               OnHouronRequest2=25;           //some junk is given in those values as 25 for now in hour and min
                               OnMinonRequest2=25;

                             
                      }

                           if(currentTime.Hour() == OnHouronRequestE3 && currentTime.Minute() == OnMinonRequestE3 && value==2)
                     {
                              digitalWrite(Relay,LOW);
                              Serial.println("ALARM ON");
                              Serial.println(str);
                              delay(20000);
                              digitalWrite(Relay,HIGH);
                              Serial.println("ALARM OFF");
                             OnHouronRequest3=25;           //some junk is given in those values as 25 for now in hour and min
                             OnMinonRequest3=25;

                             
                      }

                      
                      if(currentTime.Hour() == OnHouronRequestE4 && currentTime.Minute() == OnMinonRequestE4 && value==2)
                     {
                              digitalWrite(Relay,LOW);
                              Serial.println("ALARM ON");
                              Serial.println(str);
                              delay(20000);
                              digitalWrite(Relay,HIGH);
                              Serial.println("ALARM OFF");
                              OnHouronRequest4=25;           //some junk is given in those values as 25 for now in hour and min
                               OnMinonRequest4=25;
                             
                      }

                       if(currentTime.Hour() == OnHouronRequestE5 && currentTime.Minute() == OnMinonRequestE5 && value==2)
                     {
                              digitalWrite(Relay,LOW);
                              Serial.println("ALARM ON");
                              Serial.println(str);
                              delay(20000);
                              digitalWrite(Relay,HIGH);
                              Serial.println("ALARM OFF");
                             OnHouronRequest5=25;           //some junk is given in those values as 25 for now in hour and min
                            OnMinonRequest5=25;
                              
                      }

                        if(currentTime.Hour() == OnHouronRequestE6 && currentTime.Minute() == OnMinonRequestE6 && value==2)
                     {
                              digitalWrite(Relay,LOW);
                              Serial.println("ALARM ON");
                              Serial.println(str);
                              delay(20000);
                              digitalWrite(Relay,HIGH);
                              Serial.println("ALARM OFF");
                              OnHouronRequest6=25;           //some junk is given in those values as 25 for now in hour and min
                             OnMinonRequest6=25;

                                      
                              
                      }

                      
                      if(currentTime.Hour() == EOnHourmrng && currentTime.Minute() == EOnMinmrng && value==2){
                                digitalWrite(Relay,LOW);
                                Serial.println("ALARM ON");
                                Serial.println(str);
                                
                                delay(20000);
                                digitalWrite(Relay,HIGH);
                                Serial.println("ALARM OFF");
                                delay(40000);
                                
                      }



                      if(currentTime.Hour() == EOnHourmrngalert && currentTime.Minute() == EOnMinmrngalert && value==2){
                                digitalWrite(Relay,LOW);
                                Serial.println("ALARM ON");
                                Serial.println(str);
                                
                                delay(20000);
                                digitalWrite(Relay,HIGH);
                                Serial.println("ALARM OFF");
                                delay(40000);
                                
                      }

                      if(currentTime.Hour() == EOnHourmrnghalftime && currentTime.Minute() == EOnMinmrnghalftime && value==2){
                                digitalWrite(Relay,LOW);
                                Serial.println("ALARM ON");
                                Serial.println(str);
                                
                                delay(20000);
                                digitalWrite(Relay,HIGH);
                                Serial.println("ALARM OFF");
                                delay(40000);
                                
                      }



                      if(currentTime.Hour() == EOnHourmrnglastalert && currentTime.Minute() == EOnMinmrnglastalert && value==2){
                                digitalWrite(Relay,LOW);
                                Serial.println("ALARM ON");
                                Serial.println(str);
                                
                                delay(20000);
                                digitalWrite(Relay,HIGH);
                                Serial.println("ALARM OFF");
                                delay(40000);
                                
                      }



                        if(currentTime.Hour() == EOnHourmrngend && currentTime.Minute() == EOnMinmrngend && value==2){
                                digitalWrite(Relay,LOW);
                                Serial.println("ALARM ON");
                                Serial.println(str);
                                
                                delay(20000);
                                digitalWrite(Relay,HIGH);
                                Serial.println("ALARM OFF");
                                delay(40000);
                                
                      }


                               if(currentTime.Hour() == EOnHouraft && currentTime.Minute() == EOnMinaft && value==2){
                                digitalWrite(Relay,LOW);
                                Serial.println("ALARM ON");
                                Serial.println(str);
                                
                                delay(20000);
                                digitalWrite(Relay,HIGH);
                                Serial.println("ALARM OFF");
                                delay(40000);
                                
                      }



                      else if(currentTime.Hour() == EOnHouraftalert && currentTime.Minute() == EOnMinaftalert && value==2){
                                digitalWrite(Relay,LOW);
                                Serial.println("ALARM ON");
                                Serial.println(str);
                                
                                delay(20000);
                                digitalWrite(Relay,HIGH);
                                Serial.println("ALARM OFF");
                                delay(40000);
                               
                      }

                     else if(currentTime.Hour() == EOnHourafthalftime && currentTime.Minute() == EOnMinafthalftime && value==2){
                                digitalWrite(Relay,LOW);
                                Serial.println("ALARM ON");
                                Serial.println(str);
                                
                                delay(20000);
                                digitalWrite(Relay,HIGH);
                                Serial.println("ALARM OFF");
                                delay(40000);
                                
                      }



                     else if(currentTime.Hour() == EOnHouraftlastalert && currentTime.Minute() == EOnMinaftlastalert && value==2){
                                digitalWrite(Relay,LOW);
                                Serial.println("ALARM ON");
                                Serial.println(str);
                                
                                delay(20000);
                                digitalWrite(Relay,HIGH);
                                Serial.println("ALARM OFF");
                                delay(40000);
                                
                      }



                        else if(currentTime.Hour() == EOnHouraftend && currentTime.Minute() == EOnMinaftend && value==2){
                                digitalWrite(Relay,LOW);
                                Serial.println("ALARM ON");
                                Serial.println(str);
                                
                                delay(20000);
                                digitalWrite(Relay,HIGH);
                                Serial.println("ALARM OFF");
                                delay(40000);
                                
                      }



                      
                      
 // Serial.println(str);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 // Check if a client has connected
WiFiClient client = ESPserver.available();
if (!client) 
{
return;
}

// Wait until the client sends some data
Serial.println("New Client");
while(!client.available())
{
delay(1);
}

// Read the first line of the request
String request = client.readStringUntil('\r');
Serial.println(request);
client.flush();

// Match the request





                        if (request.indexOf("/INTERNAL") != -1) 
                        {
                            value = 1;
                            Serial.println(str);
                            Serial.println(value);
                        } 
                        if (request.indexOf("/EXTERNAL") != -1)
                        {
                        
                            value = 2;
                            Serial.println(str);
                            
                        }
                        if(request.indexOf("/BACK") != -1)
                        {
                          value=0;
                          Serial.println(str);
                          
                          }
                        if(request.indexOf("/REGULAR") != -1)
                        {
                          value=0;
                          Serial.println(str);
                          }

                        if(request.indexOf("/TURNOFF") != -1)
                        {
                        
                            value = 5;
                            Serial.println(str);
                            
                        }
  

//  Serial.println(OnHouronRequest);
//  Serial.println(OnMinonRequest);
//  

    Serial.println(value);


                          if (request.indexOf("/RELAYON") != -1 && value==0) 
                        {
                            Serial.println("ALARM is ON");
                            digitalWrite(Relay, LOW);
                            Serial.println(str);
                        } 
                        if (request.indexOf("/RELAYOFF") != -1 && value==0)
                        {
                              Serial.println("ALARM is OFF");
                              digitalWrite(Relay, HIGH);
                              
                              Serial.println(str);
                        }
                        if(request.indexOf("/TIME") != -1 )
                        {
                                //Serial.println(packet);   
                                String p1=request.substring(10,13);
                                String p2=request.substring(13,15);
                                 OnHouronRequest=p1.toInt();
                                 OnMinonRequest=p2.toInt();
                                 Serial.println(str);
                                Serial.println(OnHouronRequest);
                                Serial.println(OnMinonRequest);
                          } 
                     



                                ////////////now for internal

                                 if (request.indexOf("/RELAYONINTERNAL") != -1 && value==1) 
                        {
                            
                            Serial.println("ALARM is ON");
                            digitalWrite(Relay, LOW);
                            Serial.println(str);
                                                    
                        } 
                        if (request.indexOf("/RELAYOFFINTERNAL") != -1 && value==1)
                        {
                            Serial.println("ALARM is OFF");
                            digitalWrite(Relay, HIGH);
                            Serial.println(str);
                        }
//                        //1

                         if(request.indexOf("/TIMEI1") != -1 && value==1 )
                        {
                                //Serial.println(packet);   
                                String p1=request.substring(12,15);
                                String p2=request.substring(15,17);
                                 OnHouronRequest1=p1.toInt();
                                 OnMinonRequest1=p2.toInt();
                                 Serial.println(str);
                                Serial.println(OnHouronRequest1);
                                Serial.println(OnMinonRequest1);
                          } 
//                     
                          
                      //2
//                         
                           if(request.indexOf("/TIMEI2") != -1 && value==1 )
                        {
                                //Serial.println(packet);   
                                String p1=request.substring(12,15);
                                String p2=request.substring(15,17);
                                 OnHouronRequest2=p1.toInt();
                                 OnMinonRequest2=p2.toInt();
                                 Serial.println(str);
                                Serial.println(OnHouronRequest2);
                                Serial.println(OnMinonRequest2);
                          } 
                         
                      //3
//                          
                           if(request.indexOf("/TIMEI3") != -1 && value==1 )
                        {
                                //Serial.println(packet);   
                                String p1=request.substring(12,15);
                                String p2=request.substring(15,17);
                                 OnHouronRequest3=p1.toInt();
                                 OnMinonRequest3=p2.toInt();
                                 Serial.println(str);
                                Serial.println(OnHouronRequest3);
                                Serial.println(OnMinonRequest3);
                          } 
                      
                      //4
//                          
                       if(request.indexOf("/TIMEI4") != -1 && value==1 )
                        {
                                //Serial.println(packet);   
                                String p1=request.substring(12,15);
                                String p2=request.substring(15,17);
                                 OnHouronRequest4=p1.toInt();
                                 OnMinonRequest4=p2.toInt();
                                 Serial.println(str);
                                Serial.println(OnHouronRequest4);
                                Serial.println(OnMinonRequest4);
                          } 
                      //5
//                        
                           if(request.indexOf("/TIMEI5") != -1 && value==1 )
                        {
                                //Serial.println(packet);   
                                String p1=request.substring(12,15);
                                String p2=request.substring(15,17);
                                 OnHouronRequest5=p1.toInt();
                                 OnMinonRequest5=p2.toInt();
                                 Serial.println(str);
                                Serial.println(OnHouronRequest5);
                                Serial.println(OnMinonRequest5);
                          } 
                     
                      //6
//                     
                        if(request.indexOf("/TIMEI6") != -1 && value==1 )
                        {
                                //Serial.println(packet);   
                                String p1=request.substring(12,15);
                                String p2=request.substring(15,17);
                                 OnHouronRequest6=p1.toInt();
                                 OnMinonRequest6=p2.toInt();
                                 Serial.println(str);
                                Serial.println(OnHouronRequest6);
                                Serial.println(OnMinonRequest6);

                                                        } 


                      


                        
                      

                      //////////////////EXTERNAL STARTS HERE

                       if (request.indexOf("/RELAYONEXTERNAL") != -1 && value==2) 
                         {
                            Serial.println("ALARM is ON");
                            digitalWrite(Relay, LOW);
                            Serial.println(str);
                        } 
                        if (request.indexOf("/RELAYOFFEXTERNAL") != -1 && value==2)
                        {
                              Serial.println("ALARM is OFF");
                              digitalWrite(Relay, HIGH);
                              Serial.println(str);
                        }
                        //1
//                        
                           if(request.indexOf("/TIMEE1") != -1 && value==2 )
                        {
                                //Serial.println(packet);   
                                String p1=request.substring(12,15);
                                String p2=request.substring(15,17);
                                 OnHouronRequest5=p1.toInt();
                                 OnMinonRequest5=p2.toInt();
                                 Serial.println(str);
                                Serial.println(OnHouronRequest5);
                                Serial.println(OnMinonRequest5);
                          } 
                         
                      //2
//                           
                           if(request.indexOf("/TIMEE2") != -1 && value==2 )
                        {
                                //Serial.println(packet);   
                                String p1=request.substring(12,15);
                                String p2=request.substring(15,17);
                                 OnHouronRequest5=p1.toInt();
                                 OnMinonRequest5=p2.toInt();
                                 Serial.println(str);
                                Serial.println(OnHouronRequest5);
                                Serial.println(OnMinonRequest5);
                          } 
                       
                      //3
//                         
                            if(request.indexOf("/TIMEE3") != -1 && value==2 )
                        {
                                //Serial.println(packet);   
                                String p1=request.substring(12,15);
                                String p2=request.substring(15,17);
                                 OnHouronRequest3=p1.toInt();
                                 OnMinonRequest3=p2.toInt();
                                 Serial.println(str);
                                Serial.println(OnHouronRequest3);
                                Serial.println(OnMinonRequest3);
                          } 
                      
                      //4
//                        
                           if(request.indexOf("/TIMEE4") != -1 && value==2)
                        {
                                //Serial.println(packet);   
                                String p1=request.substring(12,15);
                                String p2=request.substring(15,17);
                                 OnHouronRequest5=p1.toInt();
                                 OnMinonRequest5=p2.toInt();
                                 Serial.println(str);
                                Serial.println(OnHouronRequest5);
                                Serial.println(OnMinonRequest5);
                          } 
                           
                      //5
//                       
                           if(request.indexOf("/TIMEE5") != -1 && value==2 )
                        {
                                //Serial.println(packet);   
                                String p1=request.substring(12,15);
                                String p2=request.substring(15,17);
                                 OnHouronRequest5=p1.toInt();
                                 OnMinonRequest5=p2.toInt();
                                 Serial.println(str);
                                Serial.println(OnHouronRequest5);
                                Serial.println(OnMinonRequest5);
                          } 
                          
                      //6
//                      
                           if(request.indexOf("/TIMEE6") != -1 && value==2 )
                        {
                                //Serial.println(packet);   
                                String p1=request.substring(12,15);
                                String p2=request.substring(15,17);
                                 OnHouronRequest6=p1.toInt();
                                 OnMinonRequest6=p2.toInt();
                                 Serial.println(str);
                                Serial.println(OnHouronRequest6);
                                Serial.println(OnMinonRequest6);
                          } 
                         

// Return the response
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println(""); //  IMPORTANT
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          
          client.print("Status of the Lamp: ");
          
          
          
          delay(1);
          client.stop();
          Serial.println("Client disconnected");
          Serial.println("");
        
 }
   




//----------------------------------------------- Fuctions used for WiFi credentials saving and connecting to it which you do not need to change 
bool testWifi(void)
{
  int c = 0;
  Serial.println("Waiting for Wifi to connect");
  while ( c < 20 ) {
    if (WiFi.status() == WL_CONNECTED)
    {
      return true;
    }
    delay(500);
    Serial.print("*");
    c++;
  }
  Serial.println("");
  Serial.println("Connect timed out, opening AP");
  return false;
}

void launchWeb()
{
  Serial.println("");
  if (WiFi.status() == WL_CONNECTED)
    Serial.println("WiFi connected");
  Serial.print("Local IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("SoftAP IP: ");
  Serial.println(WiFi.softAPIP());
  createWebServer();
  // Start the server
  server.begin();
  Serial.println("Server started");
}

void setupAP(void)
{
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0)
    Serial.println("no networks found");
  else
  {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i)
    {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*");
      delay(10);
    }
  }
  Serial.println("");
  st = "<ol>";
  for (int i = 0; i < n; ++i)
  {
    // Print SSID and RSSI for each network found
    st += "<li>";
    st += WiFi.SSID(i);
    st += " (";
    st += WiFi.RSSI(i);
    st += ")";
    st += (WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*";
    st += "</li>";
  }
  st += "</ol>";
  delay(100);
  WiFi.softAP("BMSIT", "Bmsit@123");
  Serial.println("softap");
  launchWeb();
  Serial.println("over");
}

void createWebServer()
{
 {
    server.on("/", []() {

      IPAddress ip = WiFi.softAPIP();
      String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
      content = "<!DOCTYPE HTML>\r\n<html>Hello from ESP8266 at";
       content += " ";
      content += ipStr;
      content += "<form action=\"/scan\" method=\"POST\"><input type=\"submit\" value=\"scan\"></form>";
      content += "<p>";
      content += st;
      content += "</p><form method='post' action='setting'><label>SSID: </label><input name='ssid' length=32><input name='pass' length=64><input type='submit'></form>";
      content += "</html>";
      server.send(200, "text/html", content);
    });
    server.on("/scan", []() {
      setupAP();
      IPAddress ip = WiFi.softAPIP();
      String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);

      content = "<!DOCTYPE HTML>\r\n<html>go back";
      server.send(200, "text/html", content);
    });

    server.on("/setting", []() {
      String qsid = server.arg("ssid");
      String qpass = server.arg("pass");
      if (qsid.length() > 0 && qpass.length() > 0) {
        Serial.println("clearing eeprom");
        for (int i = 0; i < 96; ++i) {
          EEPROM.write(i, 0);
        }
        Serial.println(qsid);
        Serial.println("");
        Serial.println(qpass);
        Serial.println("");

        Serial.println("writing eeprom ssid:");
        for (int i = 0; i < qsid.length(); ++i)
        {
          EEPROM.write(i, qsid[i]);
          Serial.print("Wrote: ");
          Serial.println(qsid[i]);
        }
        Serial.println("writing eeprom pass:");
        for (int i = 0; i < qpass.length(); ++i)
        {
          EEPROM.write(32 + i, qpass[i]);
          Serial.print("Wrote: ");
          Serial.println(qpass[i]);
        }
        EEPROM.commit();

        content = "{\"Success\":\"saved to eeprom... reset to boot into new wifi\"}";
        statusCode = 200;
        ESP.reset();
      } else {
        content = "{\"Error\":\"404 not found\"}";
        statusCode = 404;
        Serial.println("Sending 404");
      }
      server.sendHeader("Access-Control-Allow-Origin", "*");
      server.send(statusCode, "application/json", content);

    });
  } 
} 


void printResult(FirebaseData &data)
{

  if (data.dataType() == "int")
    Serial.println(data.intData());
  else if (data.dataType() == "float")
    Serial.println(data.floatData(), 5);
  else if (data.dataType() == "double")
    printf("%.9lf\n", data.doubleData());
  else if (data.dataType() == "boolean")
    Serial.println(data.boolData() == 1 ? "true" : "false");
  else if (data.dataType() == "string")
    Serial.println(data.stringData());
  else if (data.dataType() == "json")
  {
    Serial.println();
    FirebaseJson &json = data.jsonObject();
    //Print all object data
    Serial.println("Pretty printed JSON data:");
    String jsonStr;
    json.toString(jsonStr, true);
    Serial.println(jsonStr);
    Serial.println();
    Serial.println("Iterate JSON data:");
    Serial.println();
    size_t len = json.iteratorBegin();
    String key, value = "";
    int type = 0;
    for (size_t i = 0; i < len; i++)
    {
      json.iteratorGet(i, type, key, value);
      Serial.print(i);
      Serial.print(", ");
      Serial.print("Type: ");
      Serial.print(type == FirebaseJson::JSON_OBJECT ? "object" : "array");
      if (type == FirebaseJson::JSON_OBJECT)
      {
        Serial.print(", Key: ");
        Serial.print(key);
      }
      Serial.print(", Value: ");
      Serial.println(value);
    }
    json.iteratorEnd();
  }
  else if (data.dataType() == "array")
  {
    Serial.println();
    //get array data from FirebaseData using FirebaseJsonArray object
    FirebaseJsonArray &arr = data.jsonArray();
    //Print all array values
    Serial.println("Pretty printed Array:");
    String arrStr;
    arr.toString(arrStr, true);
    Serial.println(arrStr);
    Serial.println();
    Serial.println("Iterate array values:");
    Serial.println();
    for (size_t i = 0; i < arr.size(); i++)
    {
      Serial.print(i);
      Serial.print(", Value: ");

      FirebaseJsonData &jsonData = data.jsonData();
      //Get the result data from FirebaseJsonArray object
      arr.get(jsonData, i);
      if (jsonData.typeNum == FirebaseJson::JSON_BOOL)
        Serial.println(jsonData.boolValue ? "true" : "false");
      else if (jsonData.typeNum == FirebaseJson::JSON_INT)
        Serial.println(jsonData.intValue);
      else if (jsonData.typeNum == FirebaseJson::JSON_FLOAT)
        Serial.println(jsonData.floatValue);
      else if (jsonData.typeNum == FirebaseJson::JSON_DOUBLE)
        printf("%.9lf\n", jsonData.doubleValue);
      else if (jsonData.typeNum == FirebaseJson::JSON_STRING ||
               jsonData.typeNum == FirebaseJson::JSON_NULL ||
               jsonData.typeNum == FirebaseJson::JSON_OBJECT ||
               jsonData.typeNum == FirebaseJson::JSON_ARRAY)
        Serial.println(jsonData.stringValue);
    }
  }
  else if (data.dataType() == "blob")
  {

    Serial.println();

    for (int i = 0; i < data.blobData().size(); i++)
    {
      if (i > 0 && i % 16 == 0)
        Serial.println();

      if (i < 16)
        Serial.print("0");

      Serial.print(data.blobData()[i], HEX);
      Serial.print(" ");
    }
    Serial.println();
  }
  else if (data.dataType() == "file")
  {

    Serial.println();

    File file = data.fileStream();
    int i = 0;

    while (file.available())
    {
      if (i > 0 && i % 16 == 0)
        Serial.println();

      int v = file.read();

      if (v < 16)
        Serial.print("0");

      Serial.print(v, HEX);
      Serial.print(" ");
      i++;
    }
    Serial.println();
    file.close();
  }
  else
  {
    Serial.println(data.payload());
  }
}
