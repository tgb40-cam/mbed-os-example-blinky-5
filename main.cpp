/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

DigitalOut myled(LED1);

int main() {
        while(true) {
                myled = 1; // LED is ON
                wait(0.2); // 200 ms
                myled = 0; // LED is OFF
                wait(1.0); // 1 sec
        }
}