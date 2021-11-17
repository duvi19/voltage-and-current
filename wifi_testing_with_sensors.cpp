#include "Firebase_Arduino_WiFiNINA.h"
#define FIREBASE_HOST "peacearduinodatamkrwifi1010-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "d2R2Lseo5KVCEtw0E45GWt3ZVBajki9bcXCz8h3u"

FirebaseData firebaseData;
#include <WiFiNINA.h>

char WIFI_SSID[] = "Samsung";        // your network SSID (name)
char WIFI_PASSWORD[] = "freefree";    // your network password (use for WPA, or use as key for WEP)
int status = WL_IDLE_STATUS;     // the Wifi radio's status

#define sensornum 62n_min) + out_min);


void setup() {
  Serial.begin(9600);
  while(!Serial);

   pinMode (A2, OUTPUT);
  pinMode (A3, OUTPUT);

   // connect to wifi.
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to network: \n ");
    status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    delay(1000);
  }
  
  Serial.println("You're connected to the network");
  Serial.println("----------------------------------------");
  Serial.println("----------------------------------------");
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH, WIFI_SSID, WIFI_PASSWORD);
  Firebase.reconnectWiFi(true);
}
 



float mapf(double val, double in_min, double in_max, double out_min, double out_max) {
    return float((val - in_min) * (out_max - out_min) / (in_max - in_min) + out_min);
}


void loop() 
{
  static unsigned int n = 0; //this is only to name the logs by numbering them
  String Numbuffer, VNumbuffer, CNumNumbuffer;
  Numbuffer = String(n);
{

   
  float voltage0 = analogRead(A0);// map 0-1023 to actual voltage range
  Serial.println(voltage0);
  float voltage1 = mapf(1023-voltage0-12,0,1023, -12.11, 38.89);
  Serial.println(voltage1);

  float voltage2 = analogRead(A1);// map 0-1023 to actual voltage range
  Serial.println(voltage2);
  float voltage3 = mapf(1023-voltage2-12,0,1023, -12.11, 38.89);
  Serial.println(voltage3);


  float current0 = analogRead(A2);// map 0-1023 to actual current range
  Serial.println(current0);
  float current1 = mapf(current0, 1023, 0, -10.72, 32);
  Serial.println(current1);

  float current2 = analogRead(A3);// map 0-1023 to actual current range
  Serial.println(current0);
  float current3 = mapf(current2, 1023, 0, -10.72, 32);
  Serial.println(current1);

  

  Serial.println("");

// append new sensor values to /logs
  Firebase.setFloat(firebaseData,Numbuffer + "/VoltagePV",         voltage1);
  Firebase.setFloat(firebaseData,Numbuffer + "/VoltageBattery",    voltage3);
  Firebase.setFloat(firebaseData,Numbuffer + "/CurrentPV",         current1);
  Firebase.setFloat(firebaseData,Numbuffer + "/CurrentBattery",    current3);


   
   
 //Firebase.setTimestamp(firebaseData,Numbuffer+ "/Timestamp" );
  
 //Open/Close relays according to the mode in the database
 // unsigned int Mode = Firebase.getInt(firebaseData, "Mode");

  
  n++;  
  delay(100);
}
}
