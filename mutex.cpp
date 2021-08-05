#include<iostream>
#include<thread>
#include<atomic>
#include <chrono>
#include <mutex>
// mutex around the critical section
// critical section -> part of memory being accesed by multiple threads
// mutex not common because if critical section throws exception mutex never unlocked
// so use unique lock and lock guard
// Due to above reason we use RAII Resource Acquisition is initialisation
// so acquire resource by initialising a variable and if it goes out of scope for any reason like exception
// then release the resource
// e.g. lock_guard
int main()
{
  std::mutex mtx;
  int count = 0;
  const int iter = 1E6;
  auto func = [&](){
                 for(int i =0; i<iter; i++)
                 {
                    mtx.lock();
                    ++count;
                    mtx.unlock();
                 }
                };
  std::thread t1(func);
  std::thread t2(func);
  t1.join();
  t2.join();

  std::cout<<"Count = "<<count<<std::endl;
  return 0;
}
