#include <stdio.h>

double test( double x )
{
  double y = 1.0;
  {
    double y;
    y = x * 2;
  }
  return y;
}

int main()
{
  double a = 2.0;

  printf("%.2lf\n",test(a));
}
