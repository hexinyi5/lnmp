#include <stdio.h>
#include <string.h>

int sum( int a[], unsigned len )
{
  unsigned i, sum = 0;
  for( i = 0; i <= len - 1; ++i )
    sum += a[i];

  return sum;
}

int main()
{
  int a[] = {};
  unsigned len;

  len = sizeof(a) / sizeof(a[0]);
  printf("len = %d; sum = %d\n", len, sum(a, len));
  return 0;
}
