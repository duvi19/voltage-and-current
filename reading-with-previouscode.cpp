#include "Firebase_Arduino_WiFiNINA.h"
//#define FIREBASE_HOST "duilioepms-default-rtdb.firebaseio.com"
//#define FIREBASE_AUTH "DoYQuVOORMljLW1d8Os8sJvMrIESVwMK4YbiS3VH"
#define FIREBASE_HOST "epms-49c09-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "kHiK9tHwajNrUUl9LYu7abXi6ZHyZZMABv8jfaHj"
FirebaseData firebaseData;
String jsonStr;

#include <WiFiNINA.h>
//#include "arduino_secrets.h"
char WIFI_SSID[] = "Samsung";        // your network SSID (name)
char WIFI_PASSWORD[] = "freefree";    // your network password (use for WPA, or use as key for WEP)
int status = WL_IDLE_STATUS;     // the Wifi radio's status

//#define sensornum 62n_min) + out_min);

//voltage PV//
//const int voltageSensor = A1;
//const int numReadings1 = 5;
//float readings1[numReadings1];      // the readings from the analog input
//int my_indexvoltage = 0;                  // the my_index of the current reading
//float totalvoltage = 0;                  // the running total
//float averagevoltage = 0;                // the average

//voltageBattery//
const int voltageSensor1 = A2;
const int numReadings3 = 5;
float readings3[numReadings3];      // the readings from the analog input
int my_indexvoltage3 = 0;                  // the my_index of the current reading
float totalvoltage3 = 0;                  // the running total
float averagevoltage3 = 0;                // the average

//current PV//
//const int numReadings2 = 30;
//float readings2[numReadings2]; // the readings from the analog input
//int my_indexcurrent = 0; // the index of the current reading
//float totalcurrent = 0; // the running total
//float averagecurrent = 0; // the average
//float currentValue = 0;

//current Battery//
const int numReadings4 = 30;
float readings4[numReadings4]; // the readings from the analog input
int my_indexcurrent1 = 0; // the index of the current reading
float totalcurrent1 = 0; // the running total
float averagecurrent1 = 0; // the average
float currentValue1 = 0;

//current AC//
//const int numReadings5 = 30;
//float readings5[numReadings5]; // the readings from the analog input
//int my_indexcurrent2 = 0; // the index of the current reading
//float totalcurrent2 = 0; // the running total
//float averagecurrent2 = 0; // the average
//float currentValue2 = 0;

float vOUT = 0.0;


void setup()
{

  Serial.begin(57600);
  while(!Serial);
//   Serial.println("Voltage PV Readings: ");
//  for (int thisReading1 = 0; thisReading1 < numReadings1; thisReading1++)
//    readings1[thisReading1] = 0;

   Serial.println("Voltage Battery Readings2: ");
  for (int thisReading3 = 0; thisReading3 < numReadings3; thisReading3++)
    readings3[thisReading3] = 0;

   
//   Serial.println("Current PV Readings: ");
// for (int thisReading2 = 0; thisReading2 < numReadings2; thisReading2++)
//   readings2[thisReading2] = 0; 

   Serial.println("Current Battery Readings: ");
 for (int thisReading4 = 0; thisReading4 < numReadings4; thisReading4++)
   readings4[thisReading4] = 0; 
//
//   Serial.println("Current AC Readings: ");
// for (int thisReading5 = 0; thisReading5 < numReadings5; thisReading5++)
//   readings5[thisReading5] = 0; 

   
//  Serial.begin(57600);
//  while(!Serial);
  //Serial.begin(57600);

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


// static unsigned int n = 0; //this is only to name the logs by numbering them
 // String Numbuffer, VNumbuffer, CNumNumbuffer;
 // Numbuffer = String(n);
  
//  Serial.println("Voltage Readings: ");
//  for (int thisReading1 = 0; thisReading1 < numReadings1; thisReading1++)
//    readings1[thisReading1] = 0;
//   
//   Serial.println("Current Readings: ");
// for (int thisReading2 = 0; thisReading2 < numReadings2; thisReading2++)
//   readings2[thisReading2] = 0;   


  void loop()
 {
  static unsigned int n = 0; //this is only to name the logs by numbering them
  String Numbuffer, VNumbuffer, CNumNumbuffer;
  Numbuffer = String(n);


  
//  totalvoltage -= readings1[my_indexvoltage];
//  readings1[my_indexvoltage] = analogRead(voltageSensor); //Raw data reading
//  readings1[my_indexvoltage] = (782 - readings1[my_indexvoltage])/22;
//  totalvoltage+= readings1[my_indexvoltage]; 
//  my_indexvoltage += 1;                    
//    if (my_indexvoltage >= numReadings1)              
//      my_indexvoltage = 0;              
//  averagevoltage = totalvoltage/numReadings1;
//  
//  Serial.print("\nVoltagePV:\t");
//  Serial.print(averagevoltage);

totalvoltage3 -= readings3[my_indexvoltage3];
  readings3[my_indexvoltage3] = analogRead(voltageSensor1); //Raw data reading
  readings3[my_indexvoltage3] = (782 - readings3[my_indexvoltage3])/22;
  totalvoltage3+= readings3[my_indexvoltage3]; 
  my_indexvoltage3 += 1;                    
    if (my_indexvoltage3 >= numReadings3)              
      my_indexvoltage3 = 0;              
  averagevoltage3 = totalvoltage3/numReadings3;
  
  Serial.print("\nVoltage Battery:\t");
  Serial.print(averagevoltage3);

  

//current PV//

//totalcurrent= totalcurrent - readings2[my_indexcurrent];
// readings2[my_indexcurrent] = analogRead(0); //Raw data reading
//
// readings2[my_indexcurrent] = (readings2[my_indexcurrent]-789.4)*5/1024/0.06-0.03;
//
// totalcurrent= totalcurrent + readings2[my_indexcurrent];
// my_indexcurrent = my_indexcurrent + 1 ;
// if (my_indexcurrent >= numReadings2)
// my_indexcurrent = 0;
// averagecurrent = totalcurrent/numReadings2; //Smoothing algorithm (http://www.arduino.cc/en/Tutorial/Smoothing)
// currentValue= averagecurrent;
// Serial.print("\nCurrent PV:\t");
// Serial.println(currentValue,3);

 //current BAttery//

 totalcurrent1 = totalcurrent1 - readings4[my_indexcurrent1];
 readings4[my_indexcurrent1] = analogRead(3); //Raw data reading

 readings4[my_indexcurrent1] = (readings4[my_indexcurrent1]-789.4)*5/1024/0.06-0.03;

 totalcurrent1 = totalcurrent1 + readings4[my_indexcurrent1];
 my_indexcurrent1 = my_indexcurrent1 + 1 ;
 if (my_indexcurrent1 >= numReadings4)
 my_indexcurrent1 = 0;
 averagecurrent1 = totalcurrent1/numReadings4; //Smoothing algorithm (http://www.arduino.cc/en/Tutorial/Smoothing)
 currentValue1 = averagecurrent1;
 Serial.print("\nCurrent Battery:\t");
 Serial.println(currentValue1,3);


//current AC//

// totalcurrent2= totalcurrent2 - readings5[my_indexcurrent2];
// readings5[my_indexcurrent2] = analogRead(4); //Raw data reading
//
// readings5[my_indexcurrent2] = (readings5[my_indexcurrent2]-789.4)*5/1024/0.06-0.03;
//
// totalcurrent2 = totalcurrent2 + readings5[my_indexcurrent2];
// my_indexcurrent2 = my_indexcurrent2 + 1 ;
// if (my_indexcurrent2 >= numReadings5)
// my_indexcurrent2 = 0;
// averagecurrent2 = totalcurrent2/numReadings5; //Smoothing algorithm (http://www.arduino.cc/en/Tutorial/Smoothing)
// currentValue2= averagecurrent2;
// Serial.print("\nCurrentAC:\t");
// Serial.println(currentValue2,3);


// append new sensor values to /logs
// Firebase.setFloat(firebaseData,Numbuffer + "/VoltagePV",         averagevoltage);
  Firebase.setFloat(firebaseData,Numbuffer + "/VoltageBattery",    averagevoltage3);
//  Firebase.setFloat(firebaseData,Numbuffer + "/CurrentPV",         currentValue);
  Firebase.setFloat(firebaseData,Numbuffer + "/CurrentBattery",    currentValue1);
 // Firebase.setFloat(firebaseData,Numbuffer + "/CurrentAC",         currentValue2);
   Firebase.setTimestamp(firebaseData,Numbuffer+ "/Timestamp" );
  //Open/Close relays according to the mode in the database
  unsigned int Mode = Firebase.getInt(firebaseData, "Mode");
  switch (Mode){
  }
  
  n++;  
  delay(1000);
}
