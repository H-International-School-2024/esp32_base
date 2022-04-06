#include "led.hpp"
#include "esp_log.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

Led::Led(gpio_num_t pin) 
{
  this->_pin = pin;
  gpio_set_direction(this->_pin, GPIO_MODE_OUTPUT);
  this->off();
}

void Led::on() 
{
  gpio_set_level(this->_pin, 1);
}

void Led::off() 
{
  gpio_set_level(this->_pin, 0);
}

void Led::blink_fast() 
{
  while(true) 
  {
    this->on();
    vTaskDelay(1000);
    this->off();
    vTaskDelay(1000);
  }
}