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

DigitalOut led(PB_0);

//create interruptin object for the button
InterruptIn BUTTON (USER_BUTTON);
// InterruptIn BUTTON (PC_13);

bool active = false;

//create a ticker object for a recurring interruption
Ticker blink_ticker;

//Button handler
void BUTTON_ISR(){
    active = !active;
}
 
//Recurrent handler
void blink_ticker_function(){
    if(active) {
      led=!led;
    }else {
      led=0;
    }
}


int main() {
    //Set up
  // BUTTON.mode(PullUp);

    // attach the address of the flip function to the rising edge
  BUTTON.rise(&BUTTON_ISR);  
    // BUTTON.fall(&BUTTON_ISR);
  blink_ticker.attach(&blink_ticker_function, 0.5);

  while(1){

  }
}

