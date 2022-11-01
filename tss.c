// 使用线程存储
#include <threads.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

tss_t key;                            // 用于TSS指针的全局键

int thFunc(void *arg);                // 线程函数
void destructor(void *data);          // 析构函数

int main(void)
{
  thrd_t th1, th2;
  int result1=0, result2=0;

  // 创建一个TSS秘钥
  if( tss_create(&key, destructor) != thrd_success )
    return -1;

  // 创建线程
  if( thrd_create(&th1, thFunc, "Thread_1") != thrd_success || thrd_create(&th2, thFunc, "Thread_2") != thrd_success )
    return -2;

  thrd_join(th1, &result1);
  thrd_join(th2, &result2);
  if( result1 != 0 || result2 != 0 )
    fputs("Thread error\n", stderr);
  else
    puts("Threads finished without error.");

  tss_delete(key);                     // 释放TSS指针所有的资源
  return 0;
}

void print(void){ printf( "print: %s\n", (char*)tss_get(key) ); }

int thFunc(void *arg)
{
  char *name = (char*)arg;
  size_t size = strlen(name) + 1;

  // 设置线程存储
  if( tss_set(key, malloc(size)) != thrd_success )
    return -1;

  // 存储数据
  strcpy((char*)tss_get(key), name);
  print();
  return 0;
}

void destructor(void *data) { printf("Destructor for %s\n", (char*)data); free(data); }  // 释放内存
