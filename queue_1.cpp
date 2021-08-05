#include<iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

using namespace std;

template<typename E>
class blocking_queue
{
private:
    int max_size;
    queue<E> qu;
public:
    blocking_queue(int size):max_size(size)
    {
    }
    void push(E e)
    {
      cout<<"Push\n";
      qu.push(e);
    }

    E front()
    {
      cout<<"Front\n";
    }

    void pop()
    {
      cout<<"Pop\n";
      qu.pop();
    }

};

int main()
{
   blocking_queue<int> queue(1);
   thread t1(&blocking_queue<int>::push,& queue, 7); //interesting syntax
   thread t2(&blocking_queue<int>::pop,& queue);

   t1.join();
   t2.join();

  return 0;
}
