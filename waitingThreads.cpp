#include <iostream>
#include <thread>
#include <chrono>
#include<atomic>
using namespace std;

int main()
{
    //thread_local bool ready = false; // each thread has its own copy and main will hang.
    bool ready = false; // this works
    //atomic<bool> ready = false; // also works
    thread t1([&](){
        this_thread::sleep_for(std::chrono::seconds(3));
        ready = true;
    });
    t1.join();

    while(!ready) // this is how main can check if it can be done. inefficient way.
    {
       this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    return 0;
}
// very inefficient way for executing, we need synchronization in which one thread can tell ther thread it is done.
// thats where condition variable come in
