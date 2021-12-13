#include<iostream>
#include<thread>
#include<mutex>

using namespace std;
std::mutex m;

int myAmount = 0;
std::mutex(m1);
void addMoney(const char* threadNumber, int loopFor)
{
    std::lock_guard<mutex> l(m1);
    // ++myAmount;
    for(int i = 0; i<loopFor; i++)
    {
        ++myAmount;
        cout<< threadNumber << myAmount<<endl;
    }
}

int main()
{
    std::thread t1(addMoney, "T1: ", 5);
    std::thread t2(addMoney, "T2: ", 5);

    t1.join();
    t2.join();

    cout<<myAmount<<endl;
    return 0;

}