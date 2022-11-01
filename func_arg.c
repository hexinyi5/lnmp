#include <stdio.h>
#include <stdbool.h>


//bool compare( const void *s1, const void *s2 );
//int search( void *arr, int datacount, int el_size, void *x, bool compare);

bool compare( const void *s1, const void *s2 )
{
  return ( *(int *)s1 == *(int *)s2 );
}

int search( void *arr, int datacount, int el_size, void *x, bool compare(const void *s1, const void *s2))
{
  char *ptr = (char *)arr;

  int i = 0;
  
  for( i = 0; i < datacount; i++ )
    if( compare( ptr + i * el_size, x ) )
      return i;

  return -1;
}

int main()
{
  int arr[] = { 2, 5, 7, 90, 70 };
  int n = sizeof(arr) / sizeof(arr[0]);
  int x = 7;


  printf("Return index is %d\n", search( arr, n, sizeof(arr[0]), &x, compare ));

  return 0;
}
