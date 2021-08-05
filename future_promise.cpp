#include<iostream>
#include<cmath>
#include<iomanip>
#include<thread>
#include<future>
double cal_pi(int itr)
{
  double sum = 0.0;
  for(int i =0; i< itr ; i++)
  {
    int sign = std::pow(-1,i);
    double term = 1.0/(i*2 + 1);
    sum = sum + sign * term;
  }
  return sum*4;
}

int main()
{
  std::promise<double> promise; // thread can set result in this promise
  auto do_cal = [&](int terms){
         auto result = cal_pi(terms);
         promise.set_value(result);
     };
  std::thread t1(do_cal,1E8); // pass by valuie
  std::future<double> future = promise.get_future();
  std::cout<<std::setprecision(15)<<future.get()<<std::endl;
  t1.join();
  return 0;
}
