#include <stdio.h>

void start() {}
void pause() {}

void function_one(int input)
{
   int function_one_local = input;
}

int function_two(int input)
{
   int function_two_local;

   function_two_local = input;

   pause();

   return function_two_local;
}

int main(void)
{
   int first = 357;
   int second = 0;

   start();
   function_one(first);
   function_two(second);

   return 0;
}
