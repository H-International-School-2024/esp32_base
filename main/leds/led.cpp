#include "led.hpp"
#include "esp_log.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void Led::blink_fast_handler(void* parameter) 
{
  Led* led = (Led*) parameter;
  while (true) {
    ESP_LOGI("TAG", "blink_fast_handler 1");
    // gpio_set_level(led->_pin, 1);
    vTaskDelay(pdMS_TO_TICKS(100));
    ESP_LOGI("TAG", "blink_fast_handler 2");
    // gpio_set_level(led->_pin, 0);
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}


void Led::blink_slow_handler(void* parameter) 
{
  Led* led = (Led*) parameter;
  while (true) {
    // gpio_set_level(led->_pin, 1);
    ESP_LOGI("TAG", "blink_slow_handler 1");
    vTaskDelay(pdMS_TO_TICKS(500));
    // gpio_set_level(led->_pin, 0);
    ESP_LOGI("TAG", "blink_slow_handler 1");
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

Led::Led(gpio_num_t pin) 
{
  this->_pin = pin;
  this->_task_handle = NULL;
  gpio_set_direction(this->_pin, GPIO_MODE_OUTPUT);
  this->off();
}

void Led::clear_task_handle() 
{
  if (this->_task_handle != NULL) 
  {
    ESP_LOGI("LED", "handle is NOT null");
    vTaskDelete(this->_task_handle);
    this->_task_handle = NULL;
  }
  else 
  {
    ESP_LOGI("LED", "handle is null");
  }
}

void Led::on() 
{
  // Clear the previous task, if any
  this->clear_task_handle();
  // Turn on the LED
  gpio_set_level(this->_pin, 1);
}

void Led::off() 
{
  // Clear the previous task, if any
  this->clear_task_handle();
  // Turn off the LED
  gpio_set_level(this->_pin, 0);
}

void Led::blink_fast() 
{
  // Clear the previous task, if any
  this->clear_task_handle();
  // Create a task with IDLE_PRIORITY
  xTaskCreate(
    Led::blink_fast_handler, // the task function (need to be static)
    "LED", // the name 
    5000,
    this, // the argument that we are expecting in the task function
    tskIDLE_PRIORITY,
    &(this->_task_handle) // the handle to store the task information (WARNING: we nee the reference with the &)
  );
}


void Led::blink_slow() 
{
  // Clear the previous task, if any
  this->clear_task_handle();
  xTaskCreate(
    Led::blink_slow_handler, // the task function (need to be static)
    "LED", // the name 
    5000,
    this, // the argument that we are expecting in the task function
    tskIDLE_PRIORITY,
    &(this->_task_handle) // the handle to store the task information (WARNING: we nee the reference with the &)
  );
}