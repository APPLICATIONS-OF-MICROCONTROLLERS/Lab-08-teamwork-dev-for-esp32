#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "led.h"

static const char *TAG = "MAIN";

void app_main(void)
{
    ESP_LOGI(TAG, "Starting Lab08-67030021 application");
    
    // Initialize LED
    if (led_init() != ESP_OK) {
        ESP_LOGE(TAG, "Failed to initialize LED");
        return;
    }
    
    // Demo LED states
    ESP_LOGI(TAG, "LED Demo starting...");
    
    while (1) {
        // Turn on LED
        ESP_LOGI(TAG, "LED ON");
        led_on();
        vTaskDelay(pdMS_TO_TICKS(2000));
        
        // Turn off LED
        ESP_LOGI(TAG, "LED OFF");
        led_off();
        vTaskDelay(pdMS_TO_TICKS(2000));
        
        // Blinking mode
        ESP_LOGI(TAG, "LED BLINKING");
        led_set_state(LED_STATE_BLINK);
        vTaskDelay(pdMS_TO_TICKS(5000));
        
        // Pulse mode
        ESP_LOGI(TAG, "LED PULSE");
        led_set_state(LED_STATE_PULSE);
        vTaskDelay(pdMS_TO_TICKS(5000));
        
        // Turn off
        led_off();
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
