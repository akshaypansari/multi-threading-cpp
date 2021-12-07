#include<iostream>
#include<thread>
#include<mutex>

using namespace std;
std::mutex m;

int myAmount = 0;

void addMoney()
{
    m.lock();
    // ++myAmount;
    for(int i = 0; i<100000; i++)
    {
        ++myAmount;
    }
    m.unlock();
}

int main()
{
    std::thread t1(addMoney);
    std::thread t2(addMoney);

    t1.join();
    t2.join();

    cout<<myAmount<<endl;
    return 0;

}