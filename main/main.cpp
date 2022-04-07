#include "driver/gpio.h"
#include "./leds/led.hpp"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

extern "C" void app_main(void)
{
  Led* led = new Led(GPIO_NUM_23);
  led->on();
  vTaskDelay(pdMS_TO_TICKS(2500));
  led->blink_fast();
  vTaskDelay(pdMS_TO_TICKS(2500));
  led->blink_slow();
}