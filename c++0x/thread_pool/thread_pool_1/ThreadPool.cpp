#include "ThreadPool.h"
#include <iostream>
#include <algorithm>

using namespace netlib;

ThreadPool::ThreadPool(int theThreadNumber)
   :threadNumber_(theThreadNumber),
    isRunning_(false)
{
   std::cout << "ThreadPool constructor" << std::endl;
}

ThreadPool::~ThreadPool()
{
   std::cout << "ThreadPool destructor" << std::endl;
   if (isRunning_)
      stop();
}

bool ThreadPool::start(void)
{
   for (int i = 0; i < threadNumber_; i++)
      threadList_.push_back(std::thread(&ThreadPool::threadFunc, this));

   std::cout << "Thread pool begins to work" << std::endl;
   isRunning_ = true;
   return true;
}

bool ThreadPool::stop(void)
{
   if (isRunning_)
   {
      std::cout << "Thread pool begins to stop" << std::endl;
      isRunning_ = false;
      conditionEmpty_.notify_all();

      for_each(threadList_.begin(), threadList_.end(), [](std::thread& t) -> void {
            if (t.joinable())
               t.join();
            });
   }
   return true;
}

bool ThreadPool::addTask(Task task)
{
   std::cout << "Add a task to ThreadPool" << std::endl;

   std::lock_guard<std::mutex> guard(mutex_);
   taskList_.push_front(task);
   conditionEmpty_.notify_one();
   return true;
}

void ThreadPool::threadFunc(void)
{
   std::cout << "Thread " << std::this_thread::get_id() << "  begins to work" << std::endl;
   Task task = NULL;
   while (isRunning_)
   {
      {
         std::lock_guard<std::mutex> guard(mutex_);
         if (taskList_.empty())
            conditionEmpty_.wait(mutex_);

         if (!taskList_.empty())
         {
            std::cout << "Thread " << std::this_thread::get_id() << " Take one task from queue" << std::endl;
            task = taskList_.front();
            taskList_.pop_front();
         }
         else
            continue;
      }

      task();
   }
   std::cout << "Thread " << std::this_thread::get_id() << "  stops" << std::endl;
}




