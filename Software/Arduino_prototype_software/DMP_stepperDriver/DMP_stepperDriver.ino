//

#include <PID_v1.h>
#include "TimerOne.h"



#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include <AccelStepper.h>

AccelStepper stepper(AccelStepper::DRIVER,4,5); 
//Define Variables we'll be connecting to
double Setpoint=0, Input=0, Output=0;
double pSetpoint, pInput, pOutput;

//Specify the links and initial tuning parameters
PID myPID(&Input, &Output, &Setpoint,5.5,45,0.00022, DIRECT);
PID pPID(&pInput, &pOutput, &pSetpoint,35,5 ,15, DIRECT);
//PID pPID(&pInput, &pOutput, &pSetpoint,0.001,0.05,0.0005, DIRECT);


//uint32_t driveSpeed = 0;
//uint32_t driveCounter = 4294967295;

MPU6050 mpu;

#define LED_PIN 13 // (Arduino is 13, Teensy is 11, Teensy++ is 6)
bool blinkState = false;

// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint32_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint32_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

// orientation/motion vars
Quaternion q;           // [w, x, y, z]         quaternion container
VectorInt16 aa;         // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector
float euler[3];         // [psi, theta, phi]    Euler angle container
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector


// ================================================================
// ===               INTERRUPT DETECTION ROUTINE                ===
// ================================================================

volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
void dmpDataReady() {
    mpuInterrupt = true;
}
//int dir = 0;
int32_t stepCounter = 0;
//double speedglobal;
// ================================================================
// ===                      INITIAL SETUP                       ===
// ================================================================
double firstValue = 0;
double secondValue = 0;
double thirdValue = 0;
void setup() {
  
     stepper.setMaxSpeed(10001);
    
  
  
  
  
    // join I2C bus (I2Cdev library doesn't do this automatically)
    Wire.begin();

  
    // initialize serial communication
    // (115200 chosen because it is required for Teapot Demo output, but it's
    // really up to you depending on your project)
    Serial.begin(9600);
    while (!Serial); // wait for Leonardo enumeration, others continue immediately

    mpu.initialize();

    devStatus = mpu.dmpInitialize();
    
    // make sure it worked (returns 0 if so)
    if (devStatus == 0) {
        // turn on the DMP, now that it's ready
        Serial.println(F("Enabling DMP..."));
        mpu.setDMPEnabled(true);

        // enable Arduino interrupt detection
        //Serial.println(F("Enabling interrupt detection (Arduino external interrupt 0)..."));
        attachInterrupt(0, dmpDataReady, RISING);
        mpuIntStatus = mpu.getIntStatus();

        // set our DMP Ready flag so the main loop() function knows it's okay to use it
        //Serial.println(F("DMP ready! Waiting for first interrupt..."));
        dmpReady = true;

        // get expected DMP packet size for later comparison
        packetSize = mpu.dmpGetFIFOPacketSize();
        //Serial.println(mpu.getRate());

    } else {
        // ERROR!
        // 1 = initial memory load failed
        // 2 = DMP configuration updates failed
        // (if it's going to break, usually the code will be 1)
        //Serial.print(F("DMP Initialization failed (code "));
        //Serial.print(devStatus);
        //Serial.println(F(")"));
    }
    
    // configure LED for output3
    pinMode(LED_PIN, OUTPUT);
    
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
   
    Timer1.initialize(1000000/1000/18);         // initialize timer1, and set a 1/2 second period
    Timer1.attachInterrupt(callback);
    myPID.SetMode(AUTOMATIC);
    myPID.SetSampleTime(5);
    myPID.SetOutputLimits(-100, 100);
    pPID.SetMode(AUTOMATIC);
    pPID.SetSampleTime(100);
    pPID.SetOutputLimits(-10000, 10000);
   //stepper.targetPosition(0);
}



// ================================================================
// ===                    MAIN PROGRAM LOOP                     ===
// ================================================================
double angle = 0;
int directionAngle = 0;
int mark = 0;
double value1 = 0;
double value2 = 0;
//double value3 = 0;
double influence = 0;
double invalue1 = 0;
double invalue2 = 0;
double invalue3 = 0;
int counter_p = 1;

void PIDloop(){
  if(mark = 1){
  
           if(millis()>4000){
            //Serial.print("ypr\t");
            
            /*
            Serial.print(ypr[0] * 180/M_PI);
            Serial.print("\t");
            Serial.print(ypr[1] * 180/M_PI);
            Serial.print("\t");
            Serial.print(ypr[2] * 180/M_PI);
            */
          
          firstValue= (ypr[1]);
          secondValue = firstValue;
          thirdValue = secondValue;
          
                  

                  angle = ((0.7)*firstValue+(0.2)*secondValue+(0.1)*thirdValue)*100;
                  
                  
                  if((angle >(15.0))||(angle < (-35.0))){
                  set_speed(0);
                  }
                  else{
           //Serial.print("agl ");
           //Serial.print(angle);
           /*
           //Serial.print("\t");
            
            
            Serial.print(angle);
            Serial.print("\t");
            Serial.print("DirectionAngle");
            Serial.print(directionAngle);
            
            */
            invalue1 = stepper.distanceToGo()/10;
            invalue2 = invalue1;
            invalue3 = invalue2;
            
            
            
            Input = angle;
            //if((abs(stepper.distanceToGo()/100))>500){
              // stepper.setCurrentPosition(0);   
      
            //}
            
            //Serial.print(stepper.distanceToGo()/10);
            //Serial.print("\t");
            if(counter_p <0){
              pInput =  stepper.distanceToGo()/10;//(invalue3+invalue2+invalue1)/3;
              pSetpoint = 0;
 
              pPID.Compute();
              value1 = pOutput;
              value2 = value1;
              //value3 = value2;
              pOutput =(value1+value2)/2;
              //Serial.print("\t");
              //Serial.print(pOutput);
            //Serial.println("\t");
              influence =((3000-abs(stepper.speed()))/3000.0);
              counter_p = 4;
              
            }
            counter_p--;
            
            
            if((stepper.speed()>0 && stepper.distanceToGo() >0)||(stepper.speed()<0 && stepper.distanceToGo() <0)){
              Setpoint =  -10.0+ (influence*-1*(pOutput/1000));
              //Serial.println("yes");
            } 
            else{
              Setpoint =  -10.0+ (-1*(pOutput/1000));
              //Serial.println("no");
            }

            myPID.Compute();

            
            set_speed(-1*(Output*100));
           }
           }

  mark = 0;  
  }
      
}
byte byteRead;
int returned = 0;
void loop() {
  PIDloop();
    if (Serial.available()) {
    /* read the most recent byte */
    byteRead = Serial.read();
    /*ECHO the value that was read, back to the serial port. */
    returned = (byteRead-'0')*1000;
    if(returned < 10000){
    Serial.println(stepper.targetPosition()+((byteRead-'0')*1000)-5000);
    stepper.moveTo(stepper.targetPosition()+((byteRead-'0')*1000)-5000);
    }
    }
    
    
    
    // if programming failed, don't try to do anything
    if (!dmpReady) return;

    // wait for MPU interrupt or extra packet(s) available
    while (!mpuInterrupt && fifoCount < packetSize) {
        
      
    }

    // reset interrupt flag and get INT_STATUS byte
    mpuInterrupt = false;
    mpuIntStatus = mpu.getIntStatus();

    // get current FIFO count
    fifoCount = mpu.getFIFOCount();

    // check for overflow (this should never happen unless our code is too inefficient)
    if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
        // reset so we can continue cleanly
        mpu.resetFIFO();
        Serial.println(F("FIFO overflow!"));

    // otherwise, check for DMP data ready interrupt (this should happen frequently)
    } else if (mpuIntStatus & 0x01) {
        // wait for correct available data length, should be a VERY short wait
        while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();

        // read a packet from FIFO
        mpu.getFIFOBytes(fifoBuffer, packetSize);
        
        // track FIFO count here in case there is > 1 packet available
        // (this lets us immediately read more without waiting for an interrupt)
        fifoCount -= packetSize;

 // display Euler angles in degrees
            mpu.dmpGetQuaternion(&q, fifoBuffer);
            mpu.dmpGetGravity(&gravity, &q);
            mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
        
        
//delay(1);
        // blink LED to indicate activity
        //blinkState = !blinkState;
        //digitalWrite(LED_PIN, blinkState);
    }
    
}

void set_speed(double sp){
  stepper.setSpeed(sp);
  
}

int counter = 0;
void callback()
{
        
        
       if(counter > 260){
       mark = 1;
       counter = 0;
       }
       stepper.runSpeed();
       counter++;

}
