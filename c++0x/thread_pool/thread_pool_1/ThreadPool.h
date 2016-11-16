/*
 * http://blog.csdn.net/shreck66/article/details/50412986
 */

#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_

#include <thread>
#include <mutex>
#include <condition_variable>
#include <list>
#include <vector>
#include <memory>
#include <functional>

namespace netlib
{
   class ThreadPool
   {
      public:
         typedef std::function<void(void)> Task;
         ThreadPool(int threadNumber);
         ~ThreadPool();

         bool addTask(Task task);
         bool start(void);
         bool stop(void);
      private:
         void threadFunc(void);

         std::mutex mutex_;
         std::condition_variable_any conditionEmpty_;
         std::list<Task> taskList_;
         bool isRunning_;
         int threadNumber_;
         std::vector<std::thread> threadList_;
   };
};

#endif
