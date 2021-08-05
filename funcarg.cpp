#include<iostream>
#include<thread>
#include<atomic>
#include <chrono>
#include <mutex>
//pass pointer to func to threads.
//pass by value std::thread t1(work, count, mtx);
//pass by reference do std::ref on the variable
// std::ref calla a reference wrapper
void work(int &count, std::mutex &mtx)
{
for(int i =0; i<1E6; i++)
                 {
                    mtx.lock();
                    ++count;
                    mtx.unlock();
                 }

}

int main()
{
  std::mutex mtx;
  int count = 0;
  std::thread t1(work, std::ref(count), std::ref(mtx));
  std::thread t2(work, std::ref(count), std::ref(mtx));
  t1.join();
  t2.join();

  std::cout<<"Count = "<<count<<std::endl;
  return 0;
}
