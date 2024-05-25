#include "types.h"
#include "stat.h"
#include "user.h"
#include "rand.c"

#define PROC_NUM 5

void exit_child(int pid) {
  // int p;

  // p = wait();
  // printf(1, "process %d exited\n", p);
  wait();
}


int main(int argc, char **argv)
{
  int pid[PROC_NUM]; //여러 개 process 담을 배열
  
  ticketset(100);

  printf(1, "Test Case 1 : every ticket is 10\n");
  for (int i = 0; i < PROC_NUM; i++) {
    pid[i] = fork();
    if (pid[i] == 0) {
      //child process
      printf(1, "process %d my ticket %d\n", getpid(), ticketget());
      exit();
    }
  }
  for(int i = 0; i < PROC_NUM; i++)
    exit_child(pid[i]);


  ////////////////////////
  printf(1, "\n\nTest Case 2 : different number of ticket (50, 40, 30, 20, 10)\n");
  rand_index = 0;
  for (int i = 0; i < PROC_NUM; i++) {
    pid[i] = fork();
    if (pid[i] == 0) {
      //child process
      ticketset(50 - i*10);
      printf(1, "process %d my ticket %d\n", getpid(), ticketget());
      exit();
    }
  }
  for(int i = 0; i < PROC_NUM; i++)
    exit_child(pid[i]);


  ////////////////////////
  printf(1, "\n\nTest Case 3 : different number of ticket (30, 20, 10, 50, 40)\n");
  rand_index = 0;
  int ticket_array[PROC_NUM] = {30, 20, 10, 50, 40};
  for (int i = 0; i < PROC_NUM; i++) {
    pid[i] = fork();
    if (pid[i] == 0) {
      //child process
      ticketset(ticket_array[i]);
      printf(1, "process %d my ticket %d\n", getpid(), ticketget());
      exit();
    }
  }
  for(int i = 0; i < PROC_NUM; i++)
    exit_child(pid[i]);


  ////////////////////////
  printf(1, "\n\nTest Case 4 : ticket 1 vs. ticket 100(parent)\n");
  rand_index = 0;
  printf(1, "process %d my ticket %d [parent]\n", getpid(), ticketget());

  pid[0] = fork();
  if (pid[0] == 0) {
    //child process
    ticketset(1);
    printf(1, "process %d my ticket %d\n", getpid(), ticketget());
    exit();
  }
  printf(1, "process %d my ticket %d [parent]\n", getpid(), ticketget());
  exit_child(pid[0]);


  ////////////////////////
  printf(1, "\n\nTest Case 5 : ticket 1, ticket 1 vs. ticket 100(parent)\n");
  rand_index = 0;
  printf(1, "process %d my ticket %d [parent]\n", getpid(), ticketget());
  for (int i = 0; i < 2; i++) {
    pid[i] = fork();
    if (pid[i] == 0) {
      //child process
      ticketset(1);
      printf(1, "process %d my ticket %d\n", getpid(), ticketget());
      exit();
    }
  }
  printf(1, "process %d my ticket %d [parent]\n", getpid(), ticketget());
  exit_child(pid[0]);
  exit_child(pid[1]);

  exit();
}