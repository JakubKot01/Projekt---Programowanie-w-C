#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include <time.h>

#include "wavfile.h"
#include "frequencies.h"
#include "functions.h"

int arytm(int range, short waveform[], int i, int length)
{
    int s=0,p;
    for(int n=(i-range);n<(i+range);n++)
    {
        s=s+waveform[(n<0)? (length+n) : (n%length)];
    }
    s=s/(1+(2*range));
    return s;
}
int waveform_create(const char *filename, int vol, double freq, int length)
{
    short waveform[NUMBER_OF_SAMPLES];
    for(int i=0;i<length;i++)
    {
        double t = (double) i / WAVFILE_SAMPLES_PER_SECOND;
        waveform[i] = vol*sin(freq*t*2*M_PI);
    }
    FILE * f = wavfile_open(filename);
	if(!f)
	{
		printf("error: %s",strerror(errno));
		return 1;
	}
	wavfile_write(f,waveform,length);
	wavfile_close(f);
	return 0;
}
int wavfile_add(short new_waveform[], const char *filename,int length, int vol1, int vol2, int freq1, int freq2)
{
    int norm = (vol1 + vol2)/vol1;
    short newdata[length];
    for(int i=0;i<length;i++)
    {
        double t = (double) i / WAVFILE_SAMPLES_PER_SECOND;
        newdata[i] = vol2*sin(freq2*t*2*M_PI);
    }
    FILE * g = wavfile_open("dodany.wav");
	if(!g)
	{
		printf("error: %s",strerror(errno));
		return 1;
	}
	wavfile_write(g,newdata,length);
	wavfile_close(g);
    for(int i=0;i<length;i++)
    {
        double t = (double) i / WAVFILE_SAMPLES_PER_SECOND;
        new_waveform[i] = (vol1*sin(freq1*t*2*M_PI) + vol2*sin(freq2*t*2*M_PI))/norm;
    }
    FILE * f = wavfile_open(filename);
	if(!f)
	{
		printf("error: %s",strerror(errno));
		return 1;
	}
	wavfile_write(f,new_waveform,length);
	wavfile_close(f);
}
int noise(short noise[], short waveform[], int length)
{
    for(int i=0;i<length;i++)
    {
        noise[i] = waveform[i]+(2002 - rand() % 4004);
    }
    FILE * f = wavfile_open("noise.wav");
	if(!f)
	{
		printf("error: %s",strerror(errno));
		return 1;
	}
	wavfile_write(f,noise,length);
	wavfile_close(f);
	return 0;
}
int blur(const char *filename, short waveform[], int range, int length)
{
    short blur[length], copy[length];
    for(int i=0;i<length;i++)
    {
        copy[i] = waveform[i];
    }
    for(int i=0;i<length;i++)
    {
        blur[i] = arytm(range, copy, i, length);
    }
    FILE * f = wavfile_open(filename);
	if(!f)
	{
		printf("error: %s",strerror(errno));
		return 1;
	}
	wavfile_write(f,blur,length);
	wavfile_close(f);
	return 0;
}
