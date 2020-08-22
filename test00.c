#include <gb/gb.h>
#include <stdio.h>

void main()
{
    unsigned int i=62000;
    while(1)
    {
        unsigned char joypad_state = joypad();
        if(joypad_state)
        {
            printf("%u\n",i);
            i++;
        }
    }

}