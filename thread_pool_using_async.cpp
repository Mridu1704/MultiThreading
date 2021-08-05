#include<iostream>
#include<future>
#include<chrono>
#include<vector>
#include<mutex>
#include <queue>

using namespace std;

mutex _m;

template<typename E>
class blocking_queue
{
private:
    int max_size;
    queue<E> qu;
    mutex _m;
    condition_variable _cv;
public:
    blocking_queue(int size):max_size(size)
    {
    }
    void push(E e)
    {
      unique_lock<mutex> lock(_m);
      _cv.wait(lock, [this](){ return qu.size() < max_size; });
      printf("Push\n");
      qu.push(e);
      lock.unlock(); // can be skipped , need to see why ?
      _cv.notify_one(); // If this is not present then you can see hang
    }

    E front()
    {
      unique_lock<mutex> lock(_m);
      _cv.wait(lock, [&](){ return !qu.empty(); }); // this is so that we dont return front when queue empty else it will return 0, so wait untill queue empty 
      // notify is not needed  because we are not modifiying anything and unclock not needed
      return qu.front();
    }

    void pop()
    {
      unique_lock<mutex> lock(_m);
      _cv.wait(lock, [&](){ return !qu.empty(); });
      qu.pop();
      lock.unlock();
      _cv.notify_one();
    }

    int size()
    {
       // unique_lock<mutex> lock(_m);
         lock_guard<mutex> lock(_m);
         return qu.size();
    }

};


int work(int id)
{
   unique_lock<mutex> lock(_m);
   cout<<"Starting "<< id<<endl;
   lock.unlock();
   this_thread::sleep_for(chrono::seconds(6));
   return id;
}

int main()
{

  blocking_queue<shared_future<int>> vf(2); // future doesnot work see why?
  thread t1([&](){
  for(int i =0;i < 20;i++)
  {
     shared_future<int> f = async(launch::async,work,i);
     vf.push(f);
  }});

  for(int i =0;i < 20;i++)
  {
     shared_future<int> f = vf.front();
     cout<<"Future : "<<f.get()<<endl;
     vf.pop();
  }
  t1.join();
  return 0;
}
