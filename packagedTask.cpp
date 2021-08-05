#include<iostream>
#include<cmath>
#include<thread>
#include<future>
#include <iomanip>
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
  std::packaged_task<double(int)> task1(cal_pi); //arguments later

  std::future<double> future1 = task1.get_future(); // this catched exception as well
	// can see on video in udemy

  std::thread t1(std::move(task1), 1E6); //can not copy task1 , no copy constructure, we donot need it again, so we can move

  std::cout<<std::setprecision(15) << future1.get()<<std::endl;

  t1.join();
  
  return 0;
}
