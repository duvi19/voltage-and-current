/*READ FIRST:
 
  If Arduino cant connect to Firebase, check fingerprint of header file obtained from https://www.grc.com/fingerprints.htm when firebase.com was typed
  https://create.arduino.cc/projecthub/OscarF10/mkr-wifi-1010-firebase-9a7399
  https://flaviocopes.com/arduino-board-mkr-wifi-1010/
  https://store.arduino.cc/usa/mkr-wifi-1010
  https://www.arduino.cc/en/Guide/MKRWiFi1010/connecting-to-wifi-network
  https://content.arduino.cc/assets/mkr-microchip_samd21_family_full_datasheet-ds40001882d.pdf
  Private Repo https://github.com/jcsp2407/EPMS
  
  Install WiFiNINA Library https://github.com/arduino-libraries/WiFiNINA
  Board: Go to board manager and type: "Arduino SAMD (32-bits ARM Cortex-M0+ Boards)"
  
  8 Digital I/O pins, pins 0 - 7.
  7 Analog Input pins (ADC 8/10/12 bit), pins A0 / A6.
  1 Analog Output pin (DAC 10 bit), the pin identified with DAC0/A0.
  Pins 0, 1, 2, 3, 4, 5, 6, 7, 8, 10, 12, 18, 19 are PWM pins.
  
*/
  
#include "Firebase_Arduino_WiFiNINA.h"
#define FIREBASE_HOST "duilioepms-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "DoYQuVOORMljLW1d8Os8sJvMrIESVwMK4YbiS3VH"
FirebaseData firebaseData;
String jsonStr;

#include <WiFiNINA.h>
#include "arduino_secrets.h"
char WIFI_SSID[] = "belkin.ca4";        // your network SSID (name)
char WIFI_PASSWORD[] = "a6wf2bmy";    // your network password (use for WPA, or use as key for WEP)
int status = WL_IDLE_STATUS;     // the Wifi radio's status


#define sensornum 62n_min) + out_min);

//void printWifiData(void);

void setup() {
  Serial.begin(9600);
  while(!Serial);
 
  pinMode (0, OUTPUT);
 // pinMode(Digpin[1], OUTPUT);
 // pinMode(Digpin[2], OUTPUT);
 
  // connect to wifi.
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to network: \n ");
    status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
//     printWiFiData();
    delay(5000);
  }
  
  Serial.println("You're connected to the network");
  Serial.println("----------------------------------------");
//  printWiData();
  Serial.println("----------------------------------------");
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH, WIFI_SSID, WIFI_PASSWORD);
  Firebase.reconnectWiFi(true);
}

void loop() {
  static unsigned int n = 0; //this is only to name the logs by numbering them
  String Numbuffer, VNumbuffer, CNumNumbuffer;
  Numbuffer = String(n);

  float voltage0 =      analogRead(0)-12;// map 0-1023 to actual voltage range
//  float voltage1 =      mapf(1023-analogRead(ADCpin[1])-12,0,1023, -12.11, 38.89);// 
 // float temperatureC =  ((analogRead(ADCpin[2])/1024.0) * 3000)/10 - 5; //In Celsius
 // float temperatureF =  ((temperatureC*9)/5 +32); //in Farenheit 
 // float current0 =      (analogRead(ADCpin[3])-789.5)*5/1023/0.06-0.03; 
 // float current1 =      (analogRead(ADCpin[4])-789.5)*5/1023/0.06-0.03;
 // float current2 =      (analogRead(ADCpin[5])-789.5)*5/1023/0.06-0.03;

  // append new sensor values to /logs
  Firebase.setFloat(firebaseData,Numbuffer + "/Voltage1",    voltage0);
 // Firebase.setFloat(firebaseData,Numbuffer + "/Voltage2",    voltage1);
 // Firebase.setFloat(firebaseData,Numbuffer + "/Temperature", temperatureC);
 // Firebase.setFloat(firebaseData,Numbuffer + "/Current0",    current0);
 // Firebase.setFloat(firebaseData,Numbuffer + "/Current1",    current1);
 // Firebase.setFloat(firebaseData,Numbuffer + "/Current2",    current2);

  // get value 
  //  Serial.print("voltage: ");  Serial.println(Firebase.getFloat("voltage"));

  //Open/Close relays according to the mode in the database
  unsigned int Mode = Firebase.getInt(firebaseData, "Mode");
  switch (Mode){
    
    //case 0: //Open all relays
     // digitalWrite(Digpin[0], 0);
     // digitalWrite(Digpin[1], 0);
     // digitalWrite(Digpin[2], 0);
     // break;
      
    //case 1: //Close relay 0, all others open
     // digitalWrite(Digpin[0], 1);
     // digitalWrite(Digpin[1], 0);
      //digitalWrite(Digpin[2], 0);
      //break;
      
   // case 2: //Close relay 1, all others open
     // digitalWrite(Digpin[0], 0);
    //  digitalWrite(Digpin[1], 1);
    //  digitalWrite(Digpin[2], 0);
    //  break;
      
  //  case 3: //Close relay 2, all others open
     // digitalWrite(Digpin[0], 0);
     // digitalWrite(Digpin[1], 0);
     // digitalWrite(Digpin[2], 1);
     // break;
    }
  
  
  n++;
  delay(2000);
}
