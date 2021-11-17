#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

///////////////////////////////////////////////////////////////////////////////////////////////
//                IMPORTANT                
// Change Firebase fingerprint to 50:89:50:57:90:1F:37:E3:B8:F3:5B:02:ED:3A:65:6E:6A:34:DB:93
// Obtained from https://www.grc.com/fingerprints.htm when firebase.com was typed
///////////////////////////////////////////////////////////////////////////////////////////////

// Set these to run example.
#define FIREBASE_HOST "esp8266-databaseconnection-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "uyZH9X9OwuvWQ8P7PCbuEztcS3la53tK5wvBok05"
#define WIFI_SSID "Lok Family"
#define WIFI_PASSWORD "ncnc5958"

void setup() {
  Serial.begin(9600);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

int n = 0;

void loop() {
  
  Firebase.setString("message", "Goodmorning Dr Sarwat, Dr Deepal, Hugo");
  Firebase.setFloat("voltage", 12.0);
  Firebase.setFloat("current", 0.66);
  delay(500);
  Firebase.setFloat("voltage", 12.2);
  Firebase.setFloat("current", 0.65);
  delay(500);
  Firebase.setFloat("voltage", 12.0);
  Firebase.setFloat("current", 0.64);
  delay(500);
  Firebase.setFloat("voltage", 12.1);
  Firebase.setFloat("current", 0.65);
  delay(500);
  Firebase.setString("message", "My team made me do all the work again");
  Firebase.setFloat("voltage", 12.2);
  Firebase.setFloat("current", 0.66);
  delay(500);
  Firebase.setFloat("voltage", 12.0);
  Firebase.setFloat("current", 0.67);
  delay(500);
  Firebase.setFloat("voltage", 12.1);
  Firebase.setFloat("current", 0.65);
  delay(500);

  // get value 
  Serial.print("voltage: ");
  Serial.print("current: ");
  Serial.println(Firebase.getFloat("voltage"));
  Serial.println(Firebase.getFloat("current"));


  // append a new value to /logs
  String name = Firebase.pushInt("logs", n++);
  // handle error
  if (Firebase.failed()) {
      Serial.print("pushing /logs failed:");
      Serial.println(Firebase.error());  
      return;
  }
  Serial.print("pushed: /logs/");
  Serial.println(name);
}
