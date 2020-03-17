#include <iostream>
#include <memory>
#include <chrono>
#include <utility>
#include <string_view>

using namespace std;
using namespace chrono;

class DisVar {
private:
public:
    void *val{};
    enum type {
        Integer = 0, Long = 1, LL = 2, Double = 3, LD = 4, String
    } Type{};

    inline DisVar() = default;

    ~DisVar() {
        free(val);
    }

    inline explicit DisVar(int a) {
        val = new int(a);
        Type = type::Integer;
    }

    inline explicit DisVar(long a) {
        val = new long(a);
        Type = type::Long;
    }

    inline explicit DisVar(long long a) {
        val = new long long(a);
        Type = type::LL;
    }

    inline explicit DisVar(long double a) {
        val = new long double(a);
        Type = type::LD;
    }

    inline explicit DisVar(double a) {
        val = new double(a);
        Type = type::Double;
    }

    inline explicit DisVar(string a) {
        val = new string(std::move(a));
        Type = type::String;
    }

    DisVar &operator+(const DisVar &a) const {
        switch (this->Type) {
            case Integer:
                switch (a.Type) {
                    case Integer:
                        return *new DisVar(*reinterpret_cast<int *>(this->val) + *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(*reinterpret_cast<int *>(this->val) + *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(*reinterpret_cast<int *>(this->val) + *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(*reinterpret_cast<int *>(this->val) + *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<int *>(this->val) + *reinterpret_cast<long double *>(a.val));
                    case String:
                        return *new DisVar();
                }
            case Long:
                switch (a.Type) {
                    case Integer:
                        return *new DisVar(*reinterpret_cast<long *>(this->val) + *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(*reinterpret_cast<long *>(this->val) + *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<long *>(this->val) + *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(*reinterpret_cast<long *>(this->val) + *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<long *>(this->val) + *reinterpret_cast<long double *>(a.val));
                    case String:
                        return *new DisVar();
                }
            case LL:
                switch (a.Type) {
                    case Integer:
                        return *new DisVar(*reinterpret_cast<long long *>(this->val) + *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) + *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) + *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) + *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) + *reinterpret_cast<long double *>(a.val));
                    case String:
                        return *new DisVar();
                }
            case Double:
                switch (a.Type) {
                    case Integer:
                        return *new DisVar(*reinterpret_cast<double *>(this->val) + *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(*reinterpret_cast<double *>(this->val) + *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<double *>(this->val) + *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(*reinterpret_cast<double *>(this->val) + *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<double *>(this->val) + *reinterpret_cast<long double *>(a.val));
                    case String:
                        return *new DisVar();
                }
            case LD:
                switch (a.Type) {
                    case Integer:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) + *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) + *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) + *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) + *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) + *reinterpret_cast<long double *>(a.val));
                    case String:
                        return *new DisVar();
                }
            case String:
                switch (a.Type) {
                    case String:
                        return *new DisVar(*reinterpret_cast<string *>(this->val) + *reinterpret_cast<string *>(a.val));
                    default:
                        return *new DisVar();
                }
        }
    }

    DisVar &operator-(const DisVar &a) const {
        switch (this->Type) {
            case Integer:
                switch (a.Type) {
                    case Integer:
                        return *new DisVar(*reinterpret_cast<int *>(this->val) - *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(*reinterpret_cast<int *>(this->val) - *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(*reinterpret_cast<int *>(this->val) - *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(*reinterpret_cast<int *>(this->val) - *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<int *>(this->val) - *reinterpret_cast<long double *>(a.val));
                    case String:
                        return *new DisVar();
                }
            case Long:
                switch (a.Type) {
                    case Integer:
                        return *new DisVar(*reinterpret_cast<long *>(this->val) - *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(*reinterpret_cast<long *>(this->val) - *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<long *>(this->val) - *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(*reinterpret_cast<long *>(this->val) - *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<long *>(this->val) - *reinterpret_cast<long double *>(a.val));
                    case String:
                        return *new DisVar();
                }
            case LL:
                switch (a.Type) {
                    case Integer:
                        return *new DisVar(*reinterpret_cast<long long *>(this->val) - *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) - *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) - *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) - *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) - *reinterpret_cast<long double *>(a.val));
                    case String:
                        return *new DisVar();
                }
            case Double:
                switch (a.Type) {
                    case Integer:
                        return *new DisVar(*reinterpret_cast<double *>(this->val) - *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(*reinterpret_cast<double *>(this->val) - *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<double *>(this->val) - *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(*reinterpret_cast<double *>(this->val) - *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<double *>(this->val) - *reinterpret_cast<long double *>(a.val));
                    case String:
                        return *new DisVar();
                }
            case LD:
                switch (a.Type) {
                    case Integer:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) - *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) - *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) - *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) - *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) - *reinterpret_cast<long double *>(a.val));
                    case String:
                        return *new DisVar();
                }
            case String:
                string s;
                switch (a.Type) {
                    default:
                        return *new DisVar();
                    case Integer:
                        s = *reinterpret_cast<string *>(this->val);
                        s.erase(s.end() - *reinterpret_cast<int *>(a.val), s.end());
                        return *new DisVar(a);
                    case Long:
                        s = *reinterpret_cast<string *>(this->val);
                        s.erase(s.end() - *reinterpret_cast<long *>(a.val), s.end());
                        return *new DisVar(a);
                    case LL:
                        s = *reinterpret_cast<string *>(this->val);
                        s.erase(s.end() - *reinterpret_cast<long long *>(a.val), s.end());
                        return *new DisVar(a);
                    case String:
                        size_t pos = 0;
                        s = *reinterpret_cast<string *>(this->val);
                        while ((pos = s.find(*reinterpret_cast<string *>(a.val))) != std::string::npos) {
                            s.erase(pos, reinterpret_cast<string *>(a.val)->length());
                        }
                        return *new DisVar(s);
                }
        }
    }

    DisVar &operator*(const DisVar &a) const {
        switch (this->Type) {
            default:
                return *new DisVar();
            case Integer:
                switch (a.Type) {
                    case Integer:
                        return *new DisVar(*reinterpret_cast<int *>(this->val) * *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(*reinterpret_cast<int *>(this->val) * *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(*reinterpret_cast<int *>(this->val) * *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(*reinterpret_cast<int *>(this->val) * *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<int *>(this->val) * *reinterpret_cast<long double *>(a.val));
                    case String:
                        return *new DisVar();
                }
            case Long:
                switch (a.Type) {
                    case Integer:
                        return *new DisVar(*reinterpret_cast<long *>(this->val) * *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(*reinterpret_cast<long *>(this->val) * *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<long *>(this->val) * *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(*reinterpret_cast<long *>(this->val) * *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<long *>(this->val) * *reinterpret_cast<long double *>(a.val));
                    case String:
                        return *new DisVar();
                }
            case LL:
                switch (a.Type) {
                    case Integer:
                        return *new DisVar(*reinterpret_cast<long long *>(this->val) * *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) * *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) * *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) * *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) * *reinterpret_cast<long double *>(a.val));
                    case String:
                        return *new DisVar();
                }
            case Double:
                switch (a.Type) {
                    case Integer:
                        return *new DisVar(*reinterpret_cast<double *>(this->val) * *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(*reinterpret_cast<double *>(this->val) * *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<double *>(this->val) * *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(*reinterpret_cast<double *>(this->val) * *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<double *>(this->val) * *reinterpret_cast<long double *>(a.val));
                    case String:
                        return *new DisVar();
                }
            case LD:
                switch (a.Type) {
                    case Integer:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) * *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) * *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) * *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) * *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) * *reinterpret_cast<long double *>(a.val));
                    case String:
                        return *new DisVar();
                }
            case String:
                string r, s;
                switch (a.Type) {
                    default:
                        return *new DisVar();
                    case Integer:
                        s = *reinterpret_cast<string *>(this->val);
                        for (int c = 0; c < *reinterpret_cast<int *>(a.val); c++) {
                            r += s;
                        }
                        return *new DisVar(r);
                    case Long:
                        r = *reinterpret_cast<string *>(this->val);
                        for (int c = 0; c < *reinterpret_cast<long *>(a.val); c++) {
                            r += s;
                        }
                        return *new DisVar(r);
                    case LL:
                        r = *reinterpret_cast<string *>(this->val);
                        for (int c = 0; c < *reinterpret_cast<long long *>(a.val); c++) {
                            r += s;
                        }
                        return *new DisVar(r);
                }
        }
    }

    DisVar &operator/(const DisVar &a) const {
        switch (this->Type) {
            default:
                return *new DisVar();
            case Integer:
                switch (a.Type) {
                    case Integer:
                        return *new DisVar(*reinterpret_cast<int *>(this->val) / *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(*reinterpret_cast<int *>(this->val) / *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(*reinterpret_cast<int *>(this->val) / *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(*reinterpret_cast<int *>(this->val) / *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<int *>(this->val) / *reinterpret_cast<long double *>(a.val));
                    case String:
                        return *new DisVar();
                }
            case Long:
                switch (a.Type) {
                    case Integer:
                        return *new DisVar(*reinterpret_cast<long *>(this->val) / *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(*reinterpret_cast<long *>(this->val) / *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<long *>(this->val) / *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(*reinterpret_cast<long *>(this->val) / *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<long *>(this->val) / *reinterpret_cast<long double *>(a.val));
                    case String:
                        return *new DisVar();
                }
            case LL:
                switch (a.Type) {
                    case Integer:
                        return *new DisVar(*reinterpret_cast<long long *>(this->val) / *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) / *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) / *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) / *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) / *reinterpret_cast<long double *>(a.val));
                    case String:
                        return *new DisVar();
                }
            case Double:
                switch (a.Type) {
                    case Integer:
                        return *new DisVar(*reinterpret_cast<double *>(this->val) / *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(*reinterpret_cast<double *>(this->val) / *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<double *>(this->val) / *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(*reinterpret_cast<double *>(this->val) / *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<double *>(this->val) / *reinterpret_cast<long double *>(a.val));
                    case String:
                        return *new DisVar();
                }
            case LD:
                switch (a.Type) {
                    case Integer:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) / *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) / *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) / *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) / *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) / *reinterpret_cast<long double *>(a.val));
                    case String:
                        return *new DisVar();
                }
            case String:
                string r, s;
                switch (a.Type) {
                    default:
                        return *new DisVar();
                    case String:
                        s = *reinterpret_cast<string *>(this->val);
                        r = *reinterpret_cast<string *>(a.val);
                        if (reinterpret_cast<string *>(a.val)->length() == 0)
                            return *new DisVar(0);
                        int count = 0;
                        for (size_t offset = s.find(r); offset != std::string::npos;
                             offset = s.find(r, offset + r.length())) {
                            ++count;
                        }
                        return *new DisVar(count);
                }
        }
    }


    [[nodiscard]] inline string value() const {
        switch (this->Type) {
            case Integer:
                return to_string(*reinterpret_cast<int *>(this->val));
            case Long:
                return to_string(*reinterpret_cast<long *>(this->val));
            case LL:
                return to_string(*reinterpret_cast<long long *>(this->val));
            case Double:
                return to_string(*reinterpret_cast<double *>(this->val));
            case LD:
                return to_string(*reinterpret_cast<long double *>(this->val));
            case String:
                return *reinterpret_cast<string *>(this->val);
        }
    }
};

int main() {

    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    DisVar x;
    DisVar test("Hahaalmaolmao");
    DisVar test1("lmao");
    for (int c = 0; c < 1000000; c++) {
        x = test/test1;
    }
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span1 = duration_cast<duration<double>>(t2 - t1);
    std::cout << time_span1.count() << endl;
    cout << x.value() << endl;

    t1 = high_resolution_clock::now();

    for (int c = 0; c < 1000000; c++) {
        string ctest = "Hahaalmao";
        string ctest1 = "lmao";
        if (ctest.length() == 0) {

        }
        int count = 0;
        for (size_t offset = ctest.find(ctest1); offset != std::string::npos;
             offset = ctest.find(ctest1, offset + ctest1.length()))
        {
            ++count;
        }
    }
    t2 = high_resolution_clock::now();
    duration<double> time_span2 = duration_cast<duration<double>>(t2 - t1);
    std::cout << time_span2.count() << endl;

    return 0;
}
