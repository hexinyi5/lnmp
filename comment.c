#include <stdio.h>
#include <stdlib.h>

int main()
{
  int a = 0;
  wchar_t wc = L'\x10';
  char s[10]="";

  a = wctomb( s, wc );

  printf("%d\n",a);
  printf("%s\n",s);
}
