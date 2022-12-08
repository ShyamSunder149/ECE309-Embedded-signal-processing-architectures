#include<stdio.h>
#define CHIP_6713
#include "dsk6713.h"
#include"dsk6713_led.h"
#include"dsk6713_dip.h"
#include"dsk6713_aic23.h"
Uint32 audio[24000000];
int i=0;
#pragma DATA_SECTION(audio,".EXT_RAM")
int main()
{
	DSK6713_init();
	DSK6713_LED_init();
	DSK6713_DIP_init();
	DSK673_AIC23_init();
	DSK6713_AIC23_config config
	{
		0x0017, // line in left
		0x0017, // line in right
		0x01f9, // left headphones
		0x01f9, // right headphones
		0x0011, // analog audio path
		0x0000,// digital audio path
		0x0000, // power down
		0x0043, // DSP interface
		0x0081, // sample rate
		0x0001, // Digital interface activation
	};
	int hCodec;
	hCodec = DSK6713_AIC23_openCodec(0,&config);
	DSK6713_AIC23_setFreq(hcodec,DSK6713_AIC23_FREQ_8KHZ);
	while(1)
	{
		if(DSK6713_DIP_get(0))
		{
			DSK6713_LED_ON(0);
			while(!DSK6713_AIC23_read(hcodec,&audio[i]));
			i++;
`			if (i>24000000)
			{
				i=0;
			}
		}
		if(DSK6713_DIP_get(1))
		{
			DSK6713_LED_ON(1);
			while(!DSK6713_AIC23_write(hcodec,audio[i]));
			i++;
`			if (i>24000000)
			{
				i=0;
			}
		}
	}
	return 0;
}
