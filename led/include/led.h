#ifndef LED_H
#define LED_H

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

// LED Configuration
#define LED_GPIO GPIO_NUM_2  // Built-in LED on most ESP32 boards
#define LED_ON  0            // Active low
#define LED_OFF 1

// LED states
typedef enum {
    LED_STATE_OFF = 0,
    LED_STATE_ON,
    LED_STATE_BLINK,
    LED_STATE_PULSE
} led_state_t;

// Function declarations
esp_err_t led_init(void);
esp_err_t led_set_state(led_state_t state);
esp_err_t led_toggle(void);
esp_err_t led_on(void);
esp_err_t led_off(void);
void led_blink_task(void *pvParameters);
void led_pulse_task(void *pvParameters);

#endif // LED_H
