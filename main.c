#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sched.h>
#include <time.h>
#include <pthread.h>
#include <sys/resource.h> // setrlimit
#include <unistd.h>
#include <errno.h>

#define handle_error_en(en, msg) \
      do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

void *simulate_sensor_task(){
   fprintf(stderr, "Hello, world!\n");
}

int setrlimit_wrapper()
{
   struct rlimit oRlim;
   oRlim.rlim_cur = -1;
   oRlim.rlim_max = -1;
   return setrlimit(RLIMIT_RTPRIO, &oRlim);
}

int main()
{
    pthread_attr_t attr;
    pthread_t sensor_id;
    struct sched_param  mypar;
    int rv = 0;

    mypar.sched_priority = 10;
   

    fprintf(stderr, "rlim                       =%i\n", setrlimit_wrapper());  
    fprintf(stderr, "attr_init                  =%i\n", pthread_attr_init(&attr));
    fprintf(stderr, "inherit_sched              =%i\n", pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED));
    fprintf(stderr, "policy                     =%i\n", pthread_attr_setschedpolicy(&attr, SCHED_RR));
    fprintf(stderr, "pthread_attr_setschedparam =%i\n", pthread_attr_setschedparam(&attr, &mypar));
    fprintf(stderr, "pthread_create             =%i\n", (rv = pthread_create(&sensor_id, &attr, simulate_sensor_task, NULL)));

    if (rv != 0)
    {
         errno = rv;
         perror("pthread_create failed");
    }
    else
    {
       pthread_join(rv, NULL);
       fprintf(stderr, "Succesfully created thread\n");
    }

    return rv;
}

