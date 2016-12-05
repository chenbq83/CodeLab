#include "a.h"
#include <iostream>

using namespace std;

int var = 100;

int main(void)
{
   int var = 50;
   cout << "::var = " << ::var << endl;
   cout << "var = " << var << endl;

   cout << abs(-2) << endl;
   cout << abs2(-0.5) << endl;

   return 0;
}

