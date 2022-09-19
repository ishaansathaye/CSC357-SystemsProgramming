#include <stdio.h>

void start() {}
void pause() {}

void function_one()
{
   int first = 0;
   int nums[5];
   int mid = 10;

   for (int i = 0; i < 5; i++) {
      nums[i] = i;
   }

   pause();
}

int main(void)
{
   start();
   function_one();

   return 0;
}
