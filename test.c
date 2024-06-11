#include "types.h"
#include "stat.h"
#include "user.h"
#include "thread.h"

void wrapper(void *arg1, void *arg2) {
  printf(1, "this is thread wrapper func\n");
  *(int *)arg1 = 100;
  *(int *)arg2 = 50;
}

int main() {
  int a = 0;
  int b = 1;
  int tid = thread_create(wrapper, (void *)&a, (void *)&b);
  if (tid == -1) {
    printf(1, "thread create error\n");
  }

  tid = thread_join();
  if (tid == -1) {
    printf(1, "thread join error\n");
  }

  if (a != 100) {
    printf(1, "thread running error\n");
  }

  exit();
}