#include <iostream>
#include <thread>
#include <chrono>
#include <condition_variable>

using namespace std;

int main()
{
    condition_variable condition;
    mutex mtx;
    bool ready = false;

    thread t1([&](){
        this_thread::sleep_for(chrono::seconds(5));
        unique_lock<mutex> lock(mtx);
        ready = true;
        lock.unlock();
        condition.notify_one();
    });

    unique_lock<mutex> lock(mtx);
    condition.wait(lock);

    cout << "ready " << ready << endl;

    t1.join();
    return 0;
}
