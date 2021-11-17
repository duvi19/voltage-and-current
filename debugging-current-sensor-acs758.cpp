#define acs758 A1
//0.019x + -14.767, x is raw data, output is actual current

void setup()
{
  pinMode(acs758, INPUT);
  Serial.begin(57600);
  
  }
void loop(){

    int counts = analogRead(acs758);
    float voltage = counts * vpp;
     float amps= counts*0.042 - 32.97;
     Serial.print("Actual: "); Serial.println(amps);
        delay(1000);
}
