#include "led.h"

static const char *TAG = "LED";
static led_state_t current_state = LED_STATE_OFF;
static TaskHandle_t led_task_handle = NULL;

esp_err_t led_init(void)
{
    esp_err_t ret = ESP_OK;
    
    // Configure GPIO
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << LED_GPIO),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    
    ret = gpio_config(&io_conf);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to configure LED GPIO");
        return ret;
    }
    
    // Turn off LED initially
    gpio_set_level(LED_GPIO, LED_OFF);
    current_state = LED_STATE_OFF;
    
    ESP_LOGI(TAG, "LED initialized successfully on GPIO %d", LED_GPIO);
    return ESP_OK;
}

esp_err_t led_set_state(led_state_t state)
{
    esp_err_t ret = ESP_OK;
    
    // Stop existing task if any
    if (led_task_handle != NULL) {
        vTaskDelete(led_task_handle);
        led_task_handle = NULL;
    }
    
    switch (state) {
        case LED_STATE_OFF:
            gpio_set_level(LED_GPIO, LED_OFF);
            break;
            
        case LED_STATE_ON:
            gpio_set_level(LED_GPIO, LED_ON);
            break;
            
        case LED_STATE_BLINK:
            xTaskCreate(led_blink_task, "led_blink", 2048, NULL, 5, &led_task_handle);
            break;
            
        case LED_STATE_PULSE:
            xTaskCreate(led_pulse_task, "led_pulse", 2048, NULL, 5, &led_task_handle);
            break;
            
        default:
            ret = ESP_ERR_INVALID_ARG;
            break;
    }
    
    if (ret == ESP_OK) {
        current_state = state;
        ESP_LOGI(TAG, "LED state changed to %d", state);
    }
    
    return ret;
}

esp_err_t led_toggle(void)
{
    static bool led_status = false;
    led_status = !led_status;
    gpio_set_level(LED_GPIO, led_status ? LED_ON : LED_OFF);
    return ESP_OK;
}

esp_err_t led_on(void)
{
    return led_set_state(LED_STATE_ON);
}

esp_err_t led_off(void)
{
    return led_set_state(LED_STATE_OFF);
}

void led_blink_task(void *pvParameters)
{
    while (1) {
        gpio_set_level(LED_GPIO, LED_ON);
        vTaskDelay(pdMS_TO_TICKS(500));
        gpio_set_level(LED_GPIO, LED_OFF);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void led_pulse_task(void *pvParameters)
{
    while (1) {
        // Fade in
        for (int i = 0; i < 10; i++) {
            gpio_set_level(LED_GPIO, LED_ON);
            vTaskDelay(pdMS_TO_TICKS(50 * i));
            gpio_set_level(LED_GPIO, LED_OFF);
            vTaskDelay(pdMS_TO_TICKS(50 * (10 - i)));
        }
        
        // Fade out
        for (int i = 10; i > 0; i--) {
            gpio_set_level(LED_GPIO, LED_ON);
            vTaskDelay(pdMS_TO_TICKS(50 * i));
            gpio_set_level(LED_GPIO, LED_OFF);
            vTaskDelay(pdMS_TO_TICKS(50 * (10 - i)));
        }
    }
}
EOFcat > led/led.c << 'EOF'
#include "led.h"

static const char *TAG = "LED";
static led_state_t current_state = LED_STATE_OFF;
static TaskHandle_t led_task_handle = NULL;

esp_err_t led_init(void)
{
    esp_err_t ret = ESP_OK;
    
    // Configure GPIO
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << LED_GPIO),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    
    ret = gpio_config(&io_conf);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to configure LED GPIO");
        return ret;
    }
    
    // Turn off LED initially
    gpio_set_level(LED_GPIO, LED_OFF);
    current_state = LED_STATE_OFF;
    
    ESP_LOGI(TAG, "LED initialized successfully on GPIO %d", LED_GPIO);
    return ESP_OK;
}

esp_err_t led_set_state(led_state_t state)
{
    esp_err_t ret = ESP_OK;
    
    // Stop existing task if any
    if (led_task_handle != NULL) {
        vTaskDelete(led_task_handle);
        led_task_handle = NULL;
    }
    
    switch (state) {
        case LED_STATE_OFF:
            gpio_set_level(LED_GPIO, LED_OFF);
            break;
            
        case LED_STATE_ON:
            gpio_set_level(LED_GPIO, LED_ON);
            break;
            
        case LED_STATE_BLINK:
            xTaskCreate(led_blink_task, "led_blink", 2048, NULL, 5, &led_task_handle);
            break;
            
        case LED_STATE_PULSE:
            xTaskCreate(led_pulse_task, "led_pulse", 2048, NULL, 5, &led_task_handle);
            break;
            
        default:
            ret = ESP_ERR_INVALID_ARG;
            break;
    }
    
    if (ret == ESP_OK) {
        current_state = state;
        ESP_LOGI(TAG, "LED state changed to %d", state);
    }
    
    return ret;
}

esp_err_t led_toggle(void)
{
    static bool led_status = false;
    led_status = !led_status;
    gpio_set_level(LED_GPIO, led_status ? LED_ON : LED_OFF);
    return ESP_OK;
}

esp_err_t led_on(void)
{
    return led_set_state(LED_STATE_ON);
}

esp_err_t led_off(void)
{
    return led_set_state(LED_STATE_OFF);
}

void led_blink_task(void *pvParameters)
{
    while (1) {
        gpio_set_level(LED_GPIO, LED_ON);
        vTaskDelay(pdMS_TO_TICKS(500));
        gpio_set_level(LED_GPIO, LED_OFF);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void led_pulse_task(void *pvParameters)
{
    while (1) {
        // Fade in
        for (int i = 0; i < 10; i++) {
            gpio_set_level(LED_GPIO, LED_ON);
            vTaskDelay(pdMS_TO_TICKS(50 * i));
            gpio_set_level(LED_GPIO, LED_OFF);
            vTaskDelay(pdMS_TO_TICKS(50 * (10 - i)));
        }
        
        // Fade out
        for (int i = 10; i > 0; i--) {
            gpio_set_level(LED_GPIO, LED_ON);
            vTaskDelay(pdMS_TO_TICKS(50 * i));
            gpio_set_level(LED_GPIO, LED_OFF);
            vTaskDelay(pdMS_TO_TICKS(50 * (10 - i)));
        }
    }
}
