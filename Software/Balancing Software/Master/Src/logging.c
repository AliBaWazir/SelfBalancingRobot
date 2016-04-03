#include "logging.h"


char logArray[1024];

void setupLog(){
    
    
    TM_USART_Init(UARTTEENSY, TM_USART_PinsPack_2, 115200);
    TM_USART_Init(UARTFTDI, TM_USART_PinsPack_1, 115200);
    
    sendV100(32);
    
}


void sendV100(uint8_t command){
    TM_USART_Putc(UARTFTDI,ESC);
    TM_USART_Putc(UARTFTDI,command);
    
}

void writeLog(char* name,double num){
    
    char str[5];
    sprintf(str, "%d", (int)num);
    
    TM_USART_Puts(UARTFTDI, name);
    TM_USART_Puts(UARTFTDI, " = ");
    TM_USART_Puts(UARTFTDI, str);
    TM_USART_Puts(UARTFTDI, " ");
    
}

void logNewLine(){
    TM_USART_Putc(UARTFTDI, '\n');
}
