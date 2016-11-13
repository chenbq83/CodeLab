/*
 * http://thispointer.com/c11-multithreading-part-5-using-mutex-to-fix-race-conditions/
 */

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

using namespace std;

class Wallet {
   public:
      Wallet(): m_money(0) {}
      int get_money() { return m_money; }
      void add_money(int money) {
         // m_mutex.lock();
         // if we forgot to unclock the mutex at the end of function,
         // then as a result, one thread will exit without releasing the lock
         // and other threads will remain in waiting
         // To avoid such scenario, we should use std::lock_guard
         // lock_guard is a class template, which implements the RAII for mutex
         lock_guard<mutex> guard(m_mutex);
         for (int i = 0; i < money; i++) {
            m_money++;
         }
         // m_mutex.unlock();
      }
   private:
      int m_money;
      mutex m_mutex;
};

int test_multithreaded_wallet() {
   Wallet wallet_object;
   vector<thread> threads;
   for (int i = 0; i < 5; i++)
      threads.push_back(thread(&Wallet::add_money, &wallet_object, 1000));
   for (int i = 0; i < threads.size(); i++)
      threads.at(i).join();

   return wallet_object.get_money();
}

int main(int argc, char** argv) {
   int val = 0;
   for (int cnt = 0; cnt < 1000; cnt++)
      if ((val = test_multithreaded_wallet()) != 5000)
         cout << "Error at count = " << cnt << ", money in Wallet = " << val << endl;
   return 0;
}
