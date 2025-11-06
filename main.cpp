/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);

DigitalOut* leds[3] = {&led1, &led2, &led3};

InterruptIn button(USER_BUTTON);

Timeout button_debounce_timeout;
float debounce_time_interval = 0.3;

const int max_presses = 6;
int press_count = 0;
int active_led = 0;
int led_cycle[max_presses];

void onButtonStopDebouncing(void);

void onButtonPress(void) {
    if (press_count < max_presses) {
        *leds[0] = 1; *leds[1] = 1; *leds[2] = 1;
        led_cycle[press_count] = active_led;
        press_count++;
    } else {
        *leds[0] = 0; *leds[1] = 0; *leds[2] = 0;
    }
    button.rise(NULL);
    button_debounce_timeout.attach(onButtonStopDebouncing, debounce_time_interval);
}

void onButtonStopDebouncing(void) {
    button.rise(onButtonPress);
}

int main() {
    button.rise(onButtonPress);
    
    while (press_count < max_presses) {
        *leds[active_led] = 1;
        wait(1.0);
        active_led = (active_led + 1) % 3;
        *leds[0] = 0; *leds[1] = 0; *leds[2] = 0;
    }

    for (int j = 0; j < max_presses; j++) {
        *leds[led_cycle[j]] = 1;
        wait(1.0);
        *leds[0] = 0; *leds[1] = 0; *leds[2] = 0;
    }
}