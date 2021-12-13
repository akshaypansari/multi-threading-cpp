#include<iostream>
#include<thread>
#include<condition_variable>
#include<mutex>

using namespace std;

std::mutex m;
std::condition_variable cv;
int balance = 0;

void withdraw(int money)
{
    std::unique_lock<mutex> withdrawlock(m);
    cv.wait(withdrawlock, []{return (balance!=0)? true:false;});
    if(balance>=money)
    {
        balance-=money;
        cout<<"amount deducted  "<< money<<endl;
    }
    else{
        cout<<"amount can't be deducted current balance is less than "<< money<<endl;
    }

    cout<<"current balance is "<< balance<<endl;

}

void add(int money)
{
    std::unique_lock<mutex> addlock(m);
    balance+=money;
    cout<<"Amount added current balance is "<< balance<<endl;
    cv.notify_one();
}
int main()
{
    std::thread t1(withdraw, 500);
    std::thread t2(add, 500);

    t1.join();
    t2.join();

    return 0;
}