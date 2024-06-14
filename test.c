#include "types.h"
#include "stat.h"
#include "user.h"
#include "thread.h"

void wrapper(void *arg1, void *arg2) {
  printf(1, "[thread wrapper func] arg1 : %d, arg2 : %d | addr : %p, %p\n", *(int *)arg1, *(int *)arg2, arg1, arg2);

  *(int *)arg1 = 100;
  *(int *)arg2 = 50;

  printf(1, "[thread wrapper func (change args)] arg1 : %d, arg2 : %d | addr : %p, %p\n", *(int *)arg1, *(int *)arg2, arg1, arg2);
  exit();
}

int main() {
  int a = 9;
  int b = 3;

  int tid = thread_create(wrapper, (void *)&a, (void *)&b);
  if (tid == -1) {
    printf(1, "thread create error\n");
  } else {
    printf(1, "[Init Local var] a : %d, b : %d\n", a, b);
    printf(1, "Thread %d Created!!\n", tid);
  }

  tid = thread_join();
  if (tid == -1) {
    printf(1, "thread join error\n");
  } else {
    printf(1, "Thread %d Joined!!\n", tid);
  }

  if (a != 100 || b != 50) {
    printf(1, "thread running error\n");
  }

  printf(1, "[Thread join Result] a : %d, b : %d\n", a, b);
  exit();
}