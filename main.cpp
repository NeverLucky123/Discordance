#include "DisVar.h"

int main() {
DisVar x{1}, y{5.45678},z{2};
x=y+z;
cout<<x.value()<<endl;
/*
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    DisVar test("Hahaalmaolmao");
    DisVar test1("lmao");
    for (int c = 0; c < 10000000; c++) {
        x = y+z;
    }
    //cout<<x.value()<<endl;
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span1 = duration_cast<duration<double>>(t2 - t1);
    std::cout << time_span1.count() << endl;
    cout << x.value() << endl;

    t1 = high_resolution_clock::now();

    for (int c = 0; c < 10000000; c++) {
       int x=0+0;
    }
    t2 = high_resolution_clock::now();
    duration<double> time_span2 = duration_cast<duration<double>>(t2 - t1);
    std::cout << time_span2.count() << endl;
*/
    return 0;
}
