/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */
//включаем/выключаем процесс мигания светодиодом по прерыванию кнопки
#include "mbed.h"
#include "platform/mbed_thread.h"

#include "mbed_events.h"
#include <stdio.h>

DigitalOut led(PB_0);

// creates a queue with the default size
EventQueue queue;
    
void led_inverse()
{
    led = !led;
}


int main() {
  //every 50 ms led will be inversed
  queue.call_every(50, led_inverse);

  queue.dispatch();

    while(1){

    }
}


