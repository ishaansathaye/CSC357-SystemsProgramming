#include <stdio.h>

void start() {}
void pause() {}

void function_one(int input)
{
   int function_one_local = input;

   pause();
}

int main(void)
{
   int first = 357;
   int second = 0;

   start();

   function_one(first);

   return 0;
}
