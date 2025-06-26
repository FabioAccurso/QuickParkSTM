#include "wifi_bot.h"
#include "usart.h"      // Per usare huart2
#include "sensors.h"    // Per accedere a sensors_get_free_slots()
#include <stdio.h>
#include <string.h>

static uint32_t last_sent = 0;           // Timestamp invio precedente
static const uint32_t send_interval = 3000; // intervallo invio in ms

void wifi_bot_init(void) {
    // Nessuna inizializzazione necessaria
}

void wifi_bot_handle(void) {
    uint32_t now = HAL_GetTick();
    if (now - last_sent < send_interval) {
        return; // troppo presto per inviare di nuovo
    }

    last_sent = now;

    int free_slots = sensors_get_free_slots();
    char buffer[32];
    snprintf(buffer, sizeof(buffer), "POSTI:%d\n", free_slots);

    HAL_UART_Transmit(&huart3, (uint8_t*)buffer, strlen(buffer), HAL_MAX_DELAY);
}
