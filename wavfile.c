#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include "wavfile.h"

const int NUMBER_OF_SAMPLES = (WAVFILE_SAMPLES_PER_SECOND*2);

struct wavfile_header {
	char	riff_tag[4];
	int	riff_length;
	char	wave_tag[4];
	char	fmt_tag[4];
	int	fmt_length;
	short	audio_format;
	short	num_channels;
	int	sample_rate;
	int	byte_rate;
	short	block_align;
	short	bits_per_sample;
	char	data_tag[4];
	int	data_length;
};

FILE * wavfile_open( const char *filename )
{
	struct wavfile_header header;

	int samples_per_second = WAVFILE_SAMPLES_PER_SECOND;
	int bits_per_sample = 16;

	strncpy(header.riff_tag,"RIFF",4);
	strncpy(header.wave_tag,"WAVE",4);
	strncpy(header.fmt_tag,"fmt ",4);
	strncpy(header.data_tag,"data",4);

	header.riff_length = 0;
	header.fmt_length = 16;
	header.audio_format = 1;
	header.num_channels = 1;
	header.sample_rate = samples_per_second;
	header.byte_rate = samples_per_second*(bits_per_sample/8);
	header.block_align = bits_per_sample/8;
	header.bits_per_sample = bits_per_sample;
	header.data_length = 0;

	FILE * file = fopen(filename,"wb+");
	if(!file) return 0;

	fwrite(&header,sizeof(header),1,file);

	fflush(file);

	return file;

}

void wavfile_write( FILE *file, short data[], int length )
{
	fwrite(data,sizeof(short),length,file);
}

void wavfile_close( FILE *file )
{
	int file_length = ftell(file);

	int data_length = file_length - sizeof(struct wavfile_header);
	fseek(file,sizeof(struct wavfile_header) - sizeof(int),SEEK_SET);
	fwrite(&data_length,sizeof(data_length),1,file);

	int riff_length = file_length - 8;
	fseek(file,4,SEEK_SET);
	fwrite(&riff_length,sizeof(riff_length),1,file);

	fclose(file);
}
int wavfile_add(short data[], FILE * file,int length)
{
    short newdata[NUMBER_OF_SAMPLES],new_waveform[NUMBER_OF_SAMPLES];
    printf("Dodawanie dźwięków...\n");
    printf("częstotliwość: \n");
    double frequency2;
    scanf("%lf", &frequency2);
    printf("głośność: \n");
    int volume2;
    scanf("%d", &volume2);
    for(int i=0;i<length;i++)
    {
        double t = (double) i / WAVFILE_SAMPLES_PER_SECOND;
        newdata[i] = volume2*sin(frequency2*t*2*M_PI);
    }
    FILE * g = wavfile_open("sound2.wav");
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
        new_waveform[i] = data[i] + newdata[i];
    }
    FILE * f = wavfile_open("sound_added.wav");
	if(!f)
	{
		printf("error: %s",strerror(errno));
		return 1;
	}
	wavfile_write(f,new_waveform,length);
	wavfile_close(f);
}
