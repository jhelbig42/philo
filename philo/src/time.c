#include "../inc/philo.h"

int main(int argc, char **argv)
{
    //beginning time
    long long usec_start;
    long long usec_end;
    long long elapsed_time;
    struct timeval start_time;
    struct timeval end_time;

    gettimeofday(&start_time, NULL);
    usec_start = start_time.tv_sec * 1e6 + start_time.tv_usec;
    
    usleep(100);

    gettimeofday(&end_time, NULL);
    usec_end = end_time.tv_sec * 1e6 + end_time.tv_usec;

    elapsed_time = usec_end - usec_start;
    printf("elapsed time: %lld\n", elapsed_time);
}
