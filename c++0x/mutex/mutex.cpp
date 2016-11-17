/*
 * http://en.cppreference.com/w/cpp/thread/mutex
 *
 * std::mutex
 * The mutex class is a synchronization privitive that can be used
 * to protect shared data from being simultaneously accessed by mutiple threads
 *
 * mutex offers exclusive, non-recursive ownership semantics
 *
 * The behavior of a program is undefined if a mutex is destroyed while still owned
 * by any threads, or a thread terminates while owing a mutex.
 *
 * mutex is neither copyable nor movable
 */

#include <iostream>
#include <map>
#include <mutex>
#include <chrono>
#include <string>
#include <thread>

using namespace std;

map<string, string> g_pages;
mutex g_pages_mutex;

void save_page(const string& url)
{
   // simulate a long page fetch
   this_thread::sleep_for(chrono::seconds(2));
   string result = "fake content";

   // mutex is usually not accessed directly
   // unique_lock and lock_guard are used to manage locking in a exception-safe manner
   lock_guard<mutex> guard(g_pages_mutex);
   g_pages[url] = result;

   return;
}
int main(int argc, char** argv)
{
   thread t1(save_page, "http://foo");
   thread t2(save_page, "http://bar");

   t1.join();
   t2.join();

   // safe to access g_pages without lock now, as the threads are joined
   for (const auto& pair : g_pages) {
      cout << pair.first << " => " << pair.second << endl;
   }
}
