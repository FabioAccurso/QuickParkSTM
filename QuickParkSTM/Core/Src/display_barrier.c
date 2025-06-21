#include "display_barrier.h"
#include "stdio.h"

extern TIM_HandleTypeDef htim3; // es. per servo (TIM3-CH1 e CH2)
#define SERVO_ENTRY_CHANNEL TIM_CHANNEL_1
#define SERVO_EXIT_CHANNEL  TIM_CHANNEL_2

// Valori PWM per posizione servo
#define SERVO_UP   25  // es. 2.5% duty cycle
#define SERVO_DOWN 75  // es. 7.5% duty cycle

void display_init(void) {
    // Avvia i PWM per i due servo
    HAL_TIM_PWM_Start(&htim3, SERVO_ENTRY_CHANNEL);
    HAL_TIM_PWM_Start(&htim3, SERVO_EXIT_CHANNEL);

    // Inizialmente abbassa entrambe le sbarre
    barrier_close_entry();
    barrier_close_exit();

    //inizializza display
    display_update(0);
}

void display_update(uint8_t free_spots) {
    // Per debug: stampa via UART
    printf("Posti liberi: %d\r\n", free_spots);

    // In alternativa: aggiorna display fisico
    // lcd_clear();
    // lcd_printf("Free: %d", free_spots);
}



// --- Sbarre ingresso ---

void barrier_open_entry(void) {
    __HAL_TIM_SET_COMPARE(&htim3, SERVO_ENTRY_CHANNEL, SERVO_UP);
}

void barrier_close_entry(void) {
    __HAL_TIM_SET_COMPARE(&htim3, SERVO_ENTRY_CHANNEL, SERVO_DOWN);
}

// --- Sbarre uscita ---

void barrier_open_exit(void) {
    __HAL_TIM_SET_COMPARE(&htim3, SERVO_EXIT_CHANNEL, SERVO_UP);
}

void barrier_close_exit(void) {
    __HAL_TIM_SET_COMPARE(&htim3, SERVO_EXIT_CHANNEL, SERVO_DOWN);
}
