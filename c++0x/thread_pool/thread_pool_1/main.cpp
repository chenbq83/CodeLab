#include <iostream>
#include "ThreadPool.h"

using namespace std;

void fun(void)
{
   this_thread::sleep_for(chrono::milliseconds(200));
   cout << "Job executed" << endl;
}

int main(int argc, char** argv)
{
   netlib::ThreadPool pool(5);
   pool.start();
   
   for (int i = 0; i < 10; i++)
   {
      pool.addTask(fun);
      this_thread::sleep_for(chrono::milliseconds(200));
   }

   pool.stop();
   return 0;
}
