/*
 * http://thispointer.com/c11-multithreading-part-6-need-of-event-handling/
 */

#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

class Application {
   public:
      Application(): m_data_loaded(false) {}
      void load_data() {
         // Make this thread sleep for 1 second
         this_thread::sleep_for(chrono::milliseconds(1000));
         cout << "Loading data from XML" << endl;
         lock_guard<mutex> guard(m_mutex);
         m_data_loaded = true;
      }
      void mainTask() {
         cout << "Do some handshaking" << endl;

         while (true) {
            // BUSY waiting
            lock_guard<mutex> guard(m_mutex);
            if (m_data_loaded == true)
               break;
            else
               this_thread::sleep_for(chrono::milliseconds(100));
         }

         cout << "Do processing on loaded data" << endl;
      }
   private:
      bool m_data_loaded;
      mutex m_mutex;
};

int main(int argc, char** argv) {
   Application app;
   thread thread1(&Application::mainTask, &app);
   thread thread2(&Application::load_data, &app);

   thread1.join();
   thread2.join();
   return 0;
}

