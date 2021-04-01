#include "mbed.h"
#include "rtos.h"
#include <stdio.h>
 
DigitalOut led1(LED1);
DigitalOut led2(LED2);
Serial pc(USBTX, USBRX); // tx, rx


Thread thread; 
Thread *(test);
 
void led2_thread(void const *args) {
    pc.printf("%s\r\n", (char*)args);
//void led2_thread() {
    while (true) {
        led2 = !led2;        
        ThisThread::sleep_for(1000);       
    }
}
 
int main() {
    char message[] = "hello ARM";
    thread.start(callback(led2_thread, message));
//    thread.start(callback(led2_thread));
    test = &thread;
    test->set_priority(osPriorityHigh);
    pc.printf("%i\n\r",test->get_priority());
        
    while (true) {
        led1 = !led1;
        ThisThread::sleep_for(500);         
    }
}