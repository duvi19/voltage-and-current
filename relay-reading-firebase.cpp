/*READ FIRST:
 
  If Arduino cant connect to Firebase, check fingerprint of header file obtained from https://www.grc.com/fingerprints.htm when firebase.com was typed
  https://create.arduino.cc/projecthub/OscarF10/mkr-wifi-1010-firebase-9a7399
  https://flaviocopes.com/arduino-board-mkr-wifi-1010/
  https://store.arduino.cc/usa/mkr-wifi-1010
  https://www.arduino.cc/en/Guide/MKRWiFi1010/connecting-to-wifi-network
  https://content.arduino.cc/assets/mkr-microchip_samd21_family_full_datasheet-ds40001882d.pdf
  Private Repo https://github.com/jcsp2407/EPMS
  https://github.com/mobizt/Firebase-Arduino-WiFiNINA
  Install WiFiNINA Library https://github.com/arduino-libraries/WiFiNINA
  Board: Go to board manager and type: "Arduino SAMD (32-bits ARM Cortex-M0+ Boards)"

  8 Digital I/O pins, pins 0 - 7.
  7 Analog Input pins (ADC 8/10/12 bit), pins A0 / A6.
  1 Analog Output pin (DAC 10 bit), the pin identified with DAC0/A0.
  Pins 0, 1, 2, 3, 4, 5, 6, 7, 8, 10, 12, 18, 19 are PWM pins.
  
*/
  
#include "Firebase_Arduino_WiFiNINA.h"
#define FIREBASE_HOST "epms-49c09-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "kHiK9tHwajNrUUl9LYu7abXi6ZHyZZMABv8jfaHj"
FirebaseData firebaseData;
String jsonStr;

#include <WiFiNINA.h>
char WIFI_SSID[] = "SECRET_SSID";        // your network SSID (name)
char WIFI_PASSWORD[] = "SECRET_PASS";    // your network password (use for WPA, or use as key for WEP)
int status = WL_IDLE_STATUS;     // the Wifi radio's status

//PINOUT
#define PV_voltage_pin    A0
#define BAT_voltage_pin   A1
#define TemperatureC_pin  A2
#define PV_current_pin    A3
#define BAT_current_pin   A4
#define LOAD_current_pin  A5
#define RELAY1             8  //Battery
#define RELAY2            10 //Connected to the Grid
//END OF PINOUT

//TESTED VALUES FOR CONTROLLING THE RELAYS LOCALLY, WITHOUT FIREBASE
#define BAT_LOWER_V       23
#define BAT_UPPER_V       24
#define PV_LOWER_V        31
#define PV_UPPER_V        33

float mapf(double val, double in_min, double in_max, double out_min, double out_max) { return float((val - in_min) * (out_max - out_min) / (in_max - in_min) + out_min); }

void setup() {
//  Serial.begin(9600);
//  while(!Serial);
 
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  // connect to wifi.
  while (status != WL_CONNECTED) {
   // Serial.print("Attempting to connect to network: ");
    status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    delay(5000);
  }
  //Serial.println("Successfully connected to the network!");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH, WIFI_SSID, WIFI_PASSWORD);
  Firebase.reconnectWiFi(true);
}

void loop() {
  static unsigned long n = 0; //this is only to name the logs by numbering them

  float PV_voltage =   mapf(1023- analogRead(PV_voltage_pin)  ,0 , 1023 , -11.745 , 36.73);// map 0-1023 to actual voltage range
  float PV_current =   (analogRead(PV_current_pin)-789.5)*5/1023/0.06-0.03; 
  float BAT_voltage =  mapf(1023- analogRead(BAT_voltage_pin)  ,0 , 1023 , -11.745 , 36.73);// 
  float BAT_current =  (analogRead(BAT_current_pin)-789.5)*5/1023/0.06-0.03;
  float LOAD_current = (analogRead(LOAD_current_pin)-789.5)*5/1023/0.06-0.03;
  float TemperatureC = ((analogRead(TemperatureC_pin)/1024.0) * 3000)/10 - 5; //In Celsius
  float TemperatureF =  ((TemperatureC*9)/5 +32); //in Farenheit 

  // append new sensor values to /logs
  Firebase.setFloat(firebaseData,String(n) + "/PV_voltage",    PV_voltage);
  Firebase.setFloat(firebaseData,String(n) + "/PV_current",    PV_current);
  Firebase.setFloat(firebaseData,String(n) + "/BAT_voltage",   BAT_voltage);
  Firebase.setFloat(firebaseData,String(n) + "/BAT_current",   BAT_current);
  Firebase.setFloat(firebaseData,String(n) + "/LOAD_current",  LOAD_current);
  Firebase.setFloat(firebaseData,String(n) + "/TemperatureC",  TemperatureC);
  Firebase.setTimestamp(firebaseData,String(n)+ "/Timestamp" );
  
  //Open/Close relays according to the mode in the database
 if(Firebase.getInt(firebaseData, "Mode") ){
    unsigned int Mode = firebaseData.intData();
    switch (Mode){
    
     case 0: 
     //Save the power of the battery bank (open relay 1)
       digitalWrite(RELAY1, 0);
       digitalWrite(RELAY2, 0);
       break;
        
     case 1: 
     //Charge the battery bank or Use power of the battery bank (at night or during rainy days) (Close relay 1)
       digitalWrite(RELAY1, 1);
       digitalWrite(RELAY2, 0);
       break;
     
     case 2: 
     //send power back to the grid. (Close relay 2).
       digitalWrite(RELAY1, 0);
       digitalWrite(RELAY2, 1);
       break;
     
     default: 
     //Charge the battery bank or Use power of the battery bank (at night or during rainy days) (Close relay 1)
       digitalWrite(RELAY1, 1);
       digitalWrite(RELAY2, 0);
       break;
    }
 }
 else{ //cant establish communication with firebase, so handle locally
    
    if( (abs(BAT_voltage - BAT_UPPER_V) < 1) && (PV_voltage >PV_UPPER_V) ){
      //send power back to the grid. (Close relay 2).
      digitalWrite(RELAY1, 0);
      digitalWrite(RELAY2, 1);
     }
    else if( (BAT_voltage >BAT_LOWER_V) && (PV_voltage >BAT_LOWER_V) ){
      //Save the power of the battery bank (open relay 1)
      digitalWrite(RELAY1, 0);
      digitalWrite(RELAY2, 0);
      }
    else{
      //Charge the battery bank or Use power of the battery bank (at night or during rainy days) (Close relay 1)
      digitalWrite(RELAY1, 1);
      digitalWrite(RELAY2, 0);
     }
    
 }
    
  n++;
  delay(5000);
}
