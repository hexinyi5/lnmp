#include <stdlib.h>                                 // 为了使用malloc()和free()
#include "buffer.h"
extern int thrd_create (thrd_t *__thr, thrd_start_t __func, void *__arg);
extern int thrd_join (thrd_t __thr, int *__res);
extern int mtx_init (mtx_t *__mutex, int __type);
extern int mtx_lock (mtx_t *__mutex);
extern int mtx_unlock (mtx_t *__mutex);
extern void mtx_destroy (mtx_t *__mutex);
extern int cnd_init (cnd_t *__cond);
extern int cnd_signal (cnd_t *__cond);
extern int cnd_timedwait (cnd_t *__restrict __cond,
		          mtx_t *__restrict __mutex,
			  const struct timespec *__restrict __time_point);

bool bufInit( Buffer *bufPtr, size_t size )
{
  if( (bufPtr->data = malloc( size * sizeof(int))) == NULL )              // 之所以sizeof对于int进行计算内存空间占用, 是因为结构体Buffer中将要存储数据类型就是int
    return false;                                                         // 判断是否有足够的内存空间用于分配, bufPtr->data表示分配内存空间的首地址
  bufPtr->size = size;
  bufPtr->count = 0;
  bufPtr->tip = bufPtr->tail = 0;
  return mtx_init( &bufPtr->mtx, mtx_plain ) == thrd_success
	  && cnd_init( &bufPtr->cndPut ) == thrd_success
	  && cnd_init( &bufPtr->cndGet ) == thrd_success;
}

void bufDestroy( Buffer *bufPtr )
{
  cnd_destroy( &bufPtr->cndGet );
  cnd_destroy( &bufPtr->cndPut );
  mtx_destroy( &bufPtr->mtx );
  free( bufPtr->data );
}

// 在缓冲区中插入一个新元素
bool bufPut( Buffer *bufPtr, int data )
{
  mtx_lock( &bufPtr->mtx );

  while( bufPtr->count == bufPtr->size )
    if( cnd_wait( &bufPtr->cndPut, &bufPtr->mtx ) != thrd_success )
      return false;

  bufPtr->data[bufPtr->tip] = data;
  bufPtr->tip = (bufPtr->tip + 1) % bufPtr->size;
  ++bufPtr->count;

  mtx_unlock( &bufPtr->mtx );
  cnd_signal( &bufPtr->cndGet );

  return true;
}

// 从缓冲区中移除一个元素
// 如果缓冲区是空的, 则等待不超过sec秒
bool bufGet( Buffer *bufPtr, int *dataPtr, int sec )
{
  struct timespec ts;
  timespec_get( &ts, TIME_UTC );                                    // 当前时间
  ts.tv_sec += sec;                                                 // +sec秒延时

  mtx_lock( &bufPtr->mtx );

  while( bufPtr->count == 0 )
    if( cnd_timedwait( &bufPtr->cndGet, &bufPtr->mtx, &ts ) != thrd_success )
      return false;

  *dataPtr = bufPtr->data[bufPtr->tail];
  bufPtr->tail = (bufPtr->tail + 1) % bufPtr->size;
  --bufPtr->count;

  mtx_unlock( &bufPtr->mtx );
  cnd_signal( &bufPtr->cndPut );

  return true;
}
