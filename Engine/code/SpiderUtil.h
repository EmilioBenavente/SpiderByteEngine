#ifndef SPIDER_UTIL_H
#define SPIDER_UTIL_H

#include <stdint.h>
#include <stdio.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef float r32;
typedef double r64;

typedef char c8;

typedef struct Window Window;
struct Window
{
	u32 Width;
	u32 Height;
	u8* WindowName;
};


void
ReadEntireFile(u8* Buffer, u32* Index, const char* FileName)
{
	FILE* File = fopen(FileName, "r");
	if(File)
	{
		c8 ch = fgetc(File);
		while(ch != EOF)
		{
			Buffer[(*Index)++] = ch;
			ch = fgetc(File);

			if(ch == EOF)
			{
				c8 Tmp = ch;
				ch = fgetc(File);
				if(ch != EOF)
				{
					Buffer[(*Index)++] = Tmp;
				}
			}
		}
		fclose(File);
	}
	else
	{
		printf("Could not read file -> %s\n", FileName);
	}
}



#endif
