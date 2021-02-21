#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <inttypes.h>

int arytm(int range, short waveform[], int i, int length);
int waveform_create(const char * filename, int vol, double freq, int length);
int wavfile_add(short new_waveform[], const char *filename,int length, int vol1, int vol2, int freq1, int freq2);
int noise(short noise[], short waveform[], int length);
int blur(const char *filename, short waveform[], int range, int length);

#endif
