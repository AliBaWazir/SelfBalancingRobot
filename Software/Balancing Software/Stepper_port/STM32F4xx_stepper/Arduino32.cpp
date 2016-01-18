#include "Arduino32.h"
#include "tm_stm32f4_delay.h"


uint32_t micros(void){
    return 1;
    
}


void pinMode(uint8_t, uint8_t){
    
}
void digitalWrite(uint8_t, uint8_t){
}
int digitalRead(uint8_t){
    return 1;
}
    
int analogRead(uint8_t){
    return 1;
}
void analogReference(uint8_t mode){
    
}
void analogWrite(uint8_t, int){
    
}

void delayMicroseconds(unsigned int us){
    Delay(us);
    return;
}
unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout){
    return 1;
}
