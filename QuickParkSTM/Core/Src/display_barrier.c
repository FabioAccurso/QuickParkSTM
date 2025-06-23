#include "display_barrier.h"
#include "stdio.h"
#include "main.h"


// Valori PWM per posizione servo
#define SERVO_UP   25  // es. 2.5% duty cycle
#define SERVO_DOWN 75  // es. 7.5% duty cycle

void display_init(void) {
    // Avvia i PWM per i due servo

    // Inizialmente abbassa entrambe le sbarre

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

