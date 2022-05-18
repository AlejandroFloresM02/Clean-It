
#include "MKL25Z4.h"
#include <cstdio>
#include <stdio.h>
#include "delayTPM0.h"
#include "lcd.h"
#include "keypad.h"
#include "math.h"

bool start = false;
// main() runs in its own thread in the OS
int main()
{
    char menu_str[] = "SELECT MODE\nA1 B2 P3 ";
    char alarm_str[] = "Select a valid option";
    char Auto_str[] = "Autonoumus Mode";
    char BlueCon_str[] = "BT Control Mode";
    char Pattern_str[] = "Pattern Mode";
       
    SIM->SCGC5 |= 0x400; /* enable clock to Port B */
    PORTB->PCR[8] = 0x100; /* make PTB8 pin as GPIO */
    PTB->PDDR |= 0x00100; /* make PTB8 as output pin */

    SIM->SCGC5 |= 0x200; /* enable clock to Port A */

    /* configure PTA16 for interrupt */
    PORTA->PCR[16] |= 0x00100; /* make it GPIO */
    PORTA->PCR[16] |= 0x00003; /* enable pull-up */
    PTA->PDDR &= ~0x10000; /* make pin input */
    PORTA->PCR[16] &= ~0xF0000; /* clear interrupt selection */

    /* configure PTA17 for interrupt*/
    PORTA->PCR[17] |= 0x00100; /* make it GPIO */
    PORTA->PCR[17] |= 0x00003; /* enable pull-up */
    PTA->PDDR &= ~0x20000; /* make pin input */
    PORTA->PCR[17] &= ~0xF0000; /* clear interrupt selection */
    LCD_init();
    keypad_init();
    NVIC->ISER[0] |= 0x40000000; /* enable INT30 (bit 30 of ISER[0]) */
    __enable_irq(); /* global enable IRQs */

    while(1){
        if(!start) {
            LCD_command(1);
            LCD_command(0x80);
            send_string(menu_str,21);
            tpm_delayMs(50);
        }
    }


}
