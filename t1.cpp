#include<iostream>
#include<thread>
#include <chrono>
void work()
{
   std::this_thread::sleep_for(std::chrono::milliseconds(500));
   for(int i=0;i<10;i++)
     std::cout<<"Loop "<<i<<std::endl;
}

int main()
{
  std::thread t1(work);
  std::thread t2(work);
  t1.join();
  t2.join();
  return 0;
}
