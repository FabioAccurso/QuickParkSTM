#ifndef INC_LCD_I2C_H_
#define INC_LCD_I2C_H_

#include "stm32f3xx_hal.h"

void lcd_init (void);   // Inizializza l'LCD
void lcd_send_cmd (char cmd);  // Invia un comando
void lcd_send_data (char data);  // Invia un dato (carattere)
void lcd_send_string (char *str);  // Invia una stringa
void lcd_put_cur(int row, int col);  // Posiziona il cursore
void lcd_clear (void); // Pulisce lo schermo

#endif /* INC_LCD_I2C_H_ */
