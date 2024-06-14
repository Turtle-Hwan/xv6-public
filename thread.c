#include "types.h"
#include "stat.h"
#include "user.h"

/** join을 위해 어디까지 구현해야 하는가?
 * join을 하려면 thread_join() 내부에서 free해야 할 주소값을 알아야 한다.
 * 이를 위해 + thread가 여러 개 생성될 수도 있으니 static 배열로 thread 생성된 주소 공간 시작 주소를 저장해 놓으면?
 * 문제는 join 할 때 어떤 thread를 join해야 하는지 모르니까 각 thread별로 현재 작동하는지 여부와 thread_id 가 필요하다...
 * 으악 오류로 일단 킵.. => 굳이 배열로 구현 안해도 새 thread 생성 시 새로 malloc 되어 서로 다른 주소값을 가져서 잘 작동하는 듯하다.
 */

static void *thread_stack;

int thread_create(void(*fcn)(void *, void *), void *arg1, void *arg2) {
  void  *stack = malloc(4096);  // 기본 PGSIZE = 4096이라 4KB로 할당.
  if (stack == 0) {
    return -1;
  }

  thread_stack = stack;
  return clone(fcn, arg1, arg2, stack);
}

int thread_join() {
  int ret = join(&thread_stack);
  free(thread_stack);
  return ret;
}