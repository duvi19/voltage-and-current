#ifndef testsensor
#define testsensor

#define sampling_size 10
/*
    How to calibrate sensors using mapf function

    float mapf(double val, double in_min, double in_max, double out_min, double out_max) {
    return float((val - in_min) * (out_max - out_min) / (in_max - in_min) + out_min); }

    mapf takes in
    1) sensor reading
    2) minimum input value
    3) maximum input value
    4) minimum mapped valued
    5) maximum mapped value
    ex: Arduino ADC's range is 0-1023 using 10 bit precision
    if we have a sensor that registers -30 to 30 Amps, we can map it as following:
    
    float actual_value= mapf((analogRead(ADCpin), 0, 1023, -30, 30);

    However, to get minimum and maximum mapped values, we need to do some testing

    You need a multimeter to perform these tests

    Step 1: Get raw sensor reading at 0 Amps/Volts

    Step 2: If working with voltage, set multimeter in parallel with sernsor
            If working with current, set multimeter in series with sensor
    
    Step 3: Get both sensor and multimeter reading at another voltage/Amp
            ex: multimeter says 9.54V and raw reading is 573
    
    Then we need to get the actual range of the sensor as it relates to the ADC range
    ex: 
        if we know that raw 774 corresponds to 0V
        and 573 corresponds to actual 9.54V 
    
    then we can solve for the actual range of the sensor
    774 - 573 = 201
    201/9.54V <=> 1023/ x, where x is the range of the sensor
    x= 48.55V
    Upper limit of the range is (774/1023)48.55 = 36.73V
    Lower limit = -(48.55 - 36.73)= -11.81V

    At the end, we have all of our values for the mapping function

    1) sensor reading = analogRead(ADCpin)
    2) minimum input value = 0
    3) maximum input value = 1023
    4) minimum mapped valued = -11.81
    5) maximum mapped value = 36.73

    NOTE: The minimum and maximum mapped values are obtained experimentally as per the method described above
    Every sensor will have different mins and maximums

    This can be applied to any sensor that uses an ADC
*/

float mapf(double val, double in_min, double in_max, double out_min, double out_max) {
    return float((val - in_min) * (out_max - out_min) / (in_max - in_min) + out_min); }

/*
    ex: testing current at pin A0
    testSensor("Battery Current", A0, -10.72, 32);
*/
void testSensor(string type, int pin, int min, int max){
    Serial.println("-----     Testing %s     -----", type);
    int x= analogRead(pin); //get reading
    Serial.println("Reading at pin %d: is %d", pin, x); 

    // Map function is used
    float y= mapf(x1, 0, 1023, min, max);
    Serial.println("Mapped value at pin %d is : %f", pin, y); 
}

// Current Recommended min= -10.72
// Current Recommended max=  32
float getCurrent(int pin, int min, int max)){

    float total = 0;
    for(int i=0; i < sampling_size; i++ ){
        total += analogRead(pin);
        delay(1);
    }
    return mapf(1023 - (total/sampling_size), 0, 1023, min, max);
}

// Voltage Recommended min=  -11.745
// Voltage Recommended max=   36.73
float getVoltage(int pin, int min, int max)){

    float total = 0;
    for(int i=0; i < sampling_size; i++ ){
        total += analogRead(pin);
        delay(1);
    }
    return mapf(1023 - (total/sampling_size), 0, 1023, min, max);
}



#endif
