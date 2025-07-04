#include "display_barrier.h"
#include "lcd_i2c.h"
#include "sensors.h"

#define SERVO_UP 500
#define SERVO_DOWN 1500

extern TIM_HandleTypeDef htim1; // Riferimento alla nostra interfaccia TIM1

void servo_init(void){
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1); //Inizializza il PWM per il servomotore di ingresso
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2); //Inizializza il PWM per il servomotore di uscita
	Servo_Entrance_Close();
	Servo_Exit_Close();
}

void display_init(void){
	lcd_init(); // Inizializza il display
	lcd_put_cur(0, 0);
	lcd_send_string("QuickParkSTM");
	lcd_put_cur(1, 0);
	lcd_send_string("WELCOME!");
	HAL_Delay(3000);
	Display_Write();
}

void Servo_Entrance_Close(void){
	// Imposta la posizione iniziale a 0 gradi
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, SERVO_DOWN);
}

void Servo_Exit_Close(void){
	// Imposta la posizione iniziale a 0 gradi
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, SERVO_DOWN);
}

void Servo_Entrance_Open(void){
	// Imposta la posizione desiderata a 90 gradi
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, SERVO_UP);
}

void Servo_Exit_Open(void){
	// Imposta la posizione desiderata a 90 gradi
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, SERVO_UP);
}

void Display_Write(void){
	/*lcd_put_cur(0, 0); // Posiziona il cursore alla riga 0, colonna 0
	lcd_send_string("QuickParkSTM");*/
	if(sensors_get_free_slots() > 0){
		lcd_clear();
		lcd_put_cur(1, 0); // Posiziona il cursore alla riga 1, colonna 0
		char buffer[32];
		snprintf(buffer, sizeof(buffer), "Slot Left: %d", sensors_get_free_slots());
		lcd_send_string(buffer);
	}
	else{
		lcd_put_cur(1, 0); // Posiziona il cursore alla riga 1, colonna 0
		lcd_send_string("Parking Full");
	}

}
