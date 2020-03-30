#include "DisVar.h"
#include <iostream>
#include <chrono>
using namespace chrono;
int main() {
    DisVar x{3}, y{2},z{5}, h{"asfgewsdc"};
    auto c=3/2;
    x/=y;
    cout<<h.length()<<endl;
   // cout<<y.value()<<endl;
    cout<<x<<endl;
    cin>>x;
    cout<<x<<endl;
    if(z>x){
        cout<<"hello";
    }
/*
    cout<<sizeof(z)<<endl;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    for (int c = 0; c < 10000000; c++) {
        x = y+z;
    }
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span1 = duration_cast<duration<double>>(t2 - t1);
    std::cout << time_span1.count() << endl;
    cout<<x.value()<<endl;

    t1 = high_resolution_clock::now();
    int a = 0,b = 0,d = 0;
    for (int c = 0; c < 10000000; c++) {
        a=b+d;
    }
    t2 = high_resolution_clock::now();
    duration<double> time_span2 = duration_cast<duration<double>>(t2 - t1);
    cout<<a<<endl;
    std::cout << time_span2.count() << endl;
    std::cout << time_span1.count()/time_span2.count() << endl;

*/
    return 0;
}
