/*
 * File:   ecu1_main.c
 * Author: moham
 *
 * Created on 10 June, 2026, 8:00 AM
 */


#include "adc.h"
#include "can.h"
#include "ecu1_sensor.h"
#include "msg_id.h"
#include "uart.h"
void my_itoa(unsigned int speed,char str_speed[])
{
    str_speed[0]=(speed/100)+'0';
    str_speed[1]=((speed/10)%10)+'0';
    str_speed[2]=(speed%10)+'0';
    str_speed[3]='\0';
}
void init_config()
{
    init_adc();
    init_digital_keypad();
    //init_uart();
    init_can();
}
int main()
{
    //Call the functions
    
    init_config();
    uint16_t speed=0;
    unsigned char gear='N';
    while(1)
    {
        speed=get_speed();
        gear=get_gear_pos();
        //print it using uart
        char str_speed[4];
        my_itoa(speed,str_speed);
//        puts("speed : ");
//        puts(str_speed);
//        puts("   Gear : ");
//        putch(gear);
//        puts("\n\r");
        //Transmit the speed
        can_transmit(SPEED_MSG_ID,str_speed,4);
        for(int i=0;i<1000;i++);
        //Transmit the gear
        char Gear[4];
        Gear[0]='G';
        Gear[1]=gear;
        Gear[2]='\0';
       
        can_transmit(GEAR_MSG_ID,Gear,3);
        for(int i=0;i<1000;i++);
    }
    
}