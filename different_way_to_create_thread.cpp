#include<iostream>
#include<thread>
using namespace std;

void fun(int x )
{
    while( x-- > 0)
    {
        cout<<x<<endl;
    }
}
class Base
{
    public:
    static void run_static(int x)
    {
        while(x-- > 0)
        {
            cout<<x<<endl;
        }
    }
    void run(int x){
        while(x-- > 0)
        {
            cout<<x<<endl;
        }
    }
    void operator()(int x)
    {
        while(x-- > 0)
        {
            cout<<x<<endl;
        }
    }
};
int main(){
    // using function pointers
    std::thread t1(fun, 11);

    // using lambda function
    auto fun = [](int x){
        while(x-- > 0){
            cout<<x<<endl;
        }
    };
    // lambda
    std::thread t2(fun, 10);
    // functor
    std::thread t3(Base(), 10);
    Base b;
    // non static member function
    std::thread t4(&Base::run, &b, 10);

    // static member funciton
    std::thread t5(&Base::run_static, 10);
    
    t1.join();
    t3.join();
    t2.join();
    t4.join();
    t5.join();


    return 0;
}