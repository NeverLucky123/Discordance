#include <iostream>
#include <memory>
#include <any>
#include <chrono>
#include <type_traits>

using namespace std;
using namespace chrono;

class DisVar {
private:

public:
    void *val{};
    char type{};
    inline DisVar() {
        val = nullptr;
    };
    ~DisVar(){
        free(val);
    }
    template<typename t>
    inline explicit DisVar(t a) {
        val = new t(a);
        if (typeid(a) == typeid(int))
            type = 'i';
        else if (typeid(a) == typeid(double))
            type = 'd';
        else if (typeid(a) == typeid(string))
            type = 's';
    }

    inline DisVar operator+(const DisVar &a) {
        if (this->type != a.type)
            return DisVar();
        else {
            switch (this->type) {
                case 'i':
                    return DisVar(*static_cast<int*>(this->val) + *static_cast<int*>(a.val));
                case 'd':
                    return DisVar(*static_cast<double*>(this->val) + *static_cast<double*>(this->val));
                case 's':
                    return DisVar(*static_cast<string*>(this->val) + *static_cast<string*>(this->val));
                default:
                    return DisVar();
            }
        }
    }
    inline string value() {
        switch (this->type){
            case 'i':
                return to_string(*(int *)this->val);
            case 'd':
                return to_string(*(double *) this->val);
            case 's':
                return *(string *)this->val;
            default:
                return "error";
        }
    }
};

int main() {

    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    DisVar x;
    DisVar test(245678);
    DisVar test1(345675843);
    for (int c = 0; c < 10000000; c++) {
        x = test + test1;
    }
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    cout << x.value() << endl;
    duration time_span = duration_cast<duration<double>>(t2 - t1);
    std::cout << time_span.count() << endl;

    t1 = high_resolution_clock::now();
    int fg = 0;
    for (int c = 0; c < 10000000; c++) {
        fg = 345675843 + 245678;
    }
    cout << fg << endl;
    t2 = high_resolution_clock::now();
    time_span = duration_cast<duration<double>>(t2 - t1);
    std::cout << time_span.count() << endl;

    return 0;
}
