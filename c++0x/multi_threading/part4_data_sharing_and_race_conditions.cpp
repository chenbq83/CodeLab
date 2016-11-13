/*
 * http://thispointer.com/c11-multithreading-part-4-data-sharing-and-race-conditions/
 */

#include <iostream>
#include <thread>
#include <vector>

using namespace std;

// Example of race condition
class Wallet {
   public:
      Wallet() : m_meney(0) {}
      int get_money() { return m_meney; }
      void add_money(int money) {
         for (int i = 0; i < money; ++i)
            m_meney++;
      }
   private:
      int m_meney;
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
   for (int k = 0; k < 1000; k++) {
      if ((val = test_multithreaded_wallet()) != 5000)
         cout << "Error at count = " << k << ", money in Wallet = " << val << endl;
   }
   return 0;
}
