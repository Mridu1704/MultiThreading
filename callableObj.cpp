#include<iostream>
#include<thread>
#include<atomic>
#include <chrono>
#include <mutex>
// Callable obj is object of a class that overloads the call operator.
// not argument create member funct
class App
{
private:
 int count = 0;
 std::mutex mtx;
public:
  void operator()()
  {
                 for(int i =0; i<1E6; i++)
                 {
                    const std::lock_guard guard(mtx); // acquire lock if possible else wait
                    ++count;
                 }// resource lock after guard goes out of scope
  }
  int getCount()
  {
    return count;
  }
};

int main()
{
  App app;
  app();
  std::thread t1(std::ref(app));
  std::thread t2(std::ref(app));
  t1.join();
  t2.join();

  std::cout<<"Count = "<<app.getCount()<<std::endl;
  return 0;
}
