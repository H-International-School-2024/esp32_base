#ifndef LED_H
#define LED_H

#include "driver/gpio.h"

class Led 
{
  private:
    gpio_num_t _pin;
  public:
    Led(gpio_num_t pin);

    void on();
    void off();
    void blink_fast();
};

#endif // LED_H