#include <iostream>
#include <memory>
#include <any>
#include <chrono>
#include <type_traits>
using namespace std;
using namespace chrono;
class DisVar1 {
private:
    void* val{};
    char type{};
public:
    inline DisVar1(){
        val=nullptr;
    };
    template <typename t>
    inline explicit DisVar1(t a) {
        val=new t(a);
        if(typeid(a)==typeid(int))
            type='i';
        else if(typeid(a)==typeid(double))
            type='d';
        else if(typeid(a)==typeid(string))
            type='s';
    }
    DisVar1 operator+(DisVar1 a){
        char b=this->type;
        if(b!=a.type)
            return DisVar1();
        else{
            switch (b){
                case 'i':
                    return DisVar1(*(int*)this->val+*(int*)(a.val));
                case 'd':
                    return DisVar1(*(double*)this->val+*(double*)(a.val));
                case 's':
                    return DisVar1(*(string*)this->val+*(string*)(a.val));
            }
        }
    }
    inline string value(){
        if(this->type=='i')
            return to_string(*(int*)this->val);
        else if(this->type=='d')
            return to_string(*(double*)this->val);
        else if(this->type=='s')
            return *(string*)this->val;
    }
};
int main() {
    //ptr class solution
    /*
    DisVar test=DisVar(3467865);
    DisVar test1(3467865);
    DisVar testd=DisVar(15.237896531246890);
    DisVar tests=DisVar("string");
    std::cout << sizeof(tests) << std::endl;
    */

    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    DisVar1 x;
    DisVar1 test(245678);
    DisVar1 test1(345675843);
    for(int c=0; c<10000000; c++) {
        x=test+test1;
    }
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    cout<<x.value()<<endl;
    duration time_span = duration_cast<duration<double>>(t2 - t1);
    std::cout << time_span.count() << endl;

    t1 = high_resolution_clock::now();
    int fg;
    for(int c=0; c<10000000; c++) {
        fg=345675843+245678;
    }
    cout<<fg<<endl;
    t2 = high_resolution_clock::now();
    time_span = duration_cast<duration<double>>(t2 - t1);
    std::cout << time_span.count() << endl;

    return 0;
}
