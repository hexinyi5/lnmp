// fn_tbl.c: 以表格形式输出一个函数的值, 该程序使用了嵌套的宏
// --------------------------------------------------------------
#include <stdio.h>
#include <math.h>                                      // 函数cos()和exp()的原型

#define PI            3.141593
#define STEP          (PI/8)
#define AMPLITUDE     1.0
#define ATTENUATION   0.1                             // 声波传播的衰减指数
#define DF(x)         exp(-ATTENUATION*(x))
#define FUNC(x)       (DF(x) * AMPLITUDE * cos(x))    // 震动衰减

// 针对函数输出
#define STR(s) #s
#define XSTR(s) STR(s)                                // 将宏s展开, 然后字符串化

int main()
{
  double x = 0.0;

  printf( "\nFUNC(x) = %s\n", XSTR(FUNC(x)) );        // 输出该函数

  printf("\n %10s %25s\n", "x", STR(y = FUNC(x)) );   // 表格的标题
  printf("---------------------------------------------\n");

  for( ; x < 2*PI + STEP/2; x += STEP )
    printf( "%15f %20f\n", x, FUNC(x) );

  return 0;
}
