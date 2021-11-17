const int voltageSensor = A0;

const int numReadings = 30;
float readings[numReadings];      // the readings from the analog input
int my_index = 0;                  // the my_index of the current reading
float total = 0;                  // the running total
float average = 0;                // the average

float vOUT = 0.0;


void setup()
{
  Serial.begin(57600);
  Serial.println("Voltage Readings: ");
  for (int thisReading = 0; thisReading < numReadings; thisReading++)
    readings[thisReading] = 0;   
}

void loop()
{
  total -= readings[my_index];
  readings[my_index] = analogRead(voltageSensor); //Raw data reading
  readings[my_index] = (833 - readings[my_index])/22;
  total+= readings[my_index]; 
  my_index += 1;                    
    if (my_index >= numReadings)              
      my_index = 0;              
  average = total/numReadings;
  
  Serial.print("\nVoltage:\t");
  Serial.print(average);
  
  delay(30);
}
