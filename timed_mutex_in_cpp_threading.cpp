#include<iostream>
#include<thread>
#include<mutex>

using namespace std;
// std::mutex m1, m2;
// int X = 0, Y = 0;
std::timed_mutex m;
int amount = 0;

void increment(int threadNum)
{
    // below is for try lock for 
   /* if(m.try_lock_for(std::chrono::seconds(std::chrono::seconds(1))))
    {
        ++amount;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        cout<<"Thread "<< threadNum << " Entered "<<endl;
        m.unlock();
    }
    else{
        cout<<"Thread "<< threadNum << " Could not enter "<<endl;
    }*/

    // below is for try lock until which is similar to above
    auto now = std::chrono::steady_clock::now();
    if(m.try_lock_until(now+std::chrono::seconds(1)))
    {
        ++amount;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        cout<<"Thread "<< threadNum << " Entered "<<endl;
        m.unlock();
    }
    else{
        cout<<"Thread "<< threadNum << " Could not enter "<<endl;
        
    }
}

int main()
{
    std::thread t1(increment, 1);
    std::thread t2(increment, 2);
    t1.join();
    t2.join();

    cout<<amount<<endl;

    return 0;

}