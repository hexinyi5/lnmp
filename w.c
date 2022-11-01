#include <stdio.h>

int foo ( unsigned int x )
{
  if( x < 0 )
    return 0;  // cannot occur
  else
    return 1;
}

int main()
{
  unsigned int a= (unsigned int)-1 ;
  printf("%u\n", a);
  printf("%d\n",foo(a));
} 
