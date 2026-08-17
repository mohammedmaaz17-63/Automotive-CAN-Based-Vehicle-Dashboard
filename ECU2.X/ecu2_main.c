/*
 * File:   main.c
 * Author: moham
 *
 * Created on 9 June, 2026, 10:20 PM
 */


#include "ecu2_sensor.h"
#include "adc.h"
#include "can.h"
#include "msg_id.h"
#include "uart.h"

void my_itoa(unsigned int rpm,char str_rpm[])
{
    str_rpm[0]=(rpm/1000)+'0';
    str_rpm[1]=((rpm/100)%10)+'0';
    str_rpm[2]=((rpm/10)%10)+'0';
    str_rpm[3]=(rpm%10)+'0';
    str_rpm[4]='\0';
}
//void my_itoa_temp(unsigned int temp,char str_temp[])//for engine temperature
//{
//    str_temp[0]=(temp/100)+'0';
//    str_temp[1]=((temp/10)%10)+'0';
//    str_temp[2]=(temp%10)+'0';
//    str_temp[3]='c';
//    str_temp[4]='\0';
//}
void init_led()
{
    TRISB0=0;
    TRISB1=0;
    TRISB6=0;
    TRISB7=0;
    PORTB=0;
}
void init_config()
{
    init_adc();
    init_digital_keypad();
    init_uart();
    init_led();
    init_can();
}

void my_strcpy(char indicator[],char status[])
{
    int i=0;
    while(status[i]!='\0')
    {
        indicator[i]=status[i];
        i++;
    }
    indicator[i]='\0';
}

int main()
{
    //call the functions
    init_config();
    uint16_t rpm=0;
    uint16_t indicator_status=0;
    while(1)
    {
        rpm=get_rpm();
        indicator_status=process_indicator();
        //print it using uart
        char str_rpm[5];
        my_itoa(rpm,str_rpm);
        //transmitting the rpm
        can_transmit(RPM_MSG_ID,str_rpm,5);
        for(int i=0;i<1000;i++);
        //puts("RPM : ");
        //puts(str_rpm);
        //puts("   Indicator : ");
        //transmitting the indicator status
        char indicator[4];
        if(indicator_status==0)
        {
           // puts("OFF");
            my_strcpy(indicator,"OFF");
        }
        else if(indicator_status==1)
        {
            //puts("<--");
            my_strcpy(indicator,"<--");
        }
        else if(indicator_status==2)
        {
            //puts("-->");
            my_strcpy(indicator,"-->");
        }
        can_transmit(INDICATOR_MSG_ID,indicator,4);
        for(int i=0;i<1000;i++);
        //For engine temperature
//        uint16_t temp=get_engine_temp();
//        char str_temp[5];
//        my_itoa_temp(temp,str_temp);
//        can_transmit(ENG_TEMP_MSG_ID,temp,5)
                
                
        //puts("\n\r");
    }
}
