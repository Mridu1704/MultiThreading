#include<iostream>
#include<thread>
#include<atomic>
#include <chrono>
#include <mutex>
// Read mutex.cpp
// lock_guard vs unique_lock
// unique_lock has bunch of extra methods
// it allows you to to unlock the lock
// also try_lock
// simple situation lock_guard
// unique_lock when you need to call unlock
void work(int &count, std::mutex &mtx)
{
for(int i =0; i<1E6; i++)
                 {
                    std::unique_lock<std::mutex> guard(mtx); // acquire lock if possible else wait
                    ++count;
                 }// resource lock after guard goes out of scope

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
