/*
 * File:   ecu2_sensor.c
 * Author: moham
 *
 * Created on 10 June, 2026, 8:10 AM
 */


#include "ecu2_sensor.h"
#include "adc.h"
#include "can.h"
#include "msg_id.h"
#include "uart.h"

uint16_t get_rpm()
{
    //Implement the rpm function
    int value=read_adc(CHANNEL4);//0to5v will be converted into 0 to 1023 here
    unsigned long int rpm=(value*6000)/1023;
    if(rpm<0)
        rpm=0;
    if(rpm>6000)
        rpm=6000;
    return rpm;
}

//uint16_t get_engine_temp()
//{
//    //Implement the engine temperature function
//    int value=read_adc(CHANNEL6);
//    int temp=(value*150)/1023;
//    return temp;
//}

IndicatorStatus process_indicator()
{
    //Implement the indicator function
    char key;
    static IndicatorStatus status = 0;
    static int left_ind_delay=0;
    static int right_ind_delay=0; 
    key=read_digital_keypad(STATE_CHANGE);
    if(key==SWITCH1)//LEFT INDICATOR
    {
        status = 1;
    }
    if(key==SWITCH2)//RIGHT INDICATOR
    {
        status = 2;
    }
    if(key==SWITCH3)//TURN OFF THE INDICATOR
    {
        status = 0;
    }
    if(status == 1)
    {
        RB6 = RB7 = 0;

        if(left_ind_delay++ >= 100)
        {
            left_ind_delay = 0;
            RB0 = !RB0;
            RB1 = !RB1;
        }
    }
    else if(status == 2)
    {
        RB0 = RB1 = 0;

        if(right_ind_delay++ >= 100)
        {
            right_ind_delay = 0;
            RB6 = !RB6;
            RB7 = !RB7;
        }
    }
    else
    {
        PORTB = 0;
    }
    return status;
}