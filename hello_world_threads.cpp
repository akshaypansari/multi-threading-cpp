#include <iostream>
#include<thread>
#include<chrono>
#include<algorithm>
using namespace std;

// using namespace std::chrono;
typedef unsigned long long ull;

ull OddSum = 0;
ull EvenSum = 0;

void findEven(ull start, ull end)
{
    for(ull i = start; i<end; i++)
    {
        if((i&1)==0)
            EvenSum+=i;
    }
}

void findOdd(ull start, ull end)
{
    for(ull i = start; i<end; i++)
    {
        if((i&1)==1)
            OddSum+=i;
    }
}

int main()
{

    ull start = 0, end = 1000000000;
    auto startTime = std::chrono::high_resolution_clock::now();

    std::thread t1(findOdd, start, end);
    std::thread t2(findEven, start, end);
    // findOdd(start, end);
    // findEven(start, end);
    t1.join();
    t2.join();
    auto stopTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stopTime-startTime);
 
    cout<<"OddSum : "<< OddSum <<endl;
    cout<<"EvenSum: "<< EvenSum << endl;

    cout<<"Sec: "<<duration.count()/1000000<<endl;
    return 0;
}