#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct Buffer
{
  int *data;
  /*
  size_t size, count;
  size_t tip, tail;
  */
} Buffer;

int main(void)
{
  //Buffer *bufPtr, *bufQtr, *bufAtr, *bufBtr;
  int size = 40;
  int *bufPtr, *bufQtr=&size, *bufAtr, *bufBtr, *bufCtr;
  unsigned char c, *cPtr=&c;
  int *num;
  /*
  if( (bufPtr->data = calloc(1,sizeof(int))) == NULL  
      && (bufQtr->data = calloc(1,sizeof(int))) == NULL
      && (bufAtr->data = calloc(1,sizeof(int))) == NULL
      && (bufBtr->data = calloc(1,sizeof(int))) == NULL
    )
    return false;
  printf("%p\n",bufPtr->data);
  printf("%p\n",bufQtr->data);
  printf("%p\n",bufAtr->data);
  printf("%p\n",bufBtr->data);
  */
  if( (bufPtr = calloc(1,sizeof(int))) == NULL  
      && (bufQtr = calloc(1,sizeof(int))) == NULL
      && (bufAtr = calloc(1,sizeof(int))) == NULL
      && (bufBtr = calloc(1,sizeof(int))) == NULL
      && (bufCtr = calloc(1,sizeof(int))) == NULL
    )
    return false;
  *bufQtr = 2147451008;
  //cPtr = (unsigned char *)&size;
  cPtr = (unsigned char *)bufQtr;   // 正常指针bufQtr指向的数据类型为int, 其具有4个字节, 带有符号的int类型, 最大值为2147483647
                                    // 但是在进行指针类型转换时(如, 带符号整型转换为字符型), 因字符型(char)仅用1个字节存储, 那么对应4字节的带符号的整型
				    // 来说, 只能将4字节地址的某一个地址做转换, 是从可见十进制(2147483647)对应二进制的最高位的前8位还是从最低位的后8位
				    // 二进制最高位就是十进制最高位, 二进制最低位就是十进制最低位, 那么具体是从哪个方向来做转换换成
				    // 答案是, 从二进制最低位开始, 当赋值后字符指针进行自增时, 就会朝无符号整型的二进制高位方向移动
				    // 对于无符号字符型, 指针的赋值, 最小单位是1字节(1字节等于8比特), 一次移动的距离也是8比特
  ++cPtr;
  c = 'c';
  printf("%c,%u\n",c,*cPtr);
  num = (int *)&c;
  //cPtr = (char *)num;
  //num = (int *)&cPtr;
  
  //printf("%d\n",num);

  /*
  printf("%p\n",bufPtr);
  printf("%p\n",bufQtr);
  printf("%p\n",bufAtr);
  printf("%p\n",bufBtr);
  printf("%p\n",bufCtr);

  int a = 0, b = 0, c = 0, *m=&a, *n=&b, *p=&c;
  printf("%p\n",m);
  printf("%p\n",n);
  printf("%p\n",p);
  */
}
