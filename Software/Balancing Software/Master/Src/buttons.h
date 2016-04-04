#include "application_main.h"
#include "tm_stm32_button.h"

#define BUTTONLEFTPIN       GPIO_PIN_0
#define BUTTONRIGHTPIN      GPIO_PIN_1
extern void setCalibrateFlag(uint8_t);
void setupButtons(void);
void updateButtons(void);
extern void setState(uint8_t);
