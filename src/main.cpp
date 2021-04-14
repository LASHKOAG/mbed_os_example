/*
 * Copyright (c) 2017 - 2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */
/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

//SPI slave-master
/*
connect GND(slave) <-> GND(master)
*/

/*code for slave*/

#include "mbed.h"
#include "platform/mbed_thread.h"
#include <rtos.h>
//        thread_sleep_for(BLINKING_RATE_MS);

//for F411
//SPISlave device(PA_7, PA_6, PA_5, PA_15);
//DigitalOut drdyOut(PA_10);

//for L476
SPISlave device(PA_7, PA_6, PA_5, PA_4);

// SPI_MOSI    = PA_7,
// SPI_MISO    = PA_6,
// SPI_SCK     = PA_5,
// SPI_CS      = PB_6,

DigitalOut drdyOut(PC_7);
DigitalOut nss(PA_4);

int main()
{
    printf("\n======================================================\r\n");

    device.format(8, 3); // Setup:  bit data, high steady state clock, 2nd edge capture
    // device.frequency(1000000); // 1MHz

    uint8_t *BufferMsv = new uint8_t[3];

    BufferMsv[0] = 0x6F; //111
    BufferMsv[1] = 0x64; //100
    BufferMsv[2] = 0x32; //50

    int v;

    while (1)
    {
        drdyOut = 1;
        wait_us(1);
        if (device.receive())
        {
            wait_us(1);
            v = device.read(); // Read byte from master
                printf("v register = 0x%X\n\r", v);
            nss = 0;
            device.reply(BufferMsv[0]); // 0x6F 111
            device.reply(BufferMsv[1]); //0x64 100
            device.reply(BufferMsv[2]); //0x32 50

            nss = 1;
        }
        drdyOut = 0;
    }

    if (BufferMsv != NULL)
    {
        delete[] BufferMsv;
    }
}

/*code for master*/
//H743ZI
SPI spi(PD_7, PA_6, PA_5, PA_4); // mosi, miso, sclk, ssel
DigitalOut chipSelect(PA_4);
InterruptIn drdyIN(PE_3);

chipSelect = 1;
spi.format(8, 3);
spi.frequency(1000000); //1MHz

while (1)
{
    chipSelect = 0;
    spi.write(txBufferMsv, 3, rxBufferMsv, 3);

    // Deselect the device
    chipSelect = 1;

        printf("===============================\n");
    for (uint8_t i = 0; i < 3; ++i)
    {
        printf("rxBufferMsv[%d] = %d \n", i, rxBufferMsv[i]);
    }
        printf("===============================\n");

    ThisThread::sleep_for(5000);
}