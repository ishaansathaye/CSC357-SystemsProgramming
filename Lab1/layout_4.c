#include <stdio.h>

void start() {}
void pause() {}

void function_one()
{
   int first = 0;
   char s1[] = "357";
   int mid = 10;
   char *s2 = "357";    // this is different
   int last = 999;

   pause();
}

int main(void)
{
   start();
   function_one();

   return 0;
}
