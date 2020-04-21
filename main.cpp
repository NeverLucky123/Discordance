#include "DisVar.h"
#include "DisVector.h"
#include <iostream>
#include <chrono>
int main() {
    using namespace std;
    using namespace chrono;
    using namespace discordance;
    discordance::array<double, 10> arr10{1,2,3,4,5,6,7,8,9,10};
    std::array<double, 10> arr11{1,2,3,4,5,6,7,8,9,10};

    discordance::vector<double> vec10{1,2,3,4,5,6,7,8,9,10};
    vec10=arr10;

    var x=0; int y=0; int z=0;
    cout<<sizeof(z)<<endl;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    for (int c = 0; c < 10000000; c++) {
        var(3);
    }
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span1 = duration_cast<duration<double>>(t2 - t1);
    std::cout << time_span1.count() << endl;

    t1 = high_resolution_clock::now();
    int a = 0,b = 10,d = 0;
    for (int c = 0; c < 10000000; c++) {
        a=b+d;
    }
    t2 = high_resolution_clock::now();
    duration<double> time_span2 = duration_cast<duration<double>>(t2 - t1);
    cout<<a<<endl;
    std::cout << time_span2.count() << endl;
    std::cout << time_span1.count()/time_span2.count() << endl;


    return 0;
}
