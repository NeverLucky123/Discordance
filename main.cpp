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
        valSet(){};
        valSet(valSet const &var){
            if(var.Ival){
                long long int i=*var.Ival;
                Ival=make_unique<long long int>(i);
            }
            else if(var.Dval){
                long double d=*var.Dval;
                Dval=make_unique<long double>(d);
            }
            else if(var.Sval){
                string s=*var.Sval;
                Sval=make_unique<string>(s);
            }
        };
        valSet& operator=(valSet const &var){};
    }s;
    DisVar(){
        s.Ival=nullptr;
    }
    explicit DisVar(long long int a) {
        s.Ival=make_unique<long long int>(a);
    }
    explicit DisVar(long int a) {
        s.Ival=make_unique<long long int>(a);
    }
    explicit DisVar(int a) {
        s.Ival=make_unique<long long int>(a);
    }
    explicit DisVar(double a) {
        s.Dval=make_unique<long double>(a);
    }
    explicit DisVar(long double a) {
        s.Dval=make_unique<long double>(a);
    }

    explicit DisVar(string a) {
        s.Sval=make_unique<string>(a);
    }
    DisVar operator+(DisVar a){
      //  cout<<"adding"<<endl;
        char b=this->type();
        if(b!=a.type())
            return DisVar();
        else{
            if(this->s.Ival)
                return DisVar(*this->s.Ival+*a.s.Ival);
            else if(this->s.Dval)
                return DisVar(*this->s.Dval+*a.s.Dval);
            else if(this->s.Sval)
                return DisVar(*this->s.Sval+*a.s.Sval);
        }
            
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
    DisVar test=DisVar(3467865);
    DisVar test1(3467865);
    DisVar testd=DisVar(15.237896531246890);
   // DisVar tests=DisVar("string");
   // std::cout << sizeof(tests) << std::endl;


    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    DisVar x;
    for(int c=1; c<1000000; c++) {
        x=test+test1;
    }
    cout<<x.value()<<endl;
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration time_span = duration_cast<duration<double>>(t2 - t1);
    std::cout << time_span.count() << endl;

    t1 = high_resolution_clock::now();
    int *fg=new int;
    for(int c=1; c<1000000; c++) {
        *fg=3467865+3467865;
    }
    cout<<*fg<<endl;
    t2 = high_resolution_clock::now();
    time_span = duration_cast<duration<double>>(t2 - t1);
    std::cout << time_span.count() << endl;

    return 0;
}
