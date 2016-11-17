/*
 * http://en.cppreference.com/w/cpp/thread/unique_lock
 *
 * unique_lock
 * The class is a general-purpose mutex ownership wrapper allowing deferred
 * locking, time-constrained attempts at locking, recursive locking, transfer
 * of lock ownership, and use with condition variables
 *
 * The class is movable, but not copyable
 */

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

class Box
{
   public:
      Box(int num): num_things(num) {}
      int num_things;
      mutex m;
};

void transfer(Box& from, Box& to, int num)
{
   // do not actually take the lock yet
   // defer_lock: do not accquire ownership of the mutex
   unique_lock<mutex> lock1(from.m, defer_lock);
   unique_lock<mutex> lock2(to.m, defer_lock);

   // lock both unique_lock without deadlock
   // lock using a deadlock avoidance algorithm to avoid deadlock
   lock(lock1, lock2);

   from.num_things -= num;
   to.num_things += num;
}

int main(int argc, char** argv)
{
   Box acc1(100);
   Box acc2(50);

   cout << "Before transfer" << endl;
   cout << "Box acc1: " << acc1.num_things << endl;
   cout << "Box acc2: " << acc2.num_things << endl;

   thread t1(transfer, ref(acc1), ref(acc2), 10);
   thread t2(transfer, ref(acc2), ref(acc1), 5);

   t1.join();
   t2.join();
   
   cout << "After transfer" << endl;
   cout << "Box acc1: " << acc1.num_things << endl;
   cout << "Box acc2: " << acc2.num_things << endl;

   return 0;
}
