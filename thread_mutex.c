#include <stdio.h>
#include <threads.h>

/*
typedef int (*thrd_start_t) (void*);
extern int thrd_create (thrd_t *__thr, thrd_start_t __func, void *__arg);
extern int thrd_join (thrd_t __thr, int *__res);
typedef unsigned long int thrd_t;
typedef int (*thrd_start_t) (void*);
*/

#define COUNT 10000000L

long counter = 0, i;
mtx_t mtx;

void incFunc(void) { for ( long i = 0; i < COUNT; ++i )
	             { mtx_lock(&mtx); ++counter;  mtx_unlock(&mtx); }
                   }
void decFunc(void) { for ( long i = 0; i < COUNT/2; ++i ) 
	             { mtx_lock(&mtx); --counter;  mtx_unlock(&mtx); }
		   }
/*
void incFunc(void) { for ( long i = 0; i < COUNT; ++i ) ++counter; }
void decFunc(void) { for ( long i = 0; i < COUNT; ++i ) --counter; }
*/


int main()
{
  //printf("%ld",sizeof(int));
  clock_t cl = clock();
  thrd_t th1, th2, th3;

  if( mtx_init(&mtx, mtx_plain) != thrd_success )
  {
    fprintf(stderr, "Error initializing the mutex.\n");
    return -1;
  }

  if ( thrd_create(&th1, (thrd_start_t)incFunc, NULL) != thrd_success 
       || thrd_create(&th2, (thrd_start_t)decFunc, NULL) != thrd_success
       || thrd_create(&th3, (thrd_start_t)decFunc, NULL) != thrd_success )
  {
    fprintf( stderr, "Error creating thread\n"); return -1;
  }
  thrd_join( th1, NULL );
  thrd_join( th2, NULL );
  thrd_join( th3, NULL );

  printf("Counter: %ld \t", counter );
  printf("CPU time: %ld ms\n", (clock() -cl)*1000L/CLOCKS_PER_SEC);

  mtx_destroy(&mtx);
  return 0;
  
}
