/*
 * http://thispointer.com/c11-multithreading-part-2-joining-and-detaching-threads/
 *
 * Once a thread is started, then another thread can wait for this new thread to finish
 * For this another thread need to call join() function on the std::thread object
 *
 * std::thread thread_object(funcPtr);
 * thread_object.join()
 *
 * Detached threads are also called deamon/background threads
 * To detach a thread we need to call std::detach() function on the std::thread object
 *
 * std::thread thread_object(funcPtr);
 * thread_object.detach()
 *
 * After calling detach(), 
 * std::thread object is no longer associated with the actual thread of execution
 */

#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>

using namespace std;

class WorkerThread {
   public:
      void operator()() {
         cout << "Worker Thread " << this_thread::get_id() << " is executing" << endl;
      }
};

class ThreadRAII {
   // RAII: Resouce Acquisition Is Initialization
   public:
      ThreadRAII(thread& thread_object) : m_thread(thread_object) {}
      ~ThreadRAII() {
         // Check if thread is joinable, then detach the thread
         if (m_thread.joinable())
            m_thread.detach();
      }
   private:
      thread& m_thread;
};
int main (int argc, char** argv) {
   vector<thread> thread_list;
   for (int i = 0; i < 10; i++) {
      thread_list.push_back( thread(WorkerThread()) );
   }

   // Now wait for all the worker thread to finish
   cout << "Main thread waits for all the worker threads to finish" << endl;
   // for_each(thread_list.begin(), thread_list.end(), mem_fn(&thread::join));
   for_each(thread_list.begin(), thread_list.end(), [](thread& t)->void{t.join();});
   cout << "Exiting from main thread" << endl;

   thread thread_object((WorkerThread()));
   ThreadRAII wrapper_object(thread_object);
   return 0;
}
