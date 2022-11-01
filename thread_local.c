// 使用一个线程对象
#include <stdio.h>
#include <threads.h>

thread_local int var = 10;

void print_var(void){ printf("var = %d\n", var); }
int func(void *);

int main(int argc, char *argv[])
{
  thrd_t th1;
  if( thrd_create( &th1, func, NULL ) != thrd_success ){
    fprintf(stderr, "Error creating thread.\n");
    return 0xff;
  }

  var += 1;
  print_var();
  thrd_join(th1, NULL);
  return 0;
}

int func(void *arg)
{
  var += 10;
  print_var();
  return 0;
}
