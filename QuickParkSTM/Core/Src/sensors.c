#include "sensors.h"
#include "display_barrier.h"
#include "stm32f3xx_hal.h"

#define TOTAL_SPOTS 3

volatile int free_spots = TOTAL_SPOTS;
volatile int entry_detected = 0;
volatile int exit_detected = 0;
int close_entry = 0;

extern void Servo_Entrance_Open(void); // Funzioni implementate in display_barrier
extern void Servo_Exit_Open(void);
extern void Servo_Entrance_Close(void);
extern void Servo_Exit_Close(void);

// Eseguito una sola volta all’avvio
void sensors_init(void) {
    // Nessuna inizializzazione necessaria
}

void sensors_update(void) {
    // Lasciata vuota o usata se servono aggiornamenti periodici
}

int sensors_get_free_slots(void) {
    return free_spots;
}

int updateCloseEntry(void){
	return close_entry;
}

void setCloseEntry(int x){
	close_entry = x;
}

// --- GESTIONE INTERRUPT ---

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){

	if (GPIO_Pin == PS1_Pin) {  // Sensore ingresso
		GPIO_PinState state = HAL_GPIO_ReadPin(GPIOC, PS1_Pin);
		uint32_t last_seen;
		uint32_t now;
		uint32_t interval = 500;
		if (state == GPIO_PIN_RESET && !entry_detected) {
			// FALLING EDGE: ostacolo davanti al sensore
			entry_detected = 1;
			Servo_Entrance_Open();  // Alza la sbarra
			last_seen = HAL_GetTick();
		}
		else if (state == GPIO_PIN_SET && entry_detected) {
			// RISING EDGE: ostacolo andato via
			now = HAL_GetTick();
			if(now - last_seen > interval){
				entry_detected = 0;
				//Servo_Entrance_Close();  // Abbassa la sbarra
				close_entry = 1;
				free_spots--;
				Display_Write();
			}
		}
	}
	else if(GPIO_Pin == PS2_Pin){
		GPIO_PinState state = HAL_GPIO_ReadPin(GPIOC, PS2_Pin);
		if (state == GPIO_PIN_RESET && !exit_detected) {
			exit_detected = 1;
			Servo_Exit_Open();  // Alza sbarra uscita
		}
		else if (state == GPIO_PIN_SET && exit_detected) {
			exit_detected = 0;
			Servo_Exit_Close();   // Abbassa sbarra uscita
			free_spots++;
			Display_Write();
		}
	}
}



