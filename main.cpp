#include "DisVar.h"

int main() {
DisVar x{0}, y{0},z{0};

cout<<sizeof(x)<<endl;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    DisVar test("Hahaalmaolmao");
    DisVar test1("lmao");
    for (int c = 0; c < 10000000; c++) {
        x = y+z;
    }
    cout<<x.value()<<endl;
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span1 = duration_cast<duration<double>>(t2 - t1);
    std::cout << time_span1.count() << endl;

    t1 = high_resolution_clock::now();
    int a,b,d;
    b=0;
    d=0;
    for (int c = 0; c < 10000000; c++) {
        a=b+d;
    }
    cout<<a<<endl;
    t2 = high_resolution_clock::now();
    duration<double> time_span2 = duration_cast<duration<double>>(t2 - t1);
    std::cout << time_span2.count() << endl;

    return 0;
}
