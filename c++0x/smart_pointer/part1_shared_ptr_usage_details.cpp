/*
 * http://thispointer.com/learning-shared_ptr-part-1-usage-details/
 *
 * shared_ptr
 * is kind of Smart Pointer that is smart enough to automatically delete the associated pointer
 * when it is not used anywhere
 * Thus helps us to completely remove the problem of memory leaks and dangling pointers.
 * It follows the concept of Shared Ownership i.e. different shared_ptr objects can be associated
 * with same pointer and internally uses the reference counting mechanism to achieve this.
 * 
 * Each shared_ptr object internally points to two memory locations:
 *    1. pointer to the object
 *    2. pointer to control data that is used for reference counting
 */

#include <iostream>
#include <memory>

using namespace std;

int main (int argc, char** argv) {
   shared_ptr<int> p1(new int());
   *p1 = 42;
   cout << "p1 = " << *p1 << endl;

   // Shows the ref count
   cout << "p1 reference count = " << p1.use_count() << endl;

   // Second shared_ptr object will also point to the same pointer internally
   // It will make the ref count to 2
   shared_ptr<int> p2(p1);
   cout << "p1 reference count = " << p1.use_count() << endl;
   cout << "p2 reference count = " << p2.use_count() << endl;

   if (p1 == p2)
      cout << "p1 and p2 are pointing to same pointer " << endl;

   // Reset the shared_ptr, in this case, it will not point to any pointer
   p1.reset();
   cout << "p1 reset" << endl;
   cout << "p1 reference count = " << p1.use_count() << endl;
   cout << "p2 reference count = " << p2.use_count() << endl;

   p1.reset(new int(11));
   cout << "p1 reset to new int" << endl;
   cout << "p1 reference count = " << p1.use_count() << endl;
   cout << "p2 reference count = " << p2.use_count() << endl;

   p1 = nullptr;
   cout << "p1 set to nullptr" << endl;
   cout << "p1 reference count = " << p1.use_count() << endl;

   if (!p1)
      cout << "p1 is NULL" << endl;

   return 0;
}
