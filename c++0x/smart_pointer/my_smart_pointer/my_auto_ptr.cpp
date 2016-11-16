/*
 * http://blog.csdn.net/weiwenhp/article/details/8706864
 */

#include <iostream>

template<class T>
class My_auto_ptr
{
   private:
      T* m_ptr;
   public:
      /*
       * explicit specifies that a constructor does not allow implicite conversions
       * or copy-initialization
       */
      explicit My_auto_ptr(T* p = NULL) : m_ptr(p) {
         std::cout << "My_auto_ptr constructor" << std::endl;
      }
      My_auto_ptr(My_auto_ptr& other) {
         std::cout << "My_auto_ptr copy constructor" << std::endl;
         // this object takes the ownership from the other object
         // Not share the ownership
         m_ptr = other.m_ptr;
         other.m_ptr = NULL;
      }
      My_auto_ptr<T>& operator=(My_auto_ptr<T>& other) {
         std::cout << "My_auto_ptr operator=" << std::endl;
         if (this != &other) {
            // this object takes the ownership from the other object
            // Not share the ownership
            delete m_ptr;
            m_ptr = other.m_ptr;
            other.m_ptr = NULL;
         }
         return *this;
      }
      ~My_auto_ptr() {
         std::cout << "My_auto_ptr destructor" << std::endl;
         if (m_ptr)
            delete m_ptr;
      }
      T& operator*() {
         return *m_ptr;
      }
      T* operator->() {
         return m_ptr;
      }
};

class Data
{
   private:
      int m_i;
   public:
      Data(int i):m_i(i) {}
      int get_number() const { return m_i; }
      void set_number(int i) { m_i = i; }
};

int main(int argc, char** argv)
{
   My_auto_ptr<Data> p(new Data(42));
   std::cout << "p->get_number() = " << p->get_number() << std::endl;
   std::cout << "(*p).get_number() = " << (*p).get_number() << std::endl;

   p->set_number(43);
   std::cout << "p->get_number() = " << p->get_number() << std::endl;

   My_auto_ptr<Data> p2(new Data(78));
   p = p;
   p = p2;
   std::cout << "p->get_number() = " << p->get_number() << std::endl;

   return 0;
}

