#include "types.h"
#include "stat.h"
#include "user.h"
#include "thread.h"

void wrapper(void *arg1, void *arg2) {
  printf(1, "this is thread wrapper func1 : %d, %d\n", *(int *)arg1, *(int *)arg2);
  *(int *)arg1 = 100;
  *(int *)arg2 = 50;
  printf(1, "this is thread wrapper func2 : %d, %d\n", *(int *)arg1, *(int *)arg2);

  //exit();
}

int main() {
  int a = 9;
  int b = 3;
  int tid = thread_create(wrapper, (void *)&a, (void *)&b);
  if (tid == -1) {
    printf(1, "thread create error\n");
  }

  tid = thread_join();
  printf(1, "join fin / a : %d, b : %d", a, b);
  if (tid == -1) {
    printf(1, "thread join error\n");
  }

  if (a != 100) {
    printf(1, "thread running error\n");
  }

  exit();
}