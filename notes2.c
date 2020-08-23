#include <gb/gb.h>
#include <stdio.h>
#include "LITTLE.C"

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
{
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

unsigned int note_freq(int note_num, int note_oct)
{
	unsigned int freq[][11] = {
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

struct full_note_des {
   char *name;
   int oct;
};

full_note_des midi_note(int midi_note_num)
{
   full_note_des note;

   int note_oct = midi_note_num / 12;
   int note_num = midi_note_num - note_oct * 12;

   note.name = note_name(note_num);
   note.oct = note_oct;

   return note;
}

void midi_note_on(int midi_note_num)
{
    full_note_des note=midi_note(midi_note_num);
    FMSound_on(note.name,note.oct);
}

struct midi_header_chunk{
   char name[4];
   unsigned char length[4]; //Little endian by default
   unsigned char format[2]; //Little endian by default
   unsigned char tracks[2]; //Little endian by default
   unsigned char ticks[2];  //Little endian by default
};

void little_endian_to_big_endian(unsigned char *p, int length)
{
   int last_byte=length-1;
   for(int i=0;i<length/2;i++)
   {
      unsigned char tmp;
      tmp=p[i];
      p[i]=p[last_byte-i];
      p[last_byte-i]=tmp;
   }
}

struct midi_track_header_chunk {
   char name[4];
   unsigned char length[4];  //Little endian by default
};

void c_memcpy(unsigned char *destiny, unsigned char *origin, unsigned int size)
{
    for(int i=0;i<size;i++)
    {
        destiny[i]=origin[i];
    }
}

void main()
{                  
    FMSoundInit();

    //midi_header_chunk header;

    //c_memcpy(&header,raw_midi,sizeof(midi_header_chunk));

    printf("%s", header.name);


    FMSound_on(note_freq(note_num("C"),4));
    delay(500);     
    FMSound_off(); 

}