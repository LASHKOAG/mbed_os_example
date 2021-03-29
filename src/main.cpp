/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */
//включаем/выключаем процесс мигания светодиодом по прерыванию кнопки
#include "mbed.h"
#include "platform/mbed_thread.h"

#include "mbed_events.h"
#include <stdio.h>

//create interruptin object for the button
InterruptIn BUTTON (USER_BUTTON);
// InterruptIn BUTTON (PC_13);
bool active = false;

// creates a queue with the default size
EventQueue queue;
    
//Button handler
void BUTTON_ISR(){
    active = !active;
}

void BUTTON_EVENT(){
  queue.call(printf, "active: %d\n", active);
}


int main() {
  //when interrupt USER_BUTTON will be occur
  BUTTON.rise(&BUTTON_EVENT);
  queue.dispatch();
  //код после  dispatch(); исполняться не будет (внутри dispatch() цикл while(1))
  //code after dispatch(); will not be executed (because inside dispatch () while (1) loop))
  printf("this code will not be executed\n");

    while(1){

    }
}


