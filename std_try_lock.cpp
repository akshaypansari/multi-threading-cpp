// std::try_lock() tries to lock the lockable objects passed in it one by one in given order
//SYNTAX : std::try_lock(m1, m2, m3,m4, .... , mn)
// On success it returns -1 otherwise it will return 0-based mutex index number which it could not lock
// if it fails to lock any of the mutex then it will release all the mutex it locked before
// if a call fails to try_lock, results is an exception, unlock is called for any locked object before rethrowing
// the actual use of try_lock results is to lock multiple mutex objects at the same time

#include<iostream>
#include<thread>
#include<mutex>

using namespace std;
std::mutex m1, m2;
int X = 0, Y = 0;

void incrementXY(int& XY, std::mutex& m, const char* varName)
{
    for(int i = 0; i<5; i++)
    {
        m.lock();
            XY+=1;
        cout<<varName<< XY<<endl;
        m.unlock();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
void consumer()
{
    int count = 5;
    int XplusY = 0;
    while(1)
    {
        int try_lock = std::try_lock(m1, m2);

        if(try_lock == -1)
        {
            if(X!=0 && Y!=0)
            {
                count--;
                XplusY += (X+Y);
                X = 0;
                Y = 0;
                cout<<"total consumption = "<< XplusY<<endl;
            }
        
            m1.unlock();
            m2.unlock();
            if(count == 0) break;
        }
    }

}
int main()
{
    std::thread t1(incrementXY, std::ref(X), std::ref(m1), "X ");
    std::thread t2(incrementXY, std::ref(Y), std::ref(m2), "Y ");
    std::thread t3(consumer);

    t1.join();
    t2.join();
    t3.join();
    return 0;

}