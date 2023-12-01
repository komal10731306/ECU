#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

struct SDF {
  float temperature;
  float speed;
  float pressure;
  float fused;
};

typedef struct SDF *SDFP;

struct SDF input() {

  struct SDF avg;
  float input;
  float temp, pressure, speed;
  float w_temp = 0.4;
  float w_pressure = 0.3;
  float w_speed = 0.3;
  int n = 3;

  for (int i = 1; i <= n; i++) {
    printf("________________________________________________________________");
  t:
    printf("\nENTER THE TEMPERATURE (in Celsius(C)) (>180)\n");
    scanf("%f", &temp);
    if (temp < 180) {
      printf("\nINVALID INPUT\n");
      goto t;
    }

  p:
    printf("\nENTER THE PRESSURE (in KiloPascals(kPA)) (25-65)\n");
    scanf("%f", &pressure);
    if (pressure < 25 || pressure > 65)

    {
      printf("\nINVALID INPUT\n");
      goto p;
    }

  s:
    printf("\nENTER THE SPEED (IN RPM) (0-4000)\n");
    scanf("%f", &speed);
    if (speed < 0 || speed > 4000) {
      printf("\nINVALID INPUT\n");
      goto s;
    }

    avg.temperature += temp;
    avg.pressure += pressure;
    avg.speed += speed;
  }

  avg.temperature /= n;
  avg.pressure /= n;
  avg.speed /= n;
  avg.fused = (avg.temperature * w_temp) + (avg.pressure * w_pressure) +
              (avg.speed * w_speed);

  return avg;
}

int main() {

  struct SDF sdata;
  SDFP shared_memory;
  int shmid, key_t = 23452;

  shmid = shmget(key_t, 1024, 0666 | IPC_CREAT);
  // printf("KEY OF THE SHARED MEMORY IS %d\n", shmid);
  shared_memory = (SDFP)shmat(shmid, NULL, 0);

  if (shmid == -1) {
    printf("\nSHARED MEMORY NOT ASSIGNED\n");
    exit(0);
  }

  sdata = input();
  *shared_memory = sdata;

  printf(
      "YOU WROTE\n temp :%.2f\t pressure: %.2f speed:%.2f\nfused data:%.2f\n",
      shared_memory->temperature, shared_memory->pressure, shared_memory->speed,
      shared_memory->fused);
}
