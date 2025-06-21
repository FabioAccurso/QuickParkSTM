#ifndef INC_SENSORS_H_
#define INC_SENSORS_H_

#include "main.h"
#include "stm32f3xx_hal.h"

void sensors_init(void);
void sensors_update(void);
int sensors_get_free_slots(void);
int updateCloseEntry(void);
void setCloseEntry(int x);

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

#endif /* INC_SENSORS_H_ */
