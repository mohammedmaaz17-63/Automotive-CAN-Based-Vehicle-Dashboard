/*
 * File:   main.c
 * Author: moham
 *
 * Created on 9 June, 2026, 10:20 PM
 */


#include <xc.h>
#include <stdint.h>
#include "can.h"
#include "clcd.h"
#include "msg_id.h"
#include "message_handler.h"
//#include "isr.h"
#include "timer0.h"

static void init_leds() 
{
    TRISB = 0x08; // Set RB2 as output, RB3 as input, remaining as output
    PORTB = 0x00;
}

static void init_config(void) {
    // Initialize CLCD and CANBUS
    init_clcd();
    init_leds();
    init_can();

    // Enable Interrupts
    GIE = 1;
    PEIE = 1;
    init_timer0();
}

void main(void) {
    // Initialize peripherals
    init_config();

    /* ECU1 main loop */
    while (1) {
        // Read CAN Bus data and handle it
        process_canbus_data();
    }

    return;
}
