#include "types.h"
#include "stat.h"
#include "user.h"

/** join을 위해 어디까지 구현해야 하는가?
 * join을 하려면 thread_join() 내부에서 free해야 할 주소값을 알아야 한다.
 * 이를 위해 + thread가 여러 개 생성될 수도 있으니 static 배열로 thread 생성된 주소 공간 시작 주소를 저장해 놓으면?
 * 문제는 join 할 때 어떤 thread를 join해야 하는지 모르니까 각 thread별로 현재 작동하는지 여부와 thread_id 가 필요하다...
*/
#define MAX_THREAD_NUM 100

struct thread_info {
  int   tid;        //thread_id
  int   is_running; //사용중이면 1, 아니면 0
  void  *addr;      //thread에 할당된 주소공간 시작 주소
};

static struct thread_info t_info[MAX_THREAD_NUM];
static int now_thread_num = 0;

int thread_create(void(*fcn)(void *, void *), void *arg1, void *arg2) {
  void  *stack = malloc(4096);
  if (stack == 0) {
    return -1;
  }

  struct thread_info newThread;
  newThread.tid = now_thread_num + 1;
  now_thread_num += 1;

  printf(1, "THREAD: create\n");
  return clone(fcn, arg1, arg2, stack);
}

int thread_join() {
  //pthread_join과 달리 tid를 따로 받지 않으므로 아무 thread가 하나 종료될 때까지 대기하고, 메모리 회수하는 것으로 구현.
  for (int i = 0; i < MAX_THREAD_NUM; i++) {
    printf(1, "\nt_info : %d | t_info.tid : %d\n",t_info[0], t_info[0].tid);
    if (t_info[i].tid == 0)
      break;
    if (t_info[i].is_running == 0) {
      join(t_info[i].addr);
      break;
    }
  }
  printf(1, "THREAD: join\n");
  return 1;
}