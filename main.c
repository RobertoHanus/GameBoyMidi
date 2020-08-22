#include <gb/gb.h>
#include <stdio.h>
// #include "LITTLE.C"

void main()
{
            int i=1;
            
            i=i<<4;

            printf("%x",i);

            NR52_REG = 0x80;
            NR51_REG = 0x11;
            NR50_REG = 0x77;
            NR10_REG = 0x00;
                    
    while(1)
    {
        unsigned char joypad_state = joypad();
        if(joypad_state)
        {
            NR11_REG = 0x10;
            NR12_REG = 0xF0;
            NR13_REG = 0x00;
            NR14_REG = 0x87;
            delay(500);
            NR12_REG = 0x00;
        }
    }

}