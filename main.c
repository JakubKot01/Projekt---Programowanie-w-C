#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>

#include "frequencies.h"
#include "wavfile.h"

const int NUM_OF_SAMPLES = (WAVFILE_SAMPLES_PER_SECOND*2);

int main()
{
    short waveform[NUM_OF_SAMPLES];
    printf("[1]Wprowadzanie ręczne\n[2]schodki\t(TODO)\n[3]wyjdź");
    int c, length, volume;
    double frequency;
    scanf("%d", &c);
    if(c==1)
    {
        printf("częstotliwość: ");
        scanf("%lf", &frequency);
        printf("głośność: ");
        scanf("%d", &volume);
        int l = NUM_OF_SAMPLES;
        for(int i=0;i<l;i++)
        {
            double t = (double) i / WAVFILE_SAMPLES_PER_SECOND;
            waveform[i] = volume*sin(frequency*t*2*M_PI);
        }
        length=l;
	}
	if(c==2)
    {
        int volume = 32000;
        double f[8]={261.9, 293.7, 329.6, 349.2, 392.0, 440.0, 493.9, 523.3};
        int l = NUM_OF_SAMPLES*8;
        for(int i=0;i<l;i++)
        {
            double t = (double) i / WAVFILE_SAMPLES_PER_SECOND;
            waveform[i] = volume*sin(f[i]*t*2*M_PI);
        }
    length=l;
    }
    if(c==3) return 0;
    FILE * f = wavfile_open("fst.wav");
	if(!f)
	{
		printf("error: %s",strerror(errno));
		return 1;
	}
	wavfile_write(f,waveform,length);
	wavfile_close(f);
	wavfile_add(waveform, f, length, volume, frequency);
	return 0;
}
