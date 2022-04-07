#ifndef LED_H
#define LED_H

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

class Led 
{
  private:
    gpio_num_t _pin;
    xTaskHandle _task_handle;

    static void blink_fast_handler(void* parameter);
    static void blink_slow_handler(void* parameter);

    void clear_task_handle();
  public:
    Led(gpio_num_t pin);

    void on();
    void off();
    void blink_fast();
    void blink_slow();
};

#endif // LED_H