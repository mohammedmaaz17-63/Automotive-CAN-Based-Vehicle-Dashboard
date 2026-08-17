/*
 * File:   message_handler.c
 * Author: moham
 *
 * Created on 12 June, 2026, 8:17 AM
 */


#include <xc.h>
#include <string.h>
#include "message_handler.h"
#include "msg_id.h"
#include "can.h"
#include "clcd.h"


//volatile unsigned char led_state = LED_OFF, status = e_ind_off;


void handle_speed_data(uint8_t *data, uint8_t len)
{
    //Implement the speed function
    clcd_print(data,LINE2(0));
    clcd_print(" ",LINE2(3));
    //For temp
    //clcd_print(data,LINE2(0));
}

void handle_gear_data(uint8_t *data, uint8_t len) 
{
    //Implement the gear function
    clcd_print(data,LINE2(4));
    clcd_print("  ",LINE2(6));
    //FOR TEMP
    //clcd_print(data,LINE2(3));
}

void handle_rpm_data(uint8_t *data, uint8_t len) 
{
    //Implement the rpm function
    clcd_print(data,LINE2(8));
    clcd_print(" ",LINE2(12));
    //FOR TEMP
    //clcd_print(data,LINE2(5));
}

static int sec=0;
void handle_indicator_data(uint8_t *data, uint8_t len) 
{
    //Implement the indicator function
    clcd_print(data,LINE2(13));
    if(data[0]=='<')//LEFT INDICATOR
    {
        RB6=0;
        RB7=0;
        if(sec>=2)
        {
            sec=0;
            RB0=!RB0;
            RB1=!RB1;
        }
    }
    if(data[0]=='-')//RIGHT INDICATOR
    {
        RB0=0;
        RB1=0;
        if(sec>=2)
        {
            sec=0;
            RB6=!RB6;
            RB7=!RB7;
        }
    }
    if(data[0]=='O')//INDICATOR IS OFF
    {
        RB0=0;
        RB1=0;
        RB6=0;
        RB7=0;
    }
    //FOR TEMP
    //clcd_print(data,LINE2(9));
}

void handle_engine_temp_data(uint8_t *data, uint8_t len) 
{
    //Implement the temperature function
    //FOR TEMP
//    clcd_print(data,LINE2(12));
}

void process_canbus_data() 
{   
    //process the CAN bus data
    int msg_id=0;
    int len=0;
    char str[8];
    can_receive(&msg_id,str,&len);
    
    for(int i=0;i<5000;i++);
    if(len==0)
    {
        return;
    }
    if(len >= sizeof(str))
    {
        len = sizeof(str) - 1;
    }
    //str[len]='\0';
    
    //To print the titles in the first line of clcd
    clcd_print("SPD GR  RPM  IND",LINE1(0));
    //FOR TEMPERATURE
    //clcd_print("SPDGRRPM INDTEMP",LINE1(0));//FOR engine temperature
    switch(msg_id)
    {
        case SPEED_MSG_ID:
        {
            handle_speed_data(str,len);
            break;
        }
        case GEAR_MSG_ID:
        {
            handle_gear_data(str,len);
            break;
        }
        case RPM_MSG_ID:
        {
            handle_rpm_data(str,len);
            break;
        }
        case INDICATOR_MSG_ID:
        {
            handle_indicator_data(str,len);
            break;
        }
        case ENG_TEMP_MSG_ID:
        {
            handle_engine_temp_data(str,len);
            break;
        }
    }
    
}

void __interrupt()isr(void)
{
    static int count=0;
    if(TMR0IF==1)
    {
        TMR0=TMR0+8;
        TMR0IF=0;
        if(count++==20000)
        {
            sec++;
            count=0;
        }
    }
}
