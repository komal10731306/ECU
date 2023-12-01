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

int val;
void key_on();
void seat_belt();
void door_lock();
void hand_break();

int main() {
  msg.reg = 0;
  msg.flag[0] = 0;
  msg.flag[1] = 0;
  msg.flag[2] = 0;
  msg.flag[3] = 0;
  key_t key = 12345;
  int msgid = msgget(key, 0666 | IPC_CREAT);

  if (msgid == -1) {
    printf("\nMESSAGE QUEUE NOT CREATED OR NOT FOUND\n");
    exit(1);
  }

  do {

    printf(
        "__________________________________________________________________");

    if (msg.flag[0] == 0)
      key_on();

    if (msg.flag[1] == 0)
      seat_belt();

    if (msg.flag[2] == 0)
      door_lock();

    if (msg.flag[3] == 0)
      hand_break();

    printf(
        "__________________________________________________________________");
    printf("%d\n", msg.reg);
    msgsnd(msgid, &msg, sizeof(msg), 0);

  } while (msg.reg != 63);
}

void key_on() {
key:
  printf("\nPLEASE TURN ON THE KEY : 0 for NO 1 for YES\n");
  scanf("%d", &val);
  if (val > 1 || val < 0) {
    printf("\nInvalid input\n");
    goto key;
  }
  if (val == 1) {
    msg.reg = msg.reg | 7;
    msg.flag[0] = 1;
  }
}

void seat_belt() {
belt:
  printf("\nPLEASE WEAR ON THE SEAT BELTS : 0 for NO 1 for YES\n");
  scanf("%d", &val);
  if (val > 1 || val < 0) {
    printf("\nINVALID INPUT\n");
    goto belt;
  }
  if (val == 1) {
    msg.reg = msg.reg | (1 << 3);
    msg.flag[1] = 1;
  }
}

void door_lock() {
lock:
  printf("\nPLEASE LOCK THE DOORS : 0 for NO 1 for YES\n");
  scanf("%d", &val);
  if (val > 1 || val < 0) {
    printf("\nINVALID INPUT\n");
    goto lock;
  }
  if (val == 1) {
    msg.reg = msg.reg | (1 << 4);
    msg.flag[2] = 1;
  }
}

void hand_break() {
hbreak:
  printf("\nPLEASE APLLY HANDBREAKS : 0 for NO 1 for YES\n");
  scanf("%d", &val);
  if (val > 1 || val < 0) {
    printf("\nINVALID INPUT\n");
    goto hbreak;
  }
  if (val == 1) {
    msg.reg = msg.reg | (1 << 5);
    msg.flag[3] = 1;
  }
}
