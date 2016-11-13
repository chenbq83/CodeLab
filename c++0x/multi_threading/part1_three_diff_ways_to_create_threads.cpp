/*
 * http://thispointer.com/c-11-multithreading-part-1-three-different-ways-to-create-threads/
 *
 * Orginal C++ standard supported only single thread programming
 * In C++11 (C++0x) a new thread library is introduced
 * We can create additional threads by creating object of std::thread class
 * Each of the std::thread objet can be associated with a thread
 *
 * We can attach a callback with the std::thread object, 
 * that will be executed when this new thread starts. These callbacks can be:
 *    1. Function Pointer
 *    2. Function Objects
 *    3. Lambda Functions
 * std::thread theObj(<Callback>);
 */

#include <iostream>
#include <thread>

using namespace std;

/*
 * 1. Creating a thread using Function Pointer
 */

void thread_function() {
   for (int i = 0; i < 10000; i++);
   cout << "Thread function " << this_thread::get_id() << " executing" << endl;
}

/*
 * 2. Creating a thread using Function Objects
 */

class DisplayThread {
   public:
      void operator()() {
         for (int i = 0; i < 10000; i++);
         cout << "Display thread " << this_thread::get_id() << " executing" << endl;
      }
};

/*
 * 3. Creating a thread using Lambda Functions
 * Refer to the main thread
 */

int main(int argc, char** argv) {

   thread thread_object1(thread_function);
   for (int i = 0; i < 10000; i++);

   thread thread_object2((DisplayThread()));
   for (int i = 0; i < 10000; i++);

   thread thread_object3([]() -> void {
         for (int i = 0; i < 10000; i++);
         cout << "Lambda function " << this_thread::get_id() << " executing" << endl;
         });
   cout << "Display from main thread" << endl;

   thread thread_object4(thread_function);
   cout << "From main thread :: ID of thread 1 = " << thread_object1.get_id() << endl;
   cout << "From main thread :: ID of thread 4 = " << thread_object4.get_id() << endl;
   if (thread_object1.get_id() != thread_object2.get_id())
      cout << "Both threads have different IDs" << endl;

   thread_object1.join();
   thread_object2.join();
   thread_object3.join();
   thread_object4.join();
   cout << "Exit of main thread" << endl;
   return 0;
}
