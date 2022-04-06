#include "driver/gpio.h"
#include "./leds/led.hpp"

extern "C" void app_main(void)
{
  Led* led = new Led(GPIO_NUM_23);
  led->blink_fast();
}