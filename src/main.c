#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define PULSE_BUFFER_SIZE       256
#define REPEAT_TIMEOUT_MSEC     100

#if defined(__arm__) || defined(__TARGET_ARCH_ARM)
/* v2r davinchi arm platform */
#define IRSEND_DEVICE           "/dev/v2r_irsend"
#else
/* osx test platform */
#define IRSEND_DEVICE           "v2r_irsend.txt"
#endif

unsigned int  pulse_array[PULSE_BUFFER_SIZE];
//= {
//        4796, 1584,
//        1584, 4796,
//        1584, 4796,
//        1584, 4796,
//        1584, 4796,
//        1584, 4796,
//        1584, 4796,
//        4796, 1584,
//        0};

void msleep(int ms) {
        struct timespec time;
        time.tv_sec = ms / 1000;
        time.tv_nsec = (ms % 1000) * (1000 * 1000);
        nanosleep(&time,NULL);
}

void send_array (unsigned int * array, int repeat) {
        size_t req_sz = 0;
        //считаем длинну массива
        for (int i = 0; array[i]!=0; i++) {
                // printf( "%i: %i\n", i, array[i] );
                req_sz++;
        }
        req_sz++;

        //пересчитываем длинну массива в байтах
        req_sz=req_sz*sizeof(unsigned int);

        //открвываем файл длязаписи
        int devfile = open(IRSEND_DEVICE, O_WRONLY);
        if(devfile < 0){
                perror("open");
                exit(-1);
        }

        //записываем
        for (int i = 0; i < repeat; i++) {
                if((write(devfile, array, req_sz))!=req_sz){
                        printf( "Device file Write Error!\n" );
                }
                msleep(REPEAT_TIMEOUT_MSEC);
        }
        close(devfile);
}

int
main(int argc, char *argv[]) {
        int repeat = 1;
        int first = 1;
        if ( argc < 2 ) {
                printf( "usage: %s [-c count_repeat] pulses ..\n", argv[0] );
                exit(-1);
        }
        else {
                if ( strcmp(argv[1], "-c") == 0 ) {
                        repeat = atoi(argv[2]);
                        first = 3;
                }
                int pulse_pos = 0;
                for (int i = first; i < argc; i++) {
                        pulse_array[pulse_pos++] = (unsigned)atoi(argv[i]);
                }
                pulse_array[pulse_pos] = 0;
                printf( "repeate: %i pulses: %i\n", repeat, pulse_pos);
                send_array((unsigned int*)&pulse_array, repeat);
        }

        return 0;
}

