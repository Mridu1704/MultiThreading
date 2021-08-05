#include<iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

using namespace std;
//STL queue might not be thread safe.
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

int main()
{
   blocking_queue<int> queue(5);
   thread t1([&](){
            //this_thread::sleep_for(chrono::seconds(2)); // this is to test sync behaviour comment _cv.notify in push and see
            for(int i = 0;i<10;i++) {
                printf("Size is = %d\n",queue.size());
                queue.push(i); 
                if(i == 3)
                   this_thread::sleep_for(chrono::seconds(2)); // this is to see that both threads siultaneously working
}
             });
   thread t2([&](){
            for(int i = 0;i<10;i++){
                printf("Front = %d\n",queue.front());
                queue.pop(); }
             });

   t1.join();
   t2.join();

  return 0;
}
