/*
 * File:   ecu1_sensor.c
 * Author: moham
 *
 * Created on 10 June, 2026, 8:00 AM
 */


#include "ecu1_sensor.h"
#include "adc.h"
#include "can.h"
#include "msg_id.h"
#include "uart.h"

uint16_t get_speed()
{
    // Implement the speed function
    int value=read_adc(CHANNEL4);//0to5v will be converted into 0 to 1023 here
    //int speed=value/5.12;//to convert the speed ranging from 0 to 200
    unsigned long int speed=(value*200)/1023;
    if(speed<0)
        speed=0;
    if(speed>200)
        speed=200;
    return speed;
}

unsigned char get_gear_pos()
{
    // Implement the gear function
    char key=read_digital_keypad(STATE_CHANGE);
    static unsigned char gear='N';
    if(key==SWITCH1)
    {
        if(gear=='N')
        {
            gear='1';
        }
        
        else if(gear>='1' && gear<'6')
        {
            gear++;
        }
        else
        {
            gear='R';
        }
        return gear;
    }
    else if(key==SWITCH2)
    {
        if(gear=='1')
        {
            gear='N';
        }
        else if(gear=='R')
        {
            gear='6';
        }
        else if(gear>'1')
        {
            gear--;
        }
        else
        {
            gear='N';
        }
        return gear;
    }
    else if(key==SWITCH3)
    {
        gear='N';
        return gear;
    }
    else if(key==SWITCH4)
    {
        gear='R';
        return gear;
    }
    return gear;
}