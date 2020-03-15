#include <iostream>
#include <memory>

using namespace std;

class DisVar {
public:
    unique_ptr<long long int> Ival;
    unique_ptr<long double> Dval;
    unique_ptr<string> Sval;
    DisVar(long long int a) {
        Ival=make_unique<long long int>(a);
    }
    DisVar(long int a) {
        Ival=make_unique<long long int>(a);
    }
    DisVar(int a) {
        Ival=make_unique<long long int>(a);
    }
    DisVar(double a) {
        Dval=make_unique<long double>(a);
    }
    DisVar(long double a) {
        Dval=make_unique<long double>(a);
    }

    DisVar(string a) {
        Sval=make_unique<string>(a);
    }
    auto operator+(const DisVar& a){

    }
    char type(){
        if(Ival)
            return 'i';
        else if(Dval)
            return 'd';
        else if(Sval)
            return 's';
    }
    string value(){
        char b=this->type();
        if(b=='i')
            return to_string(*this->Ival);
        if(b=='d')
            return to_string(*this->Dval);
        if(b=='s')
            return *this->Sval;
    }
};
string value(DisVar &a){
    char b=a.type();
    if(b=='i')
        return to_string(*a.Ival);
    if(b=='d')
        return to_string(*a.Dval);
    if(b=='s')
        return *a.Sval;
}
int main() {
    DisVar test=DisVar(16776879874578655);
    DisVar testd=DisVar(15.237896531246890);
    DisVar tests=DisVar("string");
    std::cout << sizeof(tests) << std::endl;
    std::cout << test.value() << std::endl;
    std::cout << value(testd) << std::endl;
    std::cout << value(tests) << std::endl;


    return 0;
}
