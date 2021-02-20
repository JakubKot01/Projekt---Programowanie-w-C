#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>

#include "frequencies.h"
#include "wavfile.h"
#include "functions.h"

int main()
{
    int volume1, length;
    double frequency1;
    int command;
    short merged[NUMBER_OF_SAMPLES], random[NUMBER_OF_SAMPLES];
    do
    {
        printf("[1]waveform\n[2]op_add\n[3]op_filter\n[4]noise\n[5]exit\n");
        scanf("%d", &command);
        if(command == 1)
        {
            char x[14];
            printf("nazwa pliku: ");
            scanf("%s", x);
            strcat(x, ".wav");
            printf("%s\n", x);
            printf("częstotliwość: ");
            scanf("%lf", &frequency1);
            printf("%lf\n", frequency1);
            printf("głośność: ");
            scanf("%d", &volume1);
            printf("%d\n", volume1);
            length = NUMBER_OF_SAMPLES;
            waveform_create(x, volume1, frequency1, length);
            printf("utworzono plik o nazwie: %s\n", x);
        }
        if(command == 2)
        {
            char y[14];
            printf("nazwa pliku: ");
            scanf("%s", y);
            strcat(y, ".wav");
            printf("%s\n", y);
            int volume2;
            double frequency2;
            printf("częstotliwość: ");
            scanf("%lf", &frequency2);
            printf("%lf\n", frequency2);
            printf("głośność: ");
            scanf("%d", &volume2);
            printf("%d\n", volume2);
            wavfile_add(merged, y, length, volume1, volume2, frequency1, frequency2);
        }
        if(command == 3)
        {
            printf("częstotliwość: ");
            scanf("%lf", &frequency1);
            printf("%lf\n", frequency1);
            printf("głośność: ");
            scanf("%d", &volume1);
            printf("%d\n", volume1);
            length = NUMBER_OF_SAMPLES;
            noise(random, merged, length);
        }
        if(command == 4)
        {

            char z[14];
            printf("nazwa pliku: ");
            scanf("%s", z);
            strcat(z, ".wav");
            printf("%s\n", z);
            int range;
            printf("promień: ");
            scanf("%d", &range);
            printf("%d\n", range);
            length = NUMBER_OF_SAMPLES;
            blur(z, random, range, length);
        }
    }while(command!=5);
	return 0;
}
