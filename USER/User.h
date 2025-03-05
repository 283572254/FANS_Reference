#ifndef _USER_H_
#define _USER_H_

#include "main.h"



typedef struct
{
    uint8_t button1;
    uint8_t button2;
    uint8_t button3;
} UserButton;
void User_Init(void);
void User_Loop(void);
UserButton Button_Output(void);

#endif //  _USER_H_

