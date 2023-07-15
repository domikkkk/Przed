#include <stdio.h>


int increasing(char * s);

int main(void)
{
  char text[]="# 2 4 6 8 756 <AAAAARRRTT> [artur}";
  char text1[]="";
  char text2[]="987655442311";
  char text3[]="abcdefght";
  printf("Input string      > %s\n", text3);
  int result = increasing(text3);
  printf("Conversion results> %s\n", text3);
  printf("Return value	    > %d\n", result);

  return 0;
}

