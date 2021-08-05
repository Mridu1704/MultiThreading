#include<iostream>
#include<chrono>
#include<future>

using namespace std;

int work(int i)
{
   for(int i =0;i<5;i++)
   {
     //cout<<"Running "<< i << endl;
     printf("Running %d\n",i);
     this_thread::sleep_for(chrono::seconds(1));
   }
   return i*7;
}
int main()
{
  // launch has 2 options
  // any means async or defered
  // async means you can get future
  // deferred means thread not launched untill you call get from future.

  //async(launch::async, work, 0); // first this run
  //async(launch::async, work, 1); // then this run
  // this runs sync because destructor for future waits untill first call done.
  
  future<int> f1 = async(launch::async, work, 0); 
  future<int> f2 = async(launch::async, work, 1); 

  // no need to call f1.get or f2.get() if return type not there. 
  cout<<"F1 "<<f1.get()<<endl;
  cout<<"F2 "<<f2.get()<<endl;
  return 0;
}

