/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */
//включаем/выключаем процесс мигания светодиодом по прерыванию кнопки
#include "mbed.h"
#include "platform/mbed_thread.h"

#include "mbed_events.h"
#include <stdio.h>

// #define FLAG_CANCEL_TIMESIGNAL (1U << 0)
// EventFlags eventFlags;

DigitalOut led(PB_0);

// creates a queue with the default size
EventQueue queue;

EventQueue queue2;
EventQueue queue3;
EventQueue queue4;
Thread thread;
Thread thread2;  
Thread thread3; 

int32_t uniqueID = 0;
bool flag_cancel_timeSignal = 0;
bool flag_turnOFF_led = 0;

void led_inverse()
{
  // printf("========== led_inverse() ==========================\n");
    led = !led;
}

void counting(){
  if(flag_cancel_timeSignal){return;}
  printf("---------------  counting()  ----------------------\n");
  for(uint32_t i = 0; i<=4000000000; ++i){
    if(flag_cancel_timeSignal){
      break;
    }
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
  flag_cancel_timeSignal=0;
  // while(1){
    
    // ThisThread::get_id();
    // queue.call(printf, "thread counting ThisThread::get_id() = %p\n", ThisThread::get_id());
    uniqueID = queue.call(counting);
    // queue.call(printf, "uniqueID = queue.call(counting); = %d\n", uniqueID);
  // }

}
// void for_blink(){
//   led=1;
  // printf("========== for_blink() ==========================\n");
  // queue3.call_every(50, led_inverse);
  // if(flag_turnOFF_led){
  //   queue3.break_dispatch();
  // }
  // queue3.dispatch();
// }

void for_th2(){
  int32_t count=0;
  while(1){
    count++;
    ThisThread::sleep_for(2000);
    flag_cancel_timeSignal = true;
    queue.call(printf, "count = %d\n", count+=10);
    queue.call_every(50, led_inverse);
    
    // bool result_cancel = queue.cancel(uniqueID);
    // queue.call(printf, "result_cancel = %d\n", result_cancel);

    queue.call(printf, "thread led_inverse ThisThread::get_id() = %p\n", ThisThread::get_id());
  
    // queue.call(printf, "try cancel = %d\n", uniqueID);
  }

  // queue.call_every(50, led_inverse);
}

void swit(){
  
  int value = 0;

  value = 100;
    while(1){
      switch (value)
      {
      case 100:
        uniqueID = queue4.call(counting);
        break;

      case 200:
        flag_cancel_timeSignal = true;
        int countt = 0;
        queue4.call(printf, "countt = %d\n", countt+=10);
        break;

      // case 300:
      //   int counttt = 0;
      //   queue4.call(printf, "counttt = %d\n", counttt+=1000);
      //   break;

      // default:
      //   break;
      }
      ThisThread::sleep_for(5000);
      printf( "hello arm\n");

      value =200;
  }
}

int main() {

  printf("====================================\n");
  #ifdef MBED_MAJOR_VERSION
        printf("Mbed OS version: %d.%d.%d\n\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
  #endif

  // thread.start(for_th);

  // thread2.start(for_th2);
  // thread3.start(for_blink);

  thread3.start(swit);

  // queue.dispatch();
  queue4.dispatch();
  printf("===vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv====\n");

    while(1){ 

    }
}