#include "display_barrier.h"
#include "lcd_i2c.h"
#include "sensors.h"

#define SERVO_UP 1500
#define SERVO_DOWN 500

extern TIM_HandleTypeDef htim1; // Riferimento alla nostra interfaccia TIM1

void display_init(void){
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1); //Inizializza il PWM per il servomotore di ingresso
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2); //Inizializza il PWM per il servomotore di uscita
	lcd_init(); // Inizializza il display
	Servo_Entrance_Close();
	Servo_Exit_Close();
	lcd_put_cur(0, 0);
	lcd_send_string("QuickParkSTM");
	lcd_put_cur(1, 0);
	lcd_send_string("WELCOME!");
	HAL_Delay(3000);
	Display_Write();
}

/*void Servo_Set_Angle(uint8_t angle){
    if (angle > 180) angle = 180;

    // Converti angolo in tempo in µs (500 µs → 2500 µs)
    uint16_t pulse_length = 500 + ((angle * 2000) / 180);

    // Imposta il valore del compare register
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, pulse_length);
}*/

void Servo_Entrance_Close(void){
	// Imposta la posizione iniziale a 0 gradi (impulso di 500)
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, SERVO_DOWN);
}

void Servo_Exit_Close(void){ //DA MODIFICARE TIM_CHANNEL
	// Imposta la posizione iniziale a 0 gradi (impulso di 500)
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, SERVO_DOWN);
}

void Servo_Entrance_Open(void){
	// Imposta la posizione desiderata a 90 gradi (impulso di 1500)
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, SERVO_UP);
}

void Servo_Exit_Open(void){ //DA MODIFICARE TIM_CHANNEL
	// Imposta la posizione desiderata a 90 gradi (impulso di 1500)
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, SERVO_UP);
}

void Display_Write(void){
	/*lcd_put_cur(0, 0); // Posiziona il cursore alla riga 0, colonna 0
	lcd_send_string("QuickParkSTM");*/
	if(sensors_get_free_slots() > 0){
		lcd_put_cur(1, 0); // Posiziona il cursore alla riga 1, colonna 0
		char buffer[32];
		snprintf(buffer, sizeof(buffer), "Slot Left: %d", sensors_get_free_slots());
		lcd_send_string(buffer);
	}
	else{
		lcd_put_cur(1, 0); // Posiziona il cursore alla riga 1, colonna 0
		lcd_send_string("Parking Full :(");
	}

}
