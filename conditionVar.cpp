#include <iostream>
#include <thread>
#include <chrono>
#include<condition_variable>

using namespace std;

#define SYNC 1 

int main()
{
  condition_variable cond; // works with mutex
  mutex mut;

  int count = 0 ;
  int read_count;
  std::cout<<"Count = "<<count<<std::endl;
  std::cout<<"read_Count = "<<read_count<<std::endl;
  const int iter = 1E6;
  bool ready = false;
  std::thread t1([&](){
#if SYNC==1
                 unique_lock<mutex> lock1(mut);
#endif
                 for(int i =0; i<iter; i++)
                 {
                 ++count;
                 }
#if SYNC==1
                 ready = true;
                 lock1.unlock();
                 cond.notify_one();
#endif
                });

  std::thread t2([&](){
#if SYNC==1
                 unique_lock<mutex> lock1(mut);
                 while(!ready)
                    cond.wait(lock1);
                 
#endif
                 read_count = count;
                });
  t1.join();
  t2.join();
  std::cout<<"END : Count = "<<count<<std::endl;
  std::cout<<"END : read_Count = "<<read_count<<std::endl;

}
