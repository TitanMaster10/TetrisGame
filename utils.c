#include "utils.h"
#include <unistd.h>
#include <sys/time.h>


void intarzie(int ms) { // nu este suficient
    usleep(ms * 1000);
}

unsigned long timp_curent_ms(void){
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return (unsigned long)(tv.tv_sec) * 1000 + (unsigned long)(tv.tv_usec) /1000;
}