#ifndef WAVFILE_H
#define WAVFILE_H

#include <stdio.h>
#include <inttypes.h>

FILE * wavfile_open( const char *filename );
void wavfile_write( FILE *file, short data[], int length );
void wavfile_close( FILE * file );
void wavfile_read( FILE * file);
int wavfile_add(short data[], FILE * file, int length, int vol, int freq);

#define WAVFILE_SAMPLES_PER_SECOND 44100

#endif
