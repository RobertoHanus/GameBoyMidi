#include <gb/gb.h>
#include <stdio.h>
// #include "LITTLE.C"

void FMSoundInit()
{
    NR52_REG = 0x80;
    NR51_REG = 0x11;
    NR50_REG = 0x77;
    NR10_REG = 0x00;
}

void FMSound_on(int freq)
{
    NR11_REG = 0x10;
    NR12_REG = 0xF0;
    NR13_REG = freq & 0xFF;
    NR14_REG = ((freq >> 8) & 0x07) | 0x80;
}

void FMSound_off()
{
    NR12_REG = 0x00;
}

void main()
{                  
    FMSoundInit();  
    while(1)
    {
        unsigned char joypad_state = joypad();
        if(joypad_state)
        {
            FMSound_on(523);
            delay(500);     
            FMSound_off();      
        }
    }

}