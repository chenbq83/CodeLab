/*
 * http://thispointer.com/c11-multithreading-part-7-condition-variables-explained/
 *
 * Condition Variable
 * is kind of Event used for signaling between two or more threads
 * One or more threads can wait on it to get signaled, while another thread can signal this
 * A mutex is required along with condition variable
 *
 * How things actually work with condition variable?
 *    1. Thread 1 calls the wait on condition variable, 
 *       which internally acquires the mutex and check if required condition is met or not
 *    2. If not then it release the lock and waits for condition variable to get signaled
 *       Condition variable's wait() function provides both these operations in a atomic manner
 *    3. Another thread signals the condition variable when condition is met
 *    4. Once condition variable get signaled then Thread 1 which was waiting for it resumes.
 *       It then acquires the mutex lock again and checks if the condition associated with
 *       condition variable is actually met or if it is superiors call. If more than one thread
 *       was waiting then notify_one will unblock only one thread
 *    5. If it was a superior call then it again call the wait() function
 */

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

class Application
{
   public:
      Application():m_data_loaded(false) {}
      void load_data() {
         // Make this thread sleep for 1 second
         this_thread::sleep_for(chrono::milliseconds(1000));
         cout << "Loading data from XML" << endl;

         lock_guard<mutex> guard(m_mutex);
         m_data_loaded = true;
         m_cond_var.notify_one();
      }
      void main_task() {
         cout << "Do some handshaking" << endl;
         unique_lock<mutex> lock(m_mutex);
         m_cond_var.wait(lock, [=]()->bool{ return m_data_loaded; });
         cout << "Do processing on loaded data" << endl;
      }

   private:
      bool m_data_loaded;
      mutex m_mutex;
      condition_variable m_cond_var;
};

int main(int argc, char** argv) {
   Application app;
   thread thread_1(&Application::main_task, &app);
   thread thread_2(&Application::load_data, &app);
   thread_1.join();
   thread_2.join();
   return 0;
}
