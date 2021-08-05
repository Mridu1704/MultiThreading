#include<iostream>
#include<thread>
#include<atomic>
#include <chrono>
// lambda exp -> anonymous func
// [reference to variables to be captured] (parameters) {body}
// as iter is const so it doesnot needs to be captured.
int main()
{
  // int count = 0; this is shared
  std::atomic<int> count = 0 ;// makes behavious of variable as atomic
  std::cout<<"Count = "<<count<<std::endl;
  const int iter = 1E6;
  std::thread t1([&count](){
                 for(int i =0; i<iter; i++)
                 ++count;
                });
  std::thread t2([&count](){
                 for(int i =0; i<iter; i++)
                 ++count;
                });
  t1.join();
  t2.join();

  std::cout<<"Count = "<<count<<std::endl;
  return 0;
}
