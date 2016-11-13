/*
 * http://thispointer.com/c11-multithreading-part-3-carefully-pass-arguments-to-threads/
 *
 * To pass arguments to thread's associated callable object or function,
 * just pass additional arguments to the std::thread constructor
 */

#include <iostream>
#include <string>
#include <thread>

using namespace std;

// Passing simple arguments to a thread
void thread_callback(int x, string str) {
   cout << "Passed number = " << x << endl;
   cout << "Passed string = " << str << endl;
}

// How not to pass arguments to threads
// Do NOT pass address of variables from local stack to thread's callback function
// Because it might be possible the local variable in Thread 1 goes OUT OF SCOPE
// but Thread 2 is still trying to access it throught it's address.
void new_thread_callback(int* p) {
   cout << "Inside thread: p = " << *p << endl;
   chrono::milliseconds dura(1000);
   this_thread::sleep_for(dura);
   cout << "Inside thread: p = " << *p << endl;
   *p =19;
}

void start_new_thread() {
   int i = 10;
   cout << "Inside main thread: i = " << i << endl;
   thread t(new_thread_callback, &i);
   t.detach();
   cout << "Inside main thread: i = " << i << endl;
}

// Similarly, be careful while passing pointer to memory located on heap to thread
// It might be possible that some thread deletes it before new thread tries to access it

void start_new_thread2() {
   int* p = new int();
   *p = 10;
   cout << "Inside main thread: *p = " << *p << endl;
   thread t(new_thread_callback, p);
   t.detach();
   delete p;
   p = new int();
   *p = 11;
   delete p;
   p = NULL;
}

// How to pass reference to thread
// As arguments are copied to new thread stack, so if you need to pass references in common way

void thread_callback2(const int& x) {
   // Even if thread_callback2 accepts arguments as reference
   // but still changes done it are not visible outside the thread
   // It is because x in the thread function thread_callback2 is reference to the temp value
   // copied at the new thread's stack
   int& y = const_cast<int&>(x);
   y++;
   cout << "Inside thread_callback2: x = " << x << endl;
}

// Using std::ref()
void thread_callback3(const int& x) {
   int& y = const_cast<int&>(x);
   y++;
   cout << "Inside thread_callback3: x = " << x << endl;
}

// Assign pointer to member function of a class as thread function
class DummyClass {
   public:
      DummyClass() {}
      DummyClass(const DummyClass& obj) {}
      ~DummyClass() {}
      void sampleMemberFunction(int x) {
         cout << "Inside DummyClass::sampleMemberFunction x = " << x << endl;
      }
};

int main(int argc, char** argv) {
   cout << "=================================================" << endl;
   int x = 10;
   string str = "Sample string";
   thread thread_object(thread_callback, x, str);
   thread_object.join();

   cout << "=================================================" << endl;
   start_new_thread();
   chrono::milliseconds dura(2000);
   this_thread::sleep_for(dura);

   cout << "=================================================" << endl;
   start_new_thread2();
   this_thread::sleep_for(dura);

   cout << "=================================================" << endl;
   x = 9;
   cout << "In main thread: Before thread start x = " << x << endl;
   thread thread_object2(thread_callback2, x);
   thread_object2.join();
   cout << "In main thread: After thread joins x = " << x << endl;

   cout << "=================================================" << endl;
   x = 12;
   cout << "In main thread: Before thread start x = " << x << endl;
   thread thread_object3(thread_callback3, ref(x));
   thread_object3.join();
   cout << "In main thread: After thread joins x = " << x << endl;

   cout << "=================================================" << endl;
   DummyClass dummy_object;
   x = 15;
   thread thread_object4(&DummyClass::sampleMemberFunction, &dummy_object, x);
   thread_object4.join();
   cout << "=================================================" << endl;
   return 0;
}
