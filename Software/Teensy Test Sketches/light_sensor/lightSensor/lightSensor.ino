/*
  Analog input, analog output, serial output

 Reads an analog input pin, maps the result to a range from 0 to 255
 and uses the result to set the pulsewidth modulation (PWM) of an output pin.
 Also prints the results to the serial monitor.

 The circuit:
 * potentiometer connected to analog pin 0.
   Center pin of the potentiometer goes to the analog pin.
   side pins of the potentiometer go to +5V and ground
 * LED connected from digital pin 9 to ground

 created 29 Dec. 2008
 modified 9 Apr 2012
 by Tom Igoe

 This example code is in the public domain.

 */

// These constants won't change.  They're used to give names
// to the pins used:
const int analogInPin = A2;  // Analog input pin that the LIDAR is attached to
const int exposurePin = 15;  // digial sampling pin
const int clkPin = 14;  // digial sampling pin

int sensorValue = 0;        // value read from the pot


void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
 
  pinMode(exposurePin, OUTPUT);
  pinMode(clkPin, OUTPUT);

  pinMode(analogInPin, INPUT);
  
}

void loop() {
  // set the clk LOW
  digitalWrite(clkPin, LOW);
  delayMicroseconds(50);
  digitalWrite(exposurePin, HIGH);
  delayMicroseconds(50);
  digitalWrite(clkPin, HIGH);
  
  
  delayMicroseconds(1);
  //do the exposure
  digitalWrite(exposurePin, HIGH);
  delayMicroseconds(1);
  
  digitalWrite(exposurePin, LOW);
  
  Serial.print("sensor = ");
  for (int i=0; i<129; i++){
    digitalWrite(clkPin, HIGH);
    delayMicroseconds(50);
    
    // read the analog in value:
    sensorValue = analogRead(analogInPin);

  
    // print the results to the serial monitor:
    
    Serial.print(sensorValue);
    Serial.print(",");
    

    
    digitalWrite(clkPin, LOW);
    delayMicroseconds(50);


    
    
  }
  Serial.println("");

  delay(10);
}
