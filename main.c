#include <gb/gb.h>
#include <stdio.h>
// #include "LITTLE.C"

#define EQUAL 0
#define NOT_EQUAL -1
#define NOT_FOUND -1
#define TRUE 1
#define FALSE 0
#define NULL 0

unsigned char c_strcmp(char *s1, char *s2)
{
    unsigned char equality = FALSE;
    for(int i=0;i<10;i++)
    {
        if(s1[i]==NULL || s2[i]==NULL) break;
    }

    return equality;
}


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

char notes_universe[12][3]={"C","C#","D","D#","E","F","F#","G","G#","A","A#","B"};

int note_num(char *note_name)
{
   for(int i=0;i<12;i++)
   {
      int result=strcmp(notes_universe[i],note_name);
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
	{16,33,65,131,262,523,1047,2093,4186,8372,16744},
	{17,35,69,139,277,554,1109,2217,4435,8867,17740},
	{18,37,73,147,294,587,1175,2349,4699,9397,18795},
	{19,39,78,156,311,622,1245,2489,4978,9956,19912},
	{21,41,82,165,330,659,1319,2637,5274,10548,0},
	{22,44,87,175,349,698,1397,2794,5588,11175,0},
	{23,46,93,185,370,740,1480,2960,5920,11840,0},
	{25,49,98,196,392,784,1568,3136,6272,12544,0},
	{26,52,104,208,415,831,1661,3322,6645,13290,0},
	{28,55,110,220,440,880,1760,3520,7040,14080,0},
	{29,58,117,233,466,932,1865,3729,7459,14917,0},
	{31,62,123,247,494,988,1976,3951,7902,15804,0}
			};

	return freq[note_num][note_oct];
}

void main()
{                  
    FMSoundInit();  
    while(1)
    {
        unsigned char joypad_state = joypad();
        if(joypad_state)
        {
            printf("%d",c_strcmp("AA","BA"));
            delay(500);     
            FMSound_off();      
        }
    }
}