#include <stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/shm.h>
struct SDF {
    float temperature;
    float speed;
    float pressure;
    float fused;
};

typedef struct SDF *SDFP;


int main(void) {
    SDFP shared_memory;
    int shmid , key_t=23452;
    shmid=shmget(key_t,sizeof(struct SDF),0666);
    if(shmid==-1)
    {
        printf("\nSHARED MEMORY NOT FOUND\n");
        exit(0);
    }
    shared_memory=(SDFP)shmat(shmid,NULL,0);
    printf("\n RECEIVED DATA\n Temperature:%.2f\n Speed:%.2f\n Pressure:%.2f\n Fused:%.2f\n",shared_memory->temperature,shared_memory->speed,shared_memory->pressure,shared_memory->fused);
    return 0;
}
