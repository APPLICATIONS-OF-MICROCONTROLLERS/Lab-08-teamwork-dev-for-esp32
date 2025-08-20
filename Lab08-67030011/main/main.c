#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_system.h"
#include "esp_log.h"
#include "sensor.h"
#include "display.h"

static const char *TAG = "MAIN";

void app_main(void)
{
    ESP_LOGI(TAG, "Starting Lab08-67030011 application");
    
    // Initialize sensor
    if (sensor_init() != ESP_OK) {
        ESP_LOGE(TAG, "Failed to initialize sensor");
        return;
    }
    
    // Initialize display
    if (display_init() != ESP_OK) {
        ESP_LOGE(TAG, "Failed to initialize display");
        return;
    }
    
    // Create sensor task
    xTaskCreate(sensor_task, "sensor_task", 4096, NULL, 5, NULL);
    
    // Main loop to read sensor data and display
    sensor_data_t sensor_data;
    
    while (1) {
        // Wait for sensor data from queue
        if (xQueueReceive(sensor_queue, &sensor_data, pdMS_TO_TICKS(5000)) == pdTRUE) {
            ESP_LOGI(TAG, "Received sensor data:");
            ESP_LOGI(TAG, "  ADC Value: %lu", sensor_data.adc_value);
            ESP_LOGI(TAG, "  Voltage: %.2fV", sensor_data.voltage);
            ESP_LOGI(TAG, "  Temperature: %.2f°C", sensor_data.temperature);
            
            // Display sensor data on screen
            display_clear();
            display_show_text("Sensor Data:", 0, 0);
            
            char temp_str[32];
            snprintf(temp_str, sizeof(temp_str), "Temp: %.1f°C", sensor_data.temperature);
            display_show_text(temp_str, 0, 20);
            
            char volt_str[32];
            snprintf(volt_str, sizeof(volt_str), "Volt: %.2fV", sensor_data.voltage);
            display_show_text(volt_str, 0, 40);
            
            char adc_str[32];
            snprintf(adc_str, sizeof(adc_str), "ADC: %lu", sensor_data.adc_value);
            display_show_text(adc_str, 0, 60);
            
            display_update();
        } else {
            ESP_LOGW(TAG, "No sensor data received");
        }
    }
}
