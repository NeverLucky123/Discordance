#include "DisVar.h"
#include "DisVector.h"
#include <iostream>
#include <chrono>
int main() {


    using discordance::deque, discordance::vector;
    using namespace std;
    using namespace std::chrono;
    using namespace discordance;
    discordance::vector<double> vec11{1,2,3,4,5,6,7,8,9,10};

    deque<deque<vector<int >>> x(1,deque<vector<int >>(3,vector<int >(2)));
    x[0][0].assign(5,10);
    for (int i = 0; i < x.size(); ++i)
    {
        for (int j = 0; j < x[i].size(); ++j)
        {
            for (int k = 0; k < x[i][j].size(); ++k)
            {
               /* std::cout << "Element at x[" << i << "][" << j
                     << "][" << k << "] = " << x[i][j][k]
                     << std::endl;*/
            }
        }
    }
    auto a=vec11.slice(5,10);
    for(auto i:a){
        cout<<i<<endl;
    }
    return 0;

/*
    var x=0; var y=0; int z=0;
    cout<<sizeof(z)<<endl;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    for (int c = 0; c < 10000000; c++) {
        x=y+x;
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

*/
    return 0;
}
