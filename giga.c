#include <stdio.h>
#include <stdlib.h>

int main()
{  
  void *p;
  
  p = (void *) calloc(1, 1024 * 1024 * 1024);
  
  return 0;
}
