#include<iostream>
#include<thread>

using namespace std;

void run(int x)
{
    while( x-- > 0)
    {
        cout<<x<<endl;
    }
    std::this_thread::sleep_for(std::chrono::seconds(5));
}

int main()
{
    cout<<"main_thread before"<<endl;
    std::thread t1(run,10);


    t1.join();
    // t1.join();
    cout<<"main_thread after"<<endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));

    return 0;
}