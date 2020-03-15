#include <iostream>
#include <memory>
#include <any>
#include <chrono>
using namespace std;
using namespace chrono;
class DisVar {
public:
    union valSet{
        unique_ptr<long long int> Ival;
        unique_ptr<long double> Dval;
        unique_ptr<string> Sval;
        ~valSet(){};
        valSet() {};
    }s;
    DisVar(){}
    DisVar(long long int a) {
        s.Ival=make_unique<long long int>(a);
    }
    DisVar(long int a) {
        s.Ival=make_unique<long long int>(a);
    }
    DisVar(int a) {
        s.Ival=make_unique<long long int>(a);
    }
    DisVar(double a) {
        s.Dval=make_unique<long double>(a);
    }
    DisVar(long double a) {
        s.Dval=make_unique<long double>(a);
    }

    DisVar(string a) {
        s.Sval=make_unique<string>(a);
    }
    DisVar operator+(DisVar& a){
        char b=this->type();
        if(b!=a.type())
            return DisVar();
        else if(this->type())
            
    }
    char type(){
        if(s.Ival)
            return 'i';
        else if(s.Dval)
            return 'd';
        else if(s.Sval)
            return 's';
    }
    string value(){
        char b=this->type();
        if(b=='i')
            return to_string(*this->s.Ival);
        if(b=='d')
            return to_string(*this->s.Dval);
        if(b=='s')
            return *this->s.Sval;
    }

};
string value(DisVar &a){
    char b=a.type();
    if(b=='i')
        return to_string(*a.s.Ival);
    if(b=='d')
        return to_string(*a.s.Dval);
    if(b=='s')
        return *a.s.Sval;
}

int main() {
    //ptr class solution
    DisVar test=DisVar(16776879874578655);
    DisVar testd=DisVar(15.237896531246890);
    DisVar tests=DisVar("string");
    std::cout << sizeof(tests) << std::endl;

    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    int d;
    string e;
    double s;
    for(int c=1; c<1000000; c++) {
        if(test.s.Ival)
            d=*test.s.Ival;
        else if(test.s.Dval)
            s=*test.s.Dval;
        else if(test.s.Sval)
            e=*test.s.Sval;
    }
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration time_span = duration_cast<duration<double>>(t2 - t1);
    std::cout << time_span.count() << endl;

    t1 = high_resolution_clock::now();
    long long int fg;
    for(int c=1; c<1000000; c++) {
        fg=16776879874578655;
    }
    cout<<fg<<endl;
    t2 = high_resolution_clock::now();
    time_span = duration_cast<duration<double>>(t2 - t1);
    std::cout << time_span.count() << endl;

    return 0;
}
