/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */
//включаем/выключаем процесс мигания светодиодом по прерыванию кнопки
#include "mbed.h"
#include "platform/mbed_thread.h"

#include "mbed_events.h"
#include <stdio.h>

// Blinking rate in milliseconds
#define BLINKING_RATE_MS                                                    1000

// Initialise the digital pin LED1 as an output
DigitalOut led(LED1);
// DigitalOut led(PB_0);


int main()
{
   while (true) {
       led = !led;
       thread_sleep_for(BLINKING_RATE_MS);
   }
}



