/*
 * http://en.cppreference.com/w/cpp/thread/lock_guard
 *
 * lock_guard
 * The class is a mutex wrapper that provides a convenient RAII-style mechanism
 * for owning a mutex for the duration of a scoped block
 *
 * When a lock_guard object is created, it attempts to take ownership of the mutex
 * it is given. When control leaves the scope, the lock_guard is destructed and
 * the mutex is released
 *
 * The lock_guard class is non-copyable
 */

#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

int g_i = 0;
mutex g_i_mutex;

void safe_increment(unsigned int x)
{
   for (unsigned int i = 0; i < x; i++)
   {
      lock_guard<mutex> guard(g_i_mutex);
      g_i++;
   }
}

int main(int argc, char** argv)
{
   cout << __func__ << ": " << g_i << endl;

   thread t1(safe_increment, 10000);
   thread t2(safe_increment, 10000);

   t1.join();
   t2.join();

   cout << __func__ << ": " << g_i << endl;
   return 0;
}



