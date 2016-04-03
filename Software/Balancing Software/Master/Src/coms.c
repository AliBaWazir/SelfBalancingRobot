#include "coms.h"


struct teensyData{
    int8_t packetId;
    int8_t packetId2;
    int8_t leftMotorSteps;
    int8_t rightMotorSteps;
    
}incomingData;

void parseCommands(void){
    uint8_t data = TM_USART_Getc(UARTTEENSY);
    while(data){
        if(data == 0xEF){
            data = TM_USART_Getc(UARTTEENSY);
            if(data == 0xFE){
                incomingData.leftMotorSteps = TM_USART_Getc(UARTTEENSY);
                incomingData.rightMotorSteps = TM_USART_Getc(UARTTEENSY);
                TM_USART_Putc(UARTFTDI, 0x20);
                TM_USART_Putc(UARTFTDI, incomingData.leftMotorSteps);
                TM_USART_Putc(UARTFTDI, incomingData.rightMotorSteps);
                TM_USART_Putc(UARTFTDI, 0x0A);
                
            }
        }
        else data = TM_USART_Getc(UARTTEENSY);
    }
    
    
    
}
