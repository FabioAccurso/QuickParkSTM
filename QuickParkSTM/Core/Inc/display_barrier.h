#ifndef INC_DISPLAY_BARRIER_H_
#define INC_DISPLAY_BARRIER_H_

#include "stm32f3xx_hal.h"

void display_init(void); //Funzione che inizializza il PWM per i servomotori e lcd (I2C)
void Servo_Set_Angle(uint8_t angle); //Funzione per impostare angolo dei servomotori (90 gradi)
void Servo_Entrance_Close(void); //Funzione per chiudere il servomotore di ingresso
void Servo_Entrance_Open(void); //Funzione per aprire il servomotore di ingresso
void Servo_Exit_Close(void); //Funzione per chiudere il servomotore di uscita
void Servo_Exit_Open(void); //Funzione per aprire il servomotore di uscita
void Display_Write(void); //Funzione per stampare a schermo su lcd

#endif /* INC_DISPLAY_BARRIER_H_ */
