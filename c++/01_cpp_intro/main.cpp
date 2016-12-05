#include <iostream>
#include "add.h"
#include "sub.h"

using namespace std;

int main(int argc, char* argv[])
{
   int a = 10;
   int b = 3;

   cout << "a + b = " << add(a, b) << endl;
   cout << "a - b = " << sub(a, b) << endl;

   return 0;
}
