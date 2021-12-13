#include<iostream>
#include<mutex>
#include<thread>

using namespace std;
std::mutex mtx;

int counter = 0;
void increase1000(){
    for(int i = 0; i<100000; i++)
    {
        // while trying to lock it, if the thread does not find the variable free, it will skip and won't for the variable
        if(mtx.try_lock())
        {
            ++counter;
            mtx.unlock();
        }
    }
}

int main()
{
    std::thread t1(increase1000);
    std::thread t2(increase1000);
    t1.join();
    t2.join();

    cout<<"Value right now "<< counter<<endl;
    return 0;
}