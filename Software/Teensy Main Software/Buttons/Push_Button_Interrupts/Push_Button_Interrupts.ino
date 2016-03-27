#include <digitalWriteFast.h>

/* Interrupt Example code for two-buttons */
// from: https://forum.pjrc.com/threads/31259-Teensy-3-2-pin-interupts
  /* no debouncing 
  // NOTE: I'm using hardware debounce IC.
  // Manufacturer Part Number: MAX6817EUT+T / Digi-Key Part Number: MAX6817EUT+TCT-ND /  Price 5.24$ US
  // MAX6817 ±15kV ESD-Protected, Dual , CMOS Switch Debouncer, also available MAX6816 Single / MAX6818 Octal
  // there are 63kΩ (typical) pullup resistors connected to each input */

unsigned long time;
unsigned long loop_num = 0;    // loop counter



// Pin 13: Teensy 3.x has the LED on pin 13
const int ledPin = 13;  // the number of the pin for activity-indicator

//Setup the Buttons
const int pushUp = 33;  //pushUp is button 1 (B1)
const int pushDown = 32;  //pushDown is button 2 (B2)
const int pushRight = 28; //pushRight is button 3 (B3)
const int pushLeft = 27;  //pushLeft is button 4 (B4)
 

// Variables will change:
unsigned long previousMillis = 0;        // will store last time print loop counter was updated
unsigned long interval = 1000;           // interval at which to print loop counter (milliseconds)

volatile boolean flagB1;
volatile boolean flagB2;
volatile boolean flagB3;
volatile boolean flagB4;

// ***********************************************************************************************************
// *
// *                            Power Up
// *
// *
// ***********************************************************************************************************
void setup ()
{
  Serial.begin(9600);

  pinMode(ledPin, OUTPUT); // Set pin to OUTPUT for activity-indicator.

  //TEST LED on Power Up
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWriteFast(ledPin, LOW);
  delay(1000);

  // initialize pins for interrupts.
  // On Teensy3.x, the digital pins default to disable, not inputs.
  // You need to use pinMode to make the pin act as an input.
  // INPUT_PULLUP is a Teensy extension. On regular Arduino boards, digitalWrite the only way to access the pullup resistor.

  //pinMode(BUTTON1, INPUT); // button 1 with external pull-up resistor 10Kohms connected to 3.3V
  pinMode(pushUp, INPUT); //Or INPUT_PULLUP
  pinMode(pushDown, INPUT);
  pinMode(pushRight, INPUT);
  pinMode(pushLeft, INPUT);

  /*On Teensy 3.x, interrupt 0 maps to pin 0, interrupt 1 maps to pin 1,
    interrupt 2 maps to pin 2, and so on.
    Every digital pin works with attachInterrupt.
  */
  // setup interrupts
  //RISING/HIGH/CHANGE/LOW/FALLING
  attachInterrupt (pushUp, isrpushUp, RISING);  // attach BUTTON 1 interrupt handler 
  attachInterrupt (pushDown, isrpushDown, RISING);  // attach BUTTON 2 interrupt handler
  attachInterrupt (pushRight, isrpushLeft, RISING);  // attach BUTTON 3 interrupt handler 
  attachInterrupt (pushLeft, isrpushRight, RISING);  // attach BUTTON 4 interrupt handler
}

// ***********************************************************************************************************
// *
// *                            Main Loop
// *
// *
// ***********************************************************************************************************
void loop ()
{
  if (flagB1 == true)
  {
    Serial.println("pushUp button interrupt has occurred");
    Serial.print("Time: ");
    time = millis();
    //prints time since program started
    Serial.println(time);
    ResetBUTTONFlag(); //If BUTTON interrupt has occurred, reset flag.
  }
  if (flagB2 == true)
  {
    Serial.println("pushDown interrupt has occurred");
    Serial.print("Time: ");
    time = millis();
    //prints time since program started
    Serial.println(time);
    ResetBUTTONFlag(); //If BUTTON interrupt has occurred, reset flag.
  }
  
if (flagB3 == true)
  {
    Serial.println("pushRight button interrupt has occurred");
    Serial.print("Time: ");
    time = millis();
    //prints time since program started
    Serial.println(time);
    ResetBUTTONFlag(); //If BUTTON interrupt has occurred, reset flag.
  }
  if (flagB4 == true)
  {
    Serial.println("pushLeft interrupt has occurred");
    Serial.print("Time: ");
    time = millis();
    //prints time since program started
    Serial.println(time);
    ResetBUTTONFlag(); //If BUTTON interrupt has occurred, reset flag.
  }

  // Print without using the delay() function
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis > interval) {
    // save the last time you print loop counter
    previousMillis = currentMillis;

    Serial.print("loop counter: ");
    Serial.println(loop_num);
    loop_num++;
  }
  // put your main code here, to run repeatedly:

  
}

// ***********************************************************************************************************
// *
// *                        ******* buttons Interrupt Service Routine (ISR) *******
// *
// *
// ***********************************************************************************************************
// BUTTON 1 interrupt handler
void isrpushUp ()
{
  flagB1 = true;
}  // ******** end of isr Button 1 ********

// BUTTON 2 interrupt handler
void isrpushDown ()
{
  flagB2 = true;
}  // ******* end of isr Button 2  ********

// BUTTON 3 interrupt handler
void isrpushRight ()
{
  flagB3 = true;
}  // ******** end of isr Button 3 ********

// BUTTON 4 interrupt handler
void isrpushLeft ()
{
  flagB4 = true;
}  // ******* end of isr Button 4  ********

// ***********************************************************************************************************
// *
// *                        Reset BUTTON Flag
// *
// *
// ***********************************************************************************************************
void ResetBUTTONFlag()
{
  if (flagB1 == true)//reset BUTTON 1 flag + show led activity-indicator
  {
    // BUTTON 1 interrupt has occurred
    digitalWriteFast(ledPin, HIGH); //led on / activity-indicator
    delay(10); //delay to see the led blink
    digitalWriteFast(ledPin, LOW); //led off
    flagB1 = false; //reset flag
  }
  if (flagB2 == true)//reset BUTTON 2 flag + show led activity-indicator
  {
    // BUTTON 2 interrupt has occurred
    digitalWriteFast(ledPin, HIGH); //led on / activity-indicator
    delay(10); //delay to see the led blink
    digitalWriteFast(ledPin, LOW); //led off
    flagB2 = false; //reset flag
  }
   if (flagB3 == true)//reset BUTTON 1 flag + show led activity-indicator
  {
    // BUTTON 3 interrupt has occurred
    digitalWriteFast(ledPin, HIGH); //led on / activity-indicator
    delay(10); //delay to see the led blink
    digitalWriteFast(ledPin, LOW); //led off
    flagB3 = false; //reset flag
  }
  if (flagB4 == true)//reset BUTTON 2 flag + show led activity-indicator
  {
    // BUTTON 4 interrupt has occurred
    digitalWriteFast(ledPin, HIGH); //led on / activity-indicator
    delay(10); //delay to see the led blink
    digitalWriteFast(ledPin, LOW); //led off
    flagB4 = false; //reset flag
  }
}
