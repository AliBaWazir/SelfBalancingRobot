//uncomment devices present
#define SDCARD
#define DISPLAY
#define SENSOR1
//uncomment mode
#define DEBUG

void setup() {
// put your setup code here, to run once:
#ifdef DEBUG
  Serial.begin(9600);
#endif

#ifdef DISPLAY
  initDisplay();
#endif

#ifdef SDCARD
  initSDCard();
#endif

}


void initDisplay(){
  // do something to initialize display. This might hang if display not present
}
void initSDCard(){
  //do something to initialize SDCARD. This might hang if display not present
}

void loop() {
  // put your main code here, to run repeatedly:
  
#ifdef DEBUG
  Serial.print("some debug variables or information");
#endif


#ifdef DISPLAY
  // Display running code 
  drawSomething("cat");                                                                
#endif

#ifdef SDCARD
  // SDCard running code
  readFile('SONG.WAV');                                                         
#endif

}

void drawSomething(String e){
  
}
void readFile(String file){
  
}

