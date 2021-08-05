#include<iostream>
#include<chrono>
#include<future>

using namespace std;

void work(int i)
{
   for(int i =0;i<5;i++)
   {
     cout<<"Running "<< i << endl;
     this_thread::sleep_for(chrono::seconds(1));
   }
}
int main()
{
  // launch has 2 options
  // any means async or defered
  // async means you can get future
  // deferred means thread not launched untill you call get from future.
  future<void> f1 = async(launch::deferred, work, 0);
  f1.get(); // if you comment this async doednot work
  
  return 0;
}

