#include "msp430.h"
#include "stdio.h"
#include "Junior_Design.h"

char Data[] = "Junior Design TI";
char Data2[32] = "";
static unsigned int ADC_Result;
static int d_1;
static int d_10;

void main(void){
    Init_HW();

    //MOSFETLED config and ADC

    P2DIR |= (BIT5 | BIT2);
    P2OUT |= (BIT5);

    //LCD config
    LCD_I2C_Init();
    LCD_Initialize();
    LCD_CLRscreen();
    LCD_String(Data);


    while(1){
        P2OUT ^= BIT5;

        Ultrasonic_Trigger();
        Delay_Timer(DELAYT_100ms);
        unsigned long d1 = Ultrasonic_Echo_Read();

        int mm = (int)((d1 * 34)/ 20);

        d_1 = (int)(d1 * 0.066929);
        d_10 = (int)(d1 * 0.66929) - (d_1 * 10);


        ADC_Result = ADC_Read();
        Duty = (int)((float)ADC_Result/(float)10.23);

        LCD_Cursor_Postion(0x40);
        LCD_Cursor_On_No_Blink();
        sprintf(Data2, "%dmm %d.%din %d%%" , mm , d_1, d_10, (int)Duty);
        LCD_String(Data2);
        Delay_Timer(DELAYT_500ms);
    }
}

