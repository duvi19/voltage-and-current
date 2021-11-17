const int numReadings = 30;
float readings[numReadings]; // the readings from the analog input
int myindex = 0; // the index of the current reading
float total = 0; // the running total
float average = 0; // the average
float currentValue = 0;
void setup()
{
 Serial.begin(115200);
 for (int thisReading = 0; thisReading < numReadings; thisReading++)
 readings[thisReading] = 0;
}
void loop()
{
 total= total - readings[myindex];
 readings[myindex] = analogRead(0); //Raw data reading
//Data processing:510-raw data from analogRead when the input is 0;
// 5-5v; the first 0.04-0.04V/A(sensitivity); the second 0.04-offset val;
readings[myindex] = (readings[myindex]-789.5)*5/1024/0.06-0.03;

 total= total + readings[myindex];
 myindex = myindex + 1 ;
 if (myindex >= numReadings)
 myindex = 0;
 average = total/numReadings; //Smoothing algorithm (http://www.arduino.cc/en/Tutorial/Smoothing)
 currentValue= average;
 Serial.println(currentValue,3);
 delay(100); 
}
