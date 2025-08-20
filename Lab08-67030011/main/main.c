#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_system.h"
#include "esp_log.h"
#include "sensor.h"

static const char *TAG = "MAIN";

void app_main(void)
{
    ESP_LOGI(TAG, "Starting Lab08-67030011 application");
    
    // Initialize sensor
    if (sensor_init() != ESP_OK) {
        ESP_LOGE(TAG, "Failed to initialize sensor");
        return;
    }
    
    // Create sensor task
    xTaskCreate(sensor_task, "sensor_task", 4096, NULL, 5, NULL);
    
    // Main loop to read sensor data
    sensor_data_t sensor_data;
    
    while (1) {
        // Wait for sensor data from queue
        if (xQueueReceive(sensor_queue, &sensor_data, pdMS_TO_TICKS(5000)) == pdTRUE) {
            ESP_LOGI(TAG, "Received sensor data:");
            ESP_LOGI(TAG, "  ADC Value: %lu", sensor_data.adc_value);
            ESP_LOGI(TAG, "  Voltage: %.2fV", sensor_data.voltage);
            ESP_LOGI(TAG, "  Temperature: %.2f°C", sensor_data.temperature);
        } else {
            ESP_LOGW(TAG, "No sensor data received");
        }
    }
}
