#include <fcntl.h>
#include <semaphore.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

struct message {
  uint8_t reg;
  int flag[4];
};

struct message msg;
int main() {

  key_t key = 12345;
  int msgid = msgget(key, 0666 | IPC_CREAT);

  if (msgid == -1) {
    printf("\nMESSAGE QUEUE NOT CREATED OR NOT FOUND\n");
    exit(1);
  }

  while (1) {
    msgrcv(msgid, &msg, sizeof(msg), 0, 0);
    printf("_________________________________________________");
    if (msg.flag[0] == 0) {
      printf("\nKEY IS NOT ON\n");
    }
    if (msg.flag[1] == 0) {
      printf("\nSEAT BELTS ARE NOT WORN\n");
    }
    if (msg.flag[2] == 0) {
      printf("\nDOORS ARE NOT LOCKED\n");
    }
    if (msg.flag[3] == 0) {
      printf("\nHANDBREAKS ARE NOT APPLIED\n");
    }

    if (msg.flag[0] == 1 && msg.flag[1] == 1 && msg.flag[2] == 1 &&
        msg.flag[3] == 1) {
      printf("\nSIGNAL IS SENT TO THE IGNITION COIL\n");
      sleep(3);
      printf("\nVEHICLE IS ON RIDE SAFE\n");
      break;
    }
  }
  return 0;
}
