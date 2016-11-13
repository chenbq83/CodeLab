/*
 * http://thispointer.com/c11-multithreading-part-8-stdfuture-stdpromise-and-returning-values-from-thread/
 *
 * We want a thread to return a result
 *
 *    1. Old way: Share data among threads using pointer
 *       Pass a pointer to the new thread and this thread will set the data in it.
 *       Till then in main thread keep on waiting using a condition variable.
 *       When new thread sets the data and signal the condition variable, 
 *       then main thread will wake up and fetch data from the pointer.
 *
 *    2. C++11 way: Using std::future and std::promise
 *       std::future is a class template and its object stores the future value
 *       Actually a std::future object internally stores a value that will be assigned
 *       in future and it also provides a mechanism to access that value.
 *       But if somebody tries to access this associated value of future through get()
 *       function before it is available, then get() function will be block 
 *       till value is available.
 *
 *       std::promise is also a class template and its object promises to set the value
 *       in future.
 */

#include <iostream>
#include <thread>
#include <future>
#include <string>

using namespace std;

void initiazer(promise<int>* promObj) {
   cout << "Inside thread" << endl;
   promObj->set_value(35);
}

void thread_callback(promise<int>* prom_obj1, promise<string>* prom_obj2) {
   cout << "Inside thread_callback" << endl;
   this_thread::sleep_for(chrono::milliseconds(500));
   prom_obj1->set_value(42);

   this_thread::sleep_for(chrono::milliseconds(500));
   prom_obj2->set_value("Nobody");
}

int main(int argc, char** argv) {
   // Create a std::promise object
   // The promise object does NOT have any associated value
   // But it gives a promise that somebody will surely set the value in it
   // And once it's set then you can get the value through associated std::future object
   promise<int> promise_obj;

   // How main thread can know that when thread_1 is going to set the value
   // in this promise object?
   // Every std::promise object has an associated std::future object
   // through which others can fetch the value set by promise
   future<int> future_obj = promise_obj.get_future();
   thread thread_1(initiazer, &promise_obj);
   // Fetch the value set by thread_1 in std::promise through get() function
   // If value is not yet set by thread_1, then this call will get blocked
   cout << future_obj.get() << endl;
   thread_1.join();

   promise<int> promise_obj1;
   future<int> future_obj1 = promise_obj1.get_future();

   promise<string> promise_obj2;
   future<string> future_obj2 = promise_obj2.get_future();

   thread thread_2(thread_callback, &promise_obj1, &promise_obj2);

   cout << future_obj1.get() << endl;
   cout << future_obj2.get() << endl;
   thread_2.join();

   return 0;
}
