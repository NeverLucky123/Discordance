#pragma once

#include <iostream>
#include <memory>
#include <chrono>
#include <utility>
#include <string_view>
#include <typeinfo>

using namespace std;
using namespace chrono;

enum type {
    Integer, Long, LL, Double, LD, String, Untype
};
template<typename t>
type varType(t a) {
    if (typeid(a) == typeid(int))
        return Integer;
    else if (typeid(a) == typeid(long))
        return Long;
    else if (typeid(a) == typeid(long long))
        return LL;
    else if (typeid(a) == typeid(double))
        return Double;
    else if (typeid(a) == typeid(long double))
        return LD;
    else if (typeid(a).name() == typeid(string).name())
        return String;
    else
        return Untype;
}

class DisVar {
private:
    void *val{};
    type Type{};
public:


    inline explicit DisVar() : Type(type::Untype), val(nullptr) {};

    inline explicit DisVar(int a) : Type(type::Integer), val(new int(a)) {};

    inline explicit DisVar(long a) : Type(type::Long), val(new long(a)) {};

    inline explicit DisVar(long long a) : Type(type::LL), val(new long long(a)) {};

    inline explicit DisVar(double a) : Type(type::Double), val(new double(a)) {};

    inline explicit DisVar(long double a) : Type(type::LD), val(new long double(a)) {};

    inline explicit DisVar(string a) : Type(type::String), val(new string(std::move(a))) {};

    //conversion operations
    inline DisVar &operator=(int a) {
        this->val = new int(a);
        Type = Integer;
        return *this;
    };

    inline DisVar &operator=(long a) {
        this->val = new long(a);
        Type = Long;
        return *this;
    };

    inline DisVar &operator=(long long a) {
        this->val = new long long(a);
        Type = LL;
        return *this;
    };

    inline DisVar &operator=(double a) {
        this->val = new double(a);
        Type = Double;
        return *this;
    };

    inline DisVar &operator=(long double a) {
        this->val = new long double(a);
        Type = LD;
        return *this;
    };

    inline DisVar &operator=(string a) {
        this->val = new string(std::move(a));
        Type = String;
        return *this;
    };

    template<typename t>
    inline DisVar &operator=(t a) {
        this->val = new t(a);
        Type = Untype;
        return *this;
    };

    template<typename t>
    DisVar &operator+(t a) const {
        switch (this->Type) {
            case Integer:
                switch (varType(a)) {
                    case Integer: case Long : case LL : case Double: case LD:
                        return *new DisVar(*reinterpret_cast<int *>(this->val) + a);
                    case String:
                    case Untype:
                        return *new DisVar();
                }
            case Long:
                switch (varType(a)) {
                    case Integer: case Long : case LL : case Double: case LD:
                        return *new DisVar(*reinterpret_cast<long *>(this->val) + a);
                    case String:
                    case Untype:
                        return *new DisVar();
                }
            case LL:
                switch (varType(a)) {
                    case Integer: case Long : case LL : case Double: case LD:
                        return *new DisVar(*reinterpret_cast<long long *>(this->val) + a);
                    case String:
                    case Untype:
                        return *new DisVar();
                }
            case Double:
                switch (varType(a)) {
                    case Integer: case Long : case LL : case Double: case LD:
                        return *new DisVar(*reinterpret_cast<double *>(this->val) + a);
                    case String:
                    case Untype:
                        return *new DisVar();
                }
            case LD:
                switch (varType(a)) {
                    case Integer: case Long : case LL : case Double: case LD:
                        return *new DisVar(*reinterpret_cast<long double *>(this->val) + a);
                    case String:
                    case Untype:
                        return *new DisVar();
                }
            case String:
            case Untype:
                return *new DisVar();
        }
    }
    DisVar &operator+(const string& a) const {
        switch (this->Type) {
            case String:
                switch (varType(a)) {
                    case String:
                        return *new DisVar(*reinterpret_cast<string *>(this->val) + a);
                    default:
                        return *new DisVar();
                }
            default:
                return *new DisVar();
        }
    }

    template<typename t>
    DisVar &operator-(t a) const {
        switch (this->Type) {
            case Integer:
                switch (varType(a)) {
                    case Integer: case Long : case LL : case Double: case LD:
                        return *new DisVar(*reinterpret_cast<int *>(this->val) - a);
                    case String:
                    case Untype:
                        return *new DisVar();
                }
            case Long:
                switch (varType(a)) {
                    case Integer: case Long : case LL : case Double: case LD:
                        return *new DisVar(*reinterpret_cast<long *>(this->val) - a);
                    case String:
                    case Untype:
                        return *new DisVar();
                }
            case LL:
                switch (varType(a)) {
                    case Integer: case Long : case LL : case Double: case LD:
                        return *new DisVar(*reinterpret_cast<long long *>(this->val) - a);
                    case String:
                    case Untype:
                        return *new DisVar();
                }
            case Double:
                switch (varType(a)) {
                    case Integer: case Long : case LL : case Double: case LD:
                        return *new DisVar(*reinterpret_cast<double *>(this->val) - a);
                    case String:
                    case Untype:
                        return *new DisVar();
                }
            case LD:
                switch (varType(a)) {
                    case Integer: case Long : case LL : case Double: case LD:
                        return *new DisVar(*reinterpret_cast<long double *>(this->val) - a);
                    case String:
                    case Untype:
                        return *new DisVar();
                }
            case Untype:
                return *new DisVar();
            case String:
                string s;
                switch (varType(a)) {
                    default:
                        return *new DisVar();
                    case Integer: case Long: case LL:
                        s = *reinterpret_cast<string *>(this->val);
                        s.erase(s.end() - a, s.end());
                        return *new DisVar(a);
                    case String:
                        size_t pos = 0;
                        s = *reinterpret_cast<string *>(this->val);
                        while ((pos = s.find(a)) != std::string::npos) {
                            s.erase(pos, a.length());
                        }
                        return *new DisVar(s);
                }
        }
    }
    template<typename t>
    DisVar &operator*(t a) const {
        switch (this->Type) {
            case Integer:
                switch (varType(a)) {
                    case Integer: case Long : case LL : case Double: case LD:
                        return *new DisVar(*reinterpret_cast<int *>(this->val) * a);
                    case String:
                    case Untype:
                        return *new DisVar();
                }
            case Long:
                switch (varType(a)) {
                    case Integer: case Long : case LL : case Double: case LD:
                        return *new DisVar(*reinterpret_cast<long *>(this->val) * a);
                    case String:
                    case Untype:
                        return *new DisVar();
                }
            case LL:
                switch (varType(a)) {
                    case Integer: case Long : case LL : case Double: case LD:
                        return *new DisVar(*reinterpret_cast<long long *>(this->val) * a);
                    case String:
                    case Untype:
                        return *new DisVar();
                }
            case Double:
                switch (varType(a)) {
                    case Integer: case Long : case LL : case Double: case LD:
                        return *new DisVar(*reinterpret_cast<double *>(this->val) * a);
                    case String:
                    case Untype:
                        return *new DisVar();
                }
            case LD:
                switch (varType(a)) {
                    case Integer: case Long : case LL : case Double: case LD:
                        return *new DisVar(*reinterpret_cast<long double *>(this->val) * a);
                    case String:
                    case Untype:
                        return *new DisVar();
                }
            case Untype:
                return *new DisVar();
            case String:
                string r, s;
                switch (varType(a)) {
                    default:
                        return *new DisVar();
                        case Integer: case Long: case LL:
                        s = *reinterpret_cast<string *>(this->val);
                        for (int c = 0; c < a; c++) {
                            r += s;
                        }
                        return *new DisVar(r);
                }
        }
    }
    template<typename t>
    DisVar &operator/(t a) const {
        switch (this->Type) {
            case Integer:
                switch (varType(a)) {
                    case Integer: case Long : case LL : case Double: case LD:
                        return *new DisVar(*reinterpret_cast<int *>(this->val) / a);
                    case String:
                    case Untype:
                        return *new DisVar();
                }
            case Long:
                switch (varType(a)) {
                    case Integer: case Long : case LL : case Double: case LD:
                        return *new DisVar(*reinterpret_cast<long *>(this->val) / a);
                    case String:
                    case Untype:
                        return *new DisVar();
                }
            case LL:
                switch (varType(a)) {
                    case Integer: case Long : case LL : case Double: case LD:
                        return *new DisVar(*reinterpret_cast<long long *>(this->val) / a);
                    case String:
                    case Untype:
                        return *new DisVar();
                }
            case Double:
                switch (varType(a)) {
                    case Integer: case Long : case LL : case Double: case LD:
                        return *new DisVar(*reinterpret_cast<double *>(this->val) / a);
                    case String:
                    case Untype:
                        return *new DisVar();
                }
            case LD:
                switch (varType(a)) {
                    case Integer: case Long : case LL : case Double: case LD:
                        return *new DisVar(*reinterpret_cast<long double *>(this->val) / a);
                    case String:
                    case Untype:
                        return *new DisVar();
                }
            case Untype:
                return *new DisVar();
            case String:
                string r, s;
                switch (varType(a)) {
                    default:
                        return *new DisVar();
                    case String:
                        s = *reinterpret_cast<string *>(this->val);
                        r = a;
                        if (a.length() == 0)
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

    //copy constructor
    inline DisVar(const DisVar &other) : Type(other.Type), val(nullptr) {
        switch (other.Type) {
            case Integer:
                cout << *reinterpret_cast<int *>(other.val) << endl;
                this->val = new int(*reinterpret_cast<int *>(other.val));
            case Long:
                this->val = new long(*reinterpret_cast<long *>(other.val));
            case LL:
                this->val = new long long(*reinterpret_cast<long long *>(other.val));
            case Double:
                this->val = new double(*reinterpret_cast<double *>(other.val));
            case LD:
                this->val = new long double(*reinterpret_cast<long double *>(other.val));
            case String:
                this->val = new string(*reinterpret_cast<string *>(other.val));
            case Untype:
                this->val = nullptr;
        }
    };

    //destructor
    inline ~DisVar() {
        free(val);
        val = nullptr;
    }

    //arithmetic operations
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
                    case Untype:
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
                    case Untype:
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
                    case Untype:
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
                    case Untype:
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
                    case Untype:
                        return *new DisVar();
                }
            case String:
                switch (a.Type) {
                    case String:
                        return *new DisVar(*reinterpret_cast<string *>(this->val) + *reinterpret_cast<string *>(a.val));
                    default:
                        return *new DisVar();
                }
            case Untype:
                return *new DisVar();
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
                    case Untype:
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
                    case Untype:
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
                    case Untype:
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
                    case Untype:
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
                    case Untype:
                        return *new DisVar();
                }
            case Untype:
                return *new DisVar();
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
                    case Untype:
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
                    case Untype:
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
                    case Untype:
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
                    case Untype:
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
                    case Untype:
                        return *new DisVar();
                }
            case Untype:
                return *new DisVar();
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
                    case Untype:
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
                    case Untype:
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
                    case Untype:
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
                    case Untype:
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
                    case Untype:
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
            case Untype:
                return "Untype";
        }
    }
};

