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

EventQueue queue2;

Thread thread;
Thread thread2;  

void led_inverse()
{
    led = !led;
}

void counting(){
  printf("---------------  counting()  ----------------------\n");
  for(uint32_t i = 0; i<=4000000000; ++i){
    if(i== 10){
      printf("10\n");
    }
    if(i== 1000){
      printf("1000\n");
    }
    if(i== 10000){
      printf("10000\n");
    }
    if(i== 4000000000){
      printf("4000000000\n");
    }
  }
}


void for_th(){
  queue.call(counting);
  queue.dispatch();
}

void for_th2(){
  queue2.call_every(50, led_inverse);
  queue2.dispatch();
}


int main() {

  printf("====================================\n");

  thread.start(for_th);

  thread2.start(for_th2);

  printf("===vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv====\n");

    while(1){

    }
}