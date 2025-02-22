#include "uop_msb.h"

// LED Bar Display
BusOut dataBits(LED_D0_PIN, LED_D1_PIN, LED_D2_PIN, LED_D3_PIN, LED_D4_PIN, LED_D5_PIN, LED_D6_PIN, LED_D7_PIN);
DigitalOut LED_BAR_OE(LED_BAR_OE_PIN,1);
DigitalOut LED_RED_LE(LED_RED_LE_PIN);
DigitalOut LED_GRN_LE(LED_GRN_LE_PIN);
DigitalOut LED_BLUE_LE(LED_BLUE_LE_PIN);

void led_init(unsigned int dat, char g)
{
    //Disable the LED outputs
    LED_BAR_OE = 1;

    //Set data to 0
    dataBits = dat;

    //Give a little time
    wait_us(1);

    //Enable all latches
    LED_RED_LE  = 1;
    LED_GRN_LE  = 1;
    LED_BLUE_LE  = 1;

    //Give a little time
    wait_us(1);

    //Enable all latches
    LED_RED_LE  = 0;
    LED_GRN_LE  = 0;
    LED_BLUE_LE  = 0;

    
}

int main()
{
    printf("Functions demo\n");

    led_init(0b10101010, true);

    while (true) {

        //Update the red
        wait_us(1);
        dataBits = 0xFF;    //Set the 8-bit data pattern
        wait_us(1);
        LED_RED_LE  = 1;    //Copy dataBits to red latch outputs
        wait_us(1);         
        LED_RED_LE  = 0;    //Ignore inputs (dataBits)
        wait_us(1);

        //Update the green
        wait_us(1);
        dataBits = 0b10101010;
        wait_us(1);
        LED_GRN_LE  = 1;
        wait_us(1);
        LED_GRN_LE  = 0;
        wait_us(1);

        //Update the blue
        wait_us(1);
        dataBits = 0b11001100;
        wait_us(1);
        LED_BLUE_LE = 1;
        wait_us(1);
        LED_BLUE_LE = 0;
        wait_us(1);


        for (unsigned int n=0; n<10; n++) {
            //Enable all the LED BAR Latch Outputs
            LED_BAR_OE = 0;

            //Wait
            wait_us(500000);

            //Disable the latch outputs
            LED_BAR_OE = 1;

            //Wait
            wait_us(500000);            
        }


        //Spin forever
        while(true);

    }

}

