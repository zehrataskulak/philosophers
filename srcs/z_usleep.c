#include "../philo.h"

void z_usleep(int microsecond)
{
    struct timeval	tv;
    long long start_time;
    long long end_time;

    gettimeofday(&tv, NULL);
    start_time = tv.tv_sec * 1000000LL + tv.tv_usec;
    end_time = start_time;
    while(1)
    {
        gettimeofday(&tv, NULL);
        end_time = tv.tv_sec * 1000000LL + tv.tv_usec;
        if(end_time - start_time >= microsecond)
            break;
    }
}