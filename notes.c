#include <gb/gb.h>
#include <stdio.h>
// #include "LITTLE.C"

#define EQUAL 0
#define NOT_EQUAL -1
#define NOT_FOUND -1
#define TRUE 1
#define FALSE 0
#define NULL 0

unsigned char c_strlen(char *s)
{
    unsigned char i;
    for(i=0;i<100;i++)
    {
        if(s[i]==NULL) break;
    }
    return i;
}

char c_strcmp(char *s1, char *s2)
{
    char equality = EQUAL;
    for(int i=0;i<10;i++)
    {
        if(s1[i]==NULL || s2[i]==NULL) break;
        if(s1[i]!=s2[i])
        {
            equality = NOT_EQUAL;
            break;
        }
    }
    if(c_strlen(s1)!=c_strlen(s2)) equality=NOT_EQUAL;
    return equality;
}


void FMSoundInit()
{
    NR52_REG = 0x80;
    NR51_REG = 0x11;
    NR50_REG = 0x77;
    NR10_REG = 0x00;
}

void FMSound_on(unsigned int freq)
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

char notes_universe[12][3]={"C","C#","D","D#","E","F","F#","G","G#","A","A#","B"};

int note_num(char *note_name)
   for(int i=0;i<12;i++)
   {
      int result=c_strcmp(notes_universe[i],note_name);
      if(result==0) return i;
   }
   return NOT_FOUND;
}

char *note_name(int note_num)
{
   return notes_universe[note_num];
}

int note_freq(int note_num, int note_oct)
{
	int freq[][11] = {
	{0,88,1034,1541,1797,1923,1986,0,0,0,0},
	{0,165,1090,1571,1811,1929,1989,0,0,0,0},
	{0,263,1147,1598,1822,1936,1993,0,0,0,0},
	{0,360,1199,1619,1837,1943,1995,0,0,0,0},
	{0,456,1239,1645,1848,1950,1999,0,0,0,0},
	{0,541,1285,1667,1859,1953,2002,0,0,0,0},
	{0,630,1326,1687,1870,1959,2004,0,0,0,0},
	{0,708,1367,1712,1880,1966,2007,0,0,0,0},
	{0,776,1411,1729,1889,1969,2009,0,0,0,0},
	{0,847,1451,1746,1897,1973,2011,0,0,0,0},
	{0,903,1491,1762,1907,1978,2013,0,0,0,0},
	{0,970,1519,1779,1915,1983,2016,0,0,0,0}
			};
	return freq[note_num][note_oct];
}

void main()
{                  
    FMSoundInit();
    int i=500;  
    while(1)
    {
        switch(joypad())
        {
            case J_RIGHT:
                FMSound_on(i);
                delay(500);     
                FMSound_off(); 
                break;
            case J_UP:
                i++;
                printf("\n%d",i);
                break;
            case J_DOWN:
                i--;
                printf("\n%d",i);
                break;

        }
    }
}