#include <iostream>
#include <memory>

using namespace std;

class DisVar {
public:
    unique_ptr<int> Ival;
    unique_ptr<double> Dval;
    unique_ptr<string> Sval;
    explicit DisVar(int a) {
        Ival=make_unique<int>(a);
    }

    explicit DisVar(double a) {
        Dval=make_unique<double>(a);
    }

    explicit DisVar(string a) {
        Sval=make_unique<string>(a);
    }
    auto operator+(const DisVar& a){

    }
    const char * type(){
        if(Ival)
            return typeid(*Ival).name();
        else if(Dval)
            return typeid(*Dval).name();
        else if(Sval)
            return typeid(*Sval).name();
    }
};

int main() {
    DisVar test=DisVar(15);
    DisVar testd=DisVar(15.237896531246890);
    DisVar tests=DisVar("string");
    std::cout << test.type() << std::endl;
    return 0;
}
