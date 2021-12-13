/*

unique lock in cpp std::unique_lock<mutex> lock(m1))

NOTES
1. The class unique_lock is a mutex ownersip wrapper.
2. It allows
    a. can have different locking strategies.
    b. time-constrained atttempts at locking (try_lock_for, try_lock_until)
    c. recursive locking
    d. transfer of lock ownership (move not empty)
    e. condition variables

Locking Strategies      EFFECTS
    1. defer_lock       do not acquire ownership of the mutex
    2. try_to_lock      try to acquire ownership of teh mutex without blocking
    3. adopt_lock       assume the calling thread already has ownership of the mutex
*/

#include<iostream>
#include<thread>
#include<mutex>

using namespace std;
std::mutex m;

int myAmount = 0;
std::mutex(m1);
void addMoney(const char* threadNumber, int loopFor)
{
    // std::unique_lock<mutex> l(m1);// this is normal
    std::unique_lock<mutex> l(m1, std::defer_lock);//
    l.lock();// we dont need to unlock this. it will unlock when it goes out of scope
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
