#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-narrowing-conversions"
#pragma ide diagnostic ignored "bugprone-narrowing-conversions"
#pragma once
#pragma auto_inline (on)
#include <string>
#include <iostream>
using namespace std;

/*
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
*/
class DisVar {
private:
    void *val{};
public:
    enum type {
        Bool=0, Integer=1, Long=2, LL=3, Double=4, LD=5, String=6, Untype=7
    };
    type Type{};

    inline explicit DisVar() : Type(type::Untype), val(nullptr) {};

    inline explicit DisVar(const bool a) : Type(type::Bool), val(new bool(a)) {};

    inline explicit DisVar(const int a) : Type(type::Integer), val(new int(a)) {};

    inline explicit DisVar(const long a) : Type(type::Long), val(new long(a)) {};

    inline explicit DisVar(const long long a) : Type(type::LL), val(new long long(a)) {};

    inline explicit DisVar(const double a) : Type(type::Double), val(new double(a)) {};

    inline explicit DisVar(const long double a) : Type(type::LD), val(new long double(a)) {};

    inline explicit DisVar(string a) : Type(type::String), val(new string(std::move(a))) {};

    inline explicit DisVar(const char a[]) : Type(type::String), val(new string(a)) {};

    //copy constructor
    inline DisVar(const DisVar &other) : Type(other.Type), val(nullptr) {
        switch (other.Type) {
            case Bool:
                this->val = new bool(*reinterpret_cast<bool *>(other.val));
                return;
            case Integer:
                this->val = new int(*reinterpret_cast<int *>(other.val));
                return;
            case Long:
                this->val = new long(*reinterpret_cast<long *>(other.val));
                return;
            case LL:
                this->val = new long long(*reinterpret_cast<long long *>(other.val));
                return;
            case Double:
                this->val = new double(*reinterpret_cast<double *>(other.val));
                return;
            case LD:
                this->val = new long double(*reinterpret_cast<long double *>(other.val));
                return;
            case String:
                this->val = new string(*reinterpret_cast<string *>(other.val));
                return;
            case Untype:
                this->val = nullptr;
                return;
        }
    };

    //conversion operations
    inline DisVar &operator=(bool a) {
        this->val = new bool(a);
        Type = Bool;
        return *this;
    };

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

    inline DisVar &operator=(const DisVar& a)=default;

    template<typename t>
    inline DisVar &operator=(t a) {
        cout<<"anon"<<endl;
        this->val = new t(a);
        Type = Untype;
        return *this;
    };

    //destructor
    inline ~DisVar() {
        free(val);
        val = nullptr;
    }

    //arithmetic operations
    DisVar &operator+(const DisVar &a) const {
        switch (this->Type) {
            case Bool:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(*reinterpret_cast<bool *>(this->val) + *reinterpret_cast<bool *>(a.val));
                    case Integer:
                        return *new DisVar(*reinterpret_cast<bool *>(this->val) + *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(*reinterpret_cast<bool *>(this->val) + *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<bool *>(this->val) + *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(*reinterpret_cast<bool *>(this->val) + *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<bool *>(this->val) + *reinterpret_cast<long double *>(a.val));
                    default:
                        return *new DisVar();
                }
            case Integer:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(*reinterpret_cast<int *>(this->val) + *reinterpret_cast<bool *>(a.val));
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
                    default:
                        return *new DisVar();
                }
            case Long:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(*reinterpret_cast<long *>(this->val) + *reinterpret_cast<bool *>(a.val));
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
                    default:
                        return *new DisVar();
                }
            case LL:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) + *reinterpret_cast<bool *>(a.val));
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
                    default:
                        return *new DisVar();
                }
            case Double:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(*reinterpret_cast<double *>(this->val) + *reinterpret_cast<bool *>(a.val));
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
                    default:
                        return *new DisVar();
                }
            case LD:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) + *reinterpret_cast<bool *>(a.val));
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
                    default:
                        return *new DisVar();
                }
            case String:
                switch (a.Type) {
                    case String:
                        return *new DisVar(*reinterpret_cast<string *>(this->val) + *reinterpret_cast<string *>(a.val));
                    default:
                        return *new DisVar();
                }
            default:
                return *new DisVar();
        }
    }

    void operator+=(const DisVar &a) {
        switch (this->Type) {
            case Bool:
                switch (a.Type) {
                    case Bool:
                        *this = *new DisVar(*reinterpret_cast<bool *>(this->val) + *reinterpret_cast<bool *>(a.val));
                        return;
                    case Integer:
                        *this = *new DisVar(*reinterpret_cast<bool *>(this->val) + *reinterpret_cast<int *>(a.val));
                        return;
                    case Long:
                        *this = *new DisVar(*reinterpret_cast<bool *>(this->val) + *reinterpret_cast<long *>(a.val));
                        return;
                    case LL:
                        *this = *new DisVar(*reinterpret_cast<bool *>(this->val) + *reinterpret_cast<long long *>(a.val));
                        return;
                    case Double:
                        *this = *new DisVar(*reinterpret_cast<bool *>(this->val) + *reinterpret_cast<double *>(a.val));
                        return;
                    case LD:
                        *this = *new DisVar(*reinterpret_cast<bool *>(this->val) + *reinterpret_cast<long double *>(a.val));
                        return;
                    default:
                        *this = *new DisVar();
                        return;
                }
            case Integer:
                switch (a.Type) {
                    case Bool:
                        *this = *new DisVar(*reinterpret_cast<int *>(this->val) + *reinterpret_cast<bool *>(a.val));
                        return;
                    case Integer:
                        *this = *new DisVar(*reinterpret_cast<int *>(this->val) + *reinterpret_cast<int *>(a.val));
                        return;
                    case Long:
                        *this = *new DisVar(*reinterpret_cast<int *>(this->val) + *reinterpret_cast<long *>(a.val));
                        return;
                    case LL:
                        *this = *new DisVar(*reinterpret_cast<int *>(this->val) + *reinterpret_cast<long long *>(a.val));
                        return;
                    case Double:
                        *this = *new DisVar(*reinterpret_cast<int *>(this->val) + *reinterpret_cast<double *>(a.val));
                        return;
                    case LD:
                        *this = *new DisVar(*reinterpret_cast<int *>(this->val) + *reinterpret_cast<long double *>(a.val));
                        return;
                    default:
                        *this = *new DisVar();
                        return;
                }
            case Long:
                switch (a.Type) {
                    case Bool:
                        *this = *new DisVar(*reinterpret_cast<long *>(this->val) + *reinterpret_cast<bool *>(a.val));
                        return;
                    case Integer:
                        *this = *new DisVar(*reinterpret_cast<long *>(this->val) + *reinterpret_cast<int *>(a.val));
                        return;
                    case Long:
                        *this = *new DisVar(*reinterpret_cast<long *>(this->val) + *reinterpret_cast<long *>(a.val));
                        return;
                    case LL:
                        *this = *new DisVar(*reinterpret_cast<long *>(this->val) + *reinterpret_cast<long long *>(a.val));
                        return;
                    case Double:
                        *this = *new DisVar(*reinterpret_cast<long *>(this->val) + *reinterpret_cast<double *>(a.val));
                        return;
                    case LD:
                        *this = *new DisVar(*reinterpret_cast<long *>(this->val) + *reinterpret_cast<long double *>(a.val));
                        return;
                    default:
                        *this = *new DisVar();
                        return;
                }
            case LL:
                switch (a.Type) {
                    case Bool:
                        *this = *new DisVar(*reinterpret_cast<long long *>(this->val) + *reinterpret_cast<bool *>(a.val));
                        return;
                    case Integer:
                        *this = *new DisVar(*reinterpret_cast<long long *>(this->val) + *reinterpret_cast<int *>(a.val));
                        return;
                    case Long:
                        *this = *new DisVar(*reinterpret_cast<long long *>(this->val) + *reinterpret_cast<long *>(a.val));
                        return;
                    case LL:
                        *this = *new DisVar(
                                *reinterpret_cast<long long *>(this->val) + *reinterpret_cast<long long *>(a.val));
                        return;
                    case Double:
                        *this = *new DisVar(*reinterpret_cast<long long *>(this->val) + *reinterpret_cast<double *>(a.val));
                        return;
                    case LD:
                        *this = *new DisVar(
                                *reinterpret_cast<long long *>(this->val) + *reinterpret_cast<long double *>(a.val));
                        return;
                    default:
                        *this = *new DisVar();
                        return;
                }
            case Double:
                switch (a.Type) {
                    case Bool:
                        *this = *new DisVar(*reinterpret_cast<double *>(this->val) + *reinterpret_cast<bool *>(a.val));
                        return;
                    case Integer:
                        *this = *new DisVar(*reinterpret_cast<double *>(this->val) + *reinterpret_cast<int *>(a.val));
                        return;
                    case Long:
                        *this = *new DisVar(*reinterpret_cast<double *>(this->val) + *reinterpret_cast<long *>(a.val));
                        return;
                    case LL:
                        *this = *new DisVar(*reinterpret_cast<double *>(this->val) + *reinterpret_cast<long long *>(a.val));
                        return;
                    case Double:
                        *this = *new DisVar(*reinterpret_cast<double *>(this->val) + *reinterpret_cast<double *>(a.val));
                        return;
                    case LD:
                        *this = *new DisVar(
                                *reinterpret_cast<double *>(this->val) + *reinterpret_cast<long double *>(a.val));
                        return;
                    default:
                        *this = *new DisVar();
                        return;
                }
            case LD:
                switch (a.Type) {
                    case Bool:
                        *this = *new DisVar(*reinterpret_cast<long double *>(this->val) + *reinterpret_cast<bool *>(a.val));
                        return;
                    case Integer:
                        *this = *new DisVar(*reinterpret_cast<long double *>(this->val) + *reinterpret_cast<int *>(a.val));
                        return;
                    case Long:
                        *this = *new DisVar(*reinterpret_cast<long double *>(this->val) + *reinterpret_cast<long *>(a.val));
                        return;
                    case LL:
                        *this = *new DisVar(
                                *reinterpret_cast<long double *>(this->val) + *reinterpret_cast<long long *>(a.val));
                        return;
                    case Double:
                        *this = *new DisVar(
                                *reinterpret_cast<long double *>(this->val) + *reinterpret_cast<double *>(a.val));
                        return;
                    case LD:
                        *this = *new DisVar(
                                *reinterpret_cast<long double *>(this->val) + *reinterpret_cast<long double *>(a.val));
                        return;
                    default:
                        *this = *new DisVar();
                        return;
                }
            case String:
                switch (a.Type) {
                    case String:
                        *this = *new DisVar(*reinterpret_cast<string *>(this->val) + *reinterpret_cast<string *>(a.val));
                        return;
                    default:
                        *this = *new DisVar();
                        return;
                }
            default:
                *this = *new DisVar();
                return;
        }
    }

    DisVar &operator-(const DisVar &a) const {
        switch (this->Type) {
            default:
                return *new DisVar();
            case Bool:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(*reinterpret_cast<bool *>(this->val) - *reinterpret_cast<bool *>(a.val));
                    case Integer:
                        return *new DisVar(*reinterpret_cast<bool *>(this->val) - *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(*reinterpret_cast<bool *>(this->val) - *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<bool *>(this->val) - *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(*reinterpret_cast<bool *>(this->val) - *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<bool *>(this->val) - *reinterpret_cast<long double *>(a.val));
                    default:
                        return *new DisVar();
                }
            case Integer:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(*reinterpret_cast<int *>(this->val) - *reinterpret_cast<bool *>(a.val));
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
                    default:
                        return *new DisVar();
                }
            case Long:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(*reinterpret_cast<long *>(this->val) - *reinterpret_cast<bool *>(a.val));
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
                    default:
                        return *new DisVar();
                }
            case LL:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) - *reinterpret_cast<bool *>(a.val));
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
                    default:
                        return *new DisVar();
                }
            case Double:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(*reinterpret_cast<double *>(this->val) - *reinterpret_cast<bool *>(a.val));
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
                    default:
                        return *new DisVar();
                }
            case LD:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) - *reinterpret_cast<bool *>(a.val));
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
                    default:
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
                        return *new DisVar(s);
                    case Long:
                        s = *reinterpret_cast<string *>(this->val);
                        s.erase(s.end() - *reinterpret_cast<long *>(a.val), s.end());
                        return *new DisVar(s);
                    case LL:
                        s = *reinterpret_cast<string *>(this->val);
                        s.erase(s.end() - *reinterpret_cast<long long *>(a.val), s.end());
                        return *new DisVar(s);
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

    void operator-=(const DisVar &a) {
        switch (this->Type) {
            default:
                *this = *new DisVar();
                return;
            case Bool:
                switch (a.Type) {
                    case Bool:
                        *this = *new DisVar(*reinterpret_cast<bool *>(this->val) - *reinterpret_cast<bool *>(a.val));
                        return;
                    case Integer:
                        *this = *new DisVar(*reinterpret_cast<bool *>(this->val) - *reinterpret_cast<int *>(a.val));
                        return;
                    case Long:
                        *this = *new DisVar(*reinterpret_cast<bool *>(this->val) - *reinterpret_cast<long *>(a.val));
                        return;
                    case LL:
                        *this = *new DisVar(*reinterpret_cast<bool *>(this->val) - *reinterpret_cast<long long *>(a.val));
                        return;
                    case Double:
                        *this = *new DisVar(*reinterpret_cast<bool *>(this->val) - *reinterpret_cast<double *>(a.val));
                        return;
                    case LD:
                        *this = *new DisVar(*reinterpret_cast<bool *>(this->val) - *reinterpret_cast<long double *>(a.val));
                        return;
                    default:
                        *this = *new DisVar();
                        return;
                }
            case Integer:
                switch (a.Type) {
                    case Bool:
                        *this = *new DisVar(*reinterpret_cast<int *>(this->val) - *reinterpret_cast<bool *>(a.val));
                        return;
                    case Integer:
                        *this = *new DisVar(*reinterpret_cast<int *>(this->val) - *reinterpret_cast<int *>(a.val));
                        return;
                    case Long:
                        *this = *new DisVar(*reinterpret_cast<int *>(this->val) - *reinterpret_cast<long *>(a.val));
                        return;
                    case LL:
                        *this = *new DisVar(*reinterpret_cast<int *>(this->val) - *reinterpret_cast<long long *>(a.val));
                        return;
                    case Double:
                        *this = *new DisVar(*reinterpret_cast<int *>(this->val) - *reinterpret_cast<double *>(a.val));
                        return;
                    case LD:
                        *this = *new DisVar(*reinterpret_cast<int *>(this->val) - *reinterpret_cast<long double *>(a.val));
                        return;
                    default:
                        *this = *new DisVar();
                        return;
                }
            case Long:
                switch (a.Type) {
                    case Bool:
                        *this = *new DisVar(*reinterpret_cast<long *>(this->val) - *reinterpret_cast<bool *>(a.val));
                        return;
                    case Integer:
                        *this = *new DisVar(*reinterpret_cast<long *>(this->val) - *reinterpret_cast<int *>(a.val));
                        return;
                    case Long:
                        *this = *new DisVar(*reinterpret_cast<long *>(this->val) - *reinterpret_cast<long *>(a.val));
                        return;
                    case LL:
                        *this = *new DisVar(*reinterpret_cast<long *>(this->val) - *reinterpret_cast<long long *>(a.val));
                        return;
                    case Double:
                        *this = *new DisVar(*reinterpret_cast<long *>(this->val) - *reinterpret_cast<double *>(a.val));
                        return;
                    case LD:
                        *this = *new DisVar(*reinterpret_cast<long *>(this->val) - *reinterpret_cast<long double *>(a.val));
                        return;
                    default:
                        *this = *new DisVar();
                        return;
                }
            case LL:
                switch (a.Type) {
                    case Bool:
                        *this = *new DisVar(*reinterpret_cast<long long *>(this->val) - *reinterpret_cast<bool *>(a.val));
                        return;
                    case Integer:
                        *this = *new DisVar(*reinterpret_cast<long long *>(this->val) - *reinterpret_cast<int *>(a.val));
                        return;
                    case Long:
                        *this = *new DisVar(*reinterpret_cast<long long *>(this->val) - *reinterpret_cast<long *>(a.val));
                        return;
                    case LL:
                        *this = *new DisVar(
                                *reinterpret_cast<long long *>(this->val) - *reinterpret_cast<long long *>(a.val));
                        return;
                    case Double:
                        *this = *new DisVar(*reinterpret_cast<long long *>(this->val) - *reinterpret_cast<double *>(a.val));
                        return;
                    case LD:
                        *this = *new DisVar(
                                *reinterpret_cast<long long *>(this->val) - *reinterpret_cast<long double *>(a.val));
                        return;
                    default:
                        *this = *new DisVar();
                        return;
                }
            case Double:
                switch (a.Type) {
                    case Bool:
                        *this = *new DisVar(*reinterpret_cast<double *>(this->val) - *reinterpret_cast<bool *>(a.val));
                        return;
                    case Integer:
                        *this = *new DisVar(*reinterpret_cast<double *>(this->val) - *reinterpret_cast<int *>(a.val));
                        return;
                    case Long:
                        *this = *new DisVar(*reinterpret_cast<double *>(this->val) - *reinterpret_cast<long *>(a.val));
                        return;
                    case LL:
                        *this = *new DisVar(*reinterpret_cast<double *>(this->val) - *reinterpret_cast<long long *>(a.val));
                        return;
                    case Double:
                        *this = *new DisVar(*reinterpret_cast<double *>(this->val) - *reinterpret_cast<double *>(a.val));
                        return;
                    case LD:
                        *this = *new DisVar(
                                *reinterpret_cast<double *>(this->val) - *reinterpret_cast<long double *>(a.val));
                        return;
                    default:
                        *this = *new DisVar();
                        return;
                }
            case LD:
                switch (a.Type) {
                    case Bool:
                        *this = *new DisVar(*reinterpret_cast<long double *>(this->val) - *reinterpret_cast<bool *>(a.val));
                        return;
                    case Integer:
                        *this = *new DisVar(*reinterpret_cast<long double *>(this->val) - *reinterpret_cast<int *>(a.val));
                        return;
                    case Long:
                        *this = *new DisVar(*reinterpret_cast<long double *>(this->val) - *reinterpret_cast<long *>(a.val));
                        return;
                    case LL:
                        *this = *new DisVar(
                                *reinterpret_cast<long double *>(this->val) - *reinterpret_cast<long long *>(a.val));
                        return;
                    case Double:
                        *this = *new DisVar(
                                *reinterpret_cast<long double *>(this->val) - *reinterpret_cast<double *>(a.val));
                        return;
                    case LD:
                        *this = *new DisVar(
                                *reinterpret_cast<long double *>(this->val) - *reinterpret_cast<long double *>(a.val));
                        return;
                    default:
                        *this = *new DisVar();
                        return;
                }
            case String:
                string s;
                switch (a.Type) {
                    default:
                        *this= *new DisVar();
                        return;
                    case Integer:
                        s = *reinterpret_cast<string *>(this->val);
                        s.erase(s.end() - *reinterpret_cast<int *>(a.val), s.end());
                        *this= *new DisVar(s);
                        return;
                    case Long:
                        s = *reinterpret_cast<string *>(this->val);
                        s.erase(s.end() - *reinterpret_cast<long *>(a.val), s.end());
                        *this= *new DisVar(s);
                        return;
                    case LL:
                        s = *reinterpret_cast<string *>(this->val);
                        s.erase(s.end() - *reinterpret_cast<long long *>(a.val), s.end());
                        *this= *new DisVar(s);
                        return;
                    case String:
                        size_t pos = 0;
                        s = *reinterpret_cast<string *>(this->val);
                        while ((pos = s.find(*reinterpret_cast<string *>(a.val))) != std::string::npos) {
                            s.erase(pos, reinterpret_cast<string *>(a.val)->length());
                        }
                        *this= *new DisVar(s);
                        return;
                }
        }
    }

    DisVar &operator*(const DisVar &a) const {
        switch (this->Type) {
            default:
                return *new DisVar();
            case Bool:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(*reinterpret_cast<bool *>(this->val) * *reinterpret_cast<bool *>(a.val));
                    case Integer:
                        return *new DisVar(*reinterpret_cast<bool *>(this->val) * *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(*reinterpret_cast<bool *>(this->val) * *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<bool *>(this->val) * *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(*reinterpret_cast<bool *>(this->val) * *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<bool *>(this->val) * *reinterpret_cast<long double *>(a.val));
                    default:
                        return *new DisVar();
                }
            case Integer:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(*reinterpret_cast<int *>(this->val) * *reinterpret_cast<bool *>(a.val));
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
                    default:
                        return *new DisVar();
                }
            case Long:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(*reinterpret_cast<long *>(this->val) * *reinterpret_cast<bool *>(a.val));
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
                    default:
                        return *new DisVar();
                }
            case LL:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) * *reinterpret_cast<bool *>(a.val));
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
                    default:
                        return *new DisVar();
                }
            case Double:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(*reinterpret_cast<double *>(this->val) * *reinterpret_cast<bool *>(a.val));
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
                    default:
                        return *new DisVar();
                }
            case LD:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) * *reinterpret_cast<bool *>(a.val));
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
                    default:
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

    void operator*=(const DisVar &a) {
        switch (this->Type) {
            default:
                *this = *new DisVar();
                return;
            case Bool:
                switch (a.Type) {
                    case Bool:
                        *this = *new DisVar(*reinterpret_cast<bool *>(this->val) * *reinterpret_cast<bool *>(a.val));
                        return;
                    case Integer:
                        *this = *new DisVar(*reinterpret_cast<bool *>(this->val) * *reinterpret_cast<int *>(a.val));
                        return;
                    case Long:
                        *this = *new DisVar(*reinterpret_cast<bool *>(this->val) * *reinterpret_cast<long *>(a.val));
                        return;
                    case LL:
                        *this = *new DisVar(*reinterpret_cast<bool *>(this->val) * *reinterpret_cast<long long *>(a.val));
                        return;
                    case Double:
                        *this = *new DisVar(*reinterpret_cast<bool *>(this->val) * *reinterpret_cast<double *>(a.val));
                        return;
                    case LD:
                        *this = *new DisVar(*reinterpret_cast<bool *>(this->val) * *reinterpret_cast<long double *>(a.val));
                        return;
                    default:
                        *this = *new DisVar();
                        return;
                }
            case Integer:
                switch (a.Type) {
                    case Bool:
                        *this = *new DisVar(*reinterpret_cast<int *>(this->val) * *reinterpret_cast<bool *>(a.val));
                        return;
                    case Integer:
                        *this = *new DisVar(*reinterpret_cast<int *>(this->val) * *reinterpret_cast<int *>(a.val));
                        return;
                    case Long:
                        *this = *new DisVar(*reinterpret_cast<int *>(this->val) * *reinterpret_cast<long *>(a.val));
                        return;
                    case LL:
                        *this = *new DisVar(*reinterpret_cast<int *>(this->val) * *reinterpret_cast<long long *>(a.val));
                        return;
                    case Double:
                        *this = *new DisVar(*reinterpret_cast<int *>(this->val) * *reinterpret_cast<double *>(a.val));
                        return;
                    case LD:
                        *this = *new DisVar(*reinterpret_cast<int *>(this->val) * *reinterpret_cast<long double *>(a.val));
                        return;
                    default:
                        *this = *new DisVar();
                        return;
                }
            case Long:
                switch (a.Type) {
                    case Bool:
                        *this = *new DisVar(*reinterpret_cast<long *>(this->val) * *reinterpret_cast<bool *>(a.val));
                        return;
                    case Integer:
                        *this = *new DisVar(*reinterpret_cast<long *>(this->val) * *reinterpret_cast<int *>(a.val));
                        return;
                    case Long:
                        *this = *new DisVar(*reinterpret_cast<long *>(this->val) * *reinterpret_cast<long *>(a.val));
                        return;
                    case LL:
                        *this = *new DisVar(*reinterpret_cast<long *>(this->val) * *reinterpret_cast<long long *>(a.val));
                        return;
                    case Double:
                        *this = *new DisVar(*reinterpret_cast<long *>(this->val) * *reinterpret_cast<double *>(a.val));
                        return;
                    case LD:
                        *this = *new DisVar(*reinterpret_cast<long *>(this->val) * *reinterpret_cast<long double *>(a.val));
                        return;
                    default:
                        *this = *new DisVar();
                        return;
                }
            case LL:
                switch (a.Type) {
                    case Bool:
                        *this = *new DisVar(*reinterpret_cast<long long *>(this->val) * *reinterpret_cast<bool *>(a.val));
                        return;
                    case Integer:
                        *this = *new DisVar(*reinterpret_cast<long long *>(this->val) * *reinterpret_cast<int *>(a.val));
                        return;
                    case Long:
                        *this = *new DisVar(*reinterpret_cast<long long *>(this->val) * *reinterpret_cast<long *>(a.val));
                        return;
                    case LL:
                        *this = *new DisVar(
                                *reinterpret_cast<long long *>(this->val) * *reinterpret_cast<long long *>(a.val));
                        return;
                    case Double:
                        *this = *new DisVar(*reinterpret_cast<long long *>(this->val) * *reinterpret_cast<double *>(a.val));
                        return;
                    case LD:
                        *this = *new DisVar(
                                *reinterpret_cast<long long *>(this->val) * *reinterpret_cast<long double *>(a.val));
                        return;
                    default:
                        *this = *new DisVar();
                        return;
                }
            case Double:
                switch (a.Type) {
                    case Bool:
                        *this = *new DisVar(*reinterpret_cast<double *>(this->val) * *reinterpret_cast<bool *>(a.val));
                        return;
                    case Integer:
                        *this = *new DisVar(*reinterpret_cast<double *>(this->val) * *reinterpret_cast<int *>(a.val));
                        return;
                    case Long:
                        *this = *new DisVar(*reinterpret_cast<double *>(this->val) * *reinterpret_cast<long *>(a.val));
                        return;
                    case LL:
                        *this = *new DisVar(*reinterpret_cast<double *>(this->val) * *reinterpret_cast<long long *>(a.val));
                        return;
                    case Double:
                        *this = *new DisVar(*reinterpret_cast<double *>(this->val) * *reinterpret_cast<double *>(a.val));
                        return;
                    case LD:
                        *this = *new DisVar(
                                *reinterpret_cast<double *>(this->val) * *reinterpret_cast<long double *>(a.val));
                        return;
                    default:
                        *this = *new DisVar();
                        return;
                }
            case LD:
                switch (a.Type) {
                    case Bool:
                        *this = *new DisVar(*reinterpret_cast<long double *>(this->val) * *reinterpret_cast<bool *>(a.val));
                        return;
                    case Integer:
                        *this = *new DisVar(*reinterpret_cast<long double *>(this->val) * *reinterpret_cast<int *>(a.val));
                        return;
                    case Long:
                        *this = *new DisVar(*reinterpret_cast<long double *>(this->val) * *reinterpret_cast<long *>(a.val));
                        return;
                    case LL:
                        *this = *new DisVar(
                                *reinterpret_cast<long double *>(this->val) * *reinterpret_cast<long long *>(a.val));
                        return;
                    case Double:
                        *this = *new DisVar(
                                *reinterpret_cast<long double *>(this->val) * *reinterpret_cast<double *>(a.val));
                        return;
                    case LD:
                        *this = *new DisVar(
                                *reinterpret_cast<long double *>(this->val) * *reinterpret_cast<long double *>(a.val));
                        return;
                    default:
                        *this = *new DisVar();
                        return;
                }
            case String:
                string r, s;
                switch (a.Type) {
                    default:
                        *this= *new DisVar();
                        return;
                    case Integer:
                        s = *reinterpret_cast<string *>(this->val);
                        for (int c = 0; c < *reinterpret_cast<int *>(a.val); c++) {
                            r += s;
                        }
                        *this= *new DisVar(r);
                        return;
                    case Long:
                        r = *reinterpret_cast<string *>(this->val);
                        for (int c = 0; c < *reinterpret_cast<long *>(a.val); c++) {
                            r += s;
                        }
                        *this= *new DisVar(r);
                        return;
                    case LL:
                        r = *reinterpret_cast<string *>(this->val);
                        for (int c = 0; c < *reinterpret_cast<long long *>(a.val); c++) {
                            r += s;
                        }
                        *this= *new DisVar(r);
                        return;
                }
        }
    }

    DisVar &operator/(const DisVar &a) const {
        switch (this->Type) {
            default:
                return *new DisVar();
            case Bool:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(*reinterpret_cast<bool *>(this->val) / *reinterpret_cast<bool *>(a.val));
                    case Integer:
                        return *new DisVar(*reinterpret_cast<bool *>(this->val) / *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(*reinterpret_cast<bool *>(this->val) / *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<bool *>(this->val) / *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(*reinterpret_cast<bool *>(this->val) / *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<bool *>(this->val) / *reinterpret_cast<long double *>(a.val));
                    default:
                        return *new DisVar();
                }
            case Integer:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(*reinterpret_cast<int *>(this->val) / *reinterpret_cast<bool *>(a.val));
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
                    default:
                        return *new DisVar();
                }
            case Long:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(*reinterpret_cast<long *>(this->val) / *reinterpret_cast<bool *>(a.val));
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
                    default:
                        return *new DisVar();
                }
            case LL:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) / *reinterpret_cast<bool *>(a.val));
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
                    default:
                        return *new DisVar();
                }
            case Double:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(*reinterpret_cast<double *>(this->val) / *reinterpret_cast<bool *>(a.val));
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
                    default:
                        return *new DisVar();
                }
            case LD:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) / *reinterpret_cast<bool *>(a.val));
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
                    default:
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

    void operator/=(const DisVar &a) {
        switch (this->Type) {
            default:
                *this = *new DisVar();
                return;
            case Bool:
                switch (a.Type) {
                    case Bool:
                        *this = *new DisVar(*reinterpret_cast<bool *>(this->val) / *reinterpret_cast<bool *>(a.val));
                        return;
                    case Integer:
                        *this = *new DisVar(*reinterpret_cast<bool *>(this->val) / *reinterpret_cast<int *>(a.val));
                        return;
                    case Long:
                        *this = *new DisVar(*reinterpret_cast<bool *>(this->val) / *reinterpret_cast<long *>(a.val));
                        return;
                    case LL:
                        *this = *new DisVar(*reinterpret_cast<bool *>(this->val) / *reinterpret_cast<long long *>(a.val));
                        return;
                    case Double:
                        *this = *new DisVar(*reinterpret_cast<bool *>(this->val) / *reinterpret_cast<double *>(a.val));
                        return;
                    case LD:
                        *this = *new DisVar(*reinterpret_cast<bool *>(this->val) / *reinterpret_cast<long double *>(a.val));
                        return;
                    default:
                        *this = *new DisVar();
                        return;
                }
            case Integer:
                switch (a.Type) {
                    case Bool:
                        *this = *new DisVar(*reinterpret_cast<int *>(this->val) / *reinterpret_cast<bool *>(a.val));
                        return;
                    case Integer:
                        cout<<*reinterpret_cast<int *>(this->val) / *reinterpret_cast<int *>(a.val)<<endl;
                        *this = *new DisVar(*reinterpret_cast<int *>(this->val) / *reinterpret_cast<int *>(a.val));
                        return;
                    case Long:
                        *this = *new DisVar(*reinterpret_cast<int *>(this->val) / *reinterpret_cast<long *>(a.val));
                        return;
                    case LL:
                        *this = *new DisVar(*reinterpret_cast<int *>(this->val) / *reinterpret_cast<long long *>(a.val));
                        return;
                    case Double:
                        *this = *new DisVar(*reinterpret_cast<int *>(this->val) / *reinterpret_cast<double *>(a.val));
                        return;
                    case LD:
                        *this = *new DisVar(*reinterpret_cast<int *>(this->val) / *reinterpret_cast<long double *>(a.val));
                        return;
                    default:
                        *this = *new DisVar();
                        return;
                }
            case Long:
                switch (a.Type) {
                    case Bool:
                        *this = *new DisVar(*reinterpret_cast<long *>(this->val) / *reinterpret_cast<bool *>(a.val));
                        return;
                    case Integer:
                        *this = *new DisVar(*reinterpret_cast<long *>(this->val) / *reinterpret_cast<int *>(a.val));
                        return;
                    case Long:
                        *this = *new DisVar(*reinterpret_cast<long *>(this->val) / *reinterpret_cast<long *>(a.val));
                        return;
                    case LL:
                        *this = *new DisVar(*reinterpret_cast<long *>(this->val) / *reinterpret_cast<long long *>(a.val));
                        return;
                    case Double:
                        *this = *new DisVar(*reinterpret_cast<long *>(this->val) / *reinterpret_cast<double *>(a.val));
                        return;
                    case LD:
                        *this = *new DisVar(*reinterpret_cast<long *>(this->val) / *reinterpret_cast<long double *>(a.val));
                        return;
                    default:
                        *this = *new DisVar();
                        return;
                }
            case LL:
                switch (a.Type) {
                    case Bool:
                        *this = *new DisVar(*reinterpret_cast<long long *>(this->val) / *reinterpret_cast<bool *>(a.val));
                        return;
                    case Integer:
                        *this = *new DisVar(*reinterpret_cast<long long *>(this->val) / *reinterpret_cast<int *>(a.val));
                        return;
                    case Long:
                        *this = *new DisVar(*reinterpret_cast<long long *>(this->val) / *reinterpret_cast<long *>(a.val));
                        return;
                    case LL:
                        *this = *new DisVar(
                                *reinterpret_cast<long long *>(this->val) / *reinterpret_cast<long long *>(a.val));
                        return;
                    case Double:
                        *this = *new DisVar(*reinterpret_cast<long long *>(this->val) / *reinterpret_cast<double *>(a.val));
                        return;
                    case LD:
                        *this = *new DisVar(
                                *reinterpret_cast<long long *>(this->val) / *reinterpret_cast<long double *>(a.val));
                        return;
                    default:
                        *this = *new DisVar();
                        return;
                }
            case Double:
                switch (a.Type) {
                    case Bool:
                        *this = *new DisVar(*reinterpret_cast<double *>(this->val) / *reinterpret_cast<bool *>(a.val));
                        return;
                    case Integer:
                        *this = *new DisVar(*reinterpret_cast<double *>(this->val) / *reinterpret_cast<int *>(a.val));
                        return;
                    case Long:
                        *this = *new DisVar(*reinterpret_cast<double *>(this->val) / *reinterpret_cast<long *>(a.val));
                        return;
                    case LL:
                        *this = *new DisVar(*reinterpret_cast<double *>(this->val) / *reinterpret_cast<long long *>(a.val));
                        return;
                    case Double:
                        *this = *new DisVar(*reinterpret_cast<double *>(this->val) / *reinterpret_cast<double *>(a.val));
                        return;
                    case LD:
                        *this = *new DisVar(
                                *reinterpret_cast<double *>(this->val) / *reinterpret_cast<long double *>(a.val));
                        return;
                    default:
                        *this = *new DisVar();
                        return;
                }
            case LD:
                switch (a.Type) {
                    case Bool:
                        *this = *new DisVar(*reinterpret_cast<long double *>(this->val) / *reinterpret_cast<bool *>(a.val));
                        return;
                    case Integer:
                        *this = *new DisVar(*reinterpret_cast<long double *>(this->val) / *reinterpret_cast<int *>(a.val));
                        return;
                    case Long:
                        *this = *new DisVar(*reinterpret_cast<long double *>(this->val) / *reinterpret_cast<long *>(a.val));
                        return;
                    case LL:
                        *this = *new DisVar(
                                *reinterpret_cast<long double *>(this->val) / *reinterpret_cast<long long *>(a.val));
                        return;
                    case Double:
                        *this = *new DisVar(
                                *reinterpret_cast<long double *>(this->val) / *reinterpret_cast<double *>(a.val));
                        return;
                    case LD:
                        *this = *new DisVar(
                                *reinterpret_cast<long double *>(this->val) / *reinterpret_cast<long double *>(a.val));
                        return;
                    default:
                        *this = *new DisVar();
                        return;
                }
            case String:
                string r, s;
                switch (a.Type) {
                    default:
                        *this= *new DisVar();
                        return;
                    case String:
                        s = *reinterpret_cast<string *>(this->val);
                        r = *reinterpret_cast<string *>(a.val);
                        if (reinterpret_cast<string *>(a.val)->length() == 0){
                            *this= *new DisVar(0);
                            return;
                        }
                        int count = 0;
                        for (size_t offset = s.find(r); offset != std::string::npos;
                             offset = s.find(r, offset + r.length())) {
                            ++count;
                        }
                        *this= *new DisVar(count);
                        return;
                }
        }
    }

    DisVar &operator%(const DisVar &a) const {
        switch (this->Type) {
            default:
                return *new DisVar();
            case Bool:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(*reinterpret_cast<bool *>(this->val) % *reinterpret_cast<bool *>(a.val));
                    case Integer:
                        return *new DisVar(*reinterpret_cast<bool *>(this->val) % *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(*reinterpret_cast<bool *>(this->val) % *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<bool *>(this->val) % *reinterpret_cast<long long *>(a.val));
                    default:
                        return *new DisVar();
                }
            case Integer:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(*reinterpret_cast<int *>(this->val) % *reinterpret_cast<bool *>(a.val));
                    case Integer:
                        return *new DisVar(*reinterpret_cast<int *>(this->val) % *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(*reinterpret_cast<int *>(this->val) % *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(*reinterpret_cast<int *>(this->val) % *reinterpret_cast<long long *>(a.val));
                    default:
                        return *new DisVar();
                }
            case Long:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(*reinterpret_cast<long *>(this->val) % *reinterpret_cast<bool *>(a.val));
                    case Integer:
                        return *new DisVar(*reinterpret_cast<long *>(this->val) % *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(*reinterpret_cast<long *>(this->val) % *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<long *>(this->val) % *reinterpret_cast<long long *>(a.val));
                    default:
                        return *new DisVar();
                }
            case LL:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) % *reinterpret_cast<bool *>(a.val));
                    case Integer:
                        return *new DisVar(*reinterpret_cast<long long *>(this->val) % *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) % *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) % *reinterpret_cast<long long *>(a.val));
                    default:
                        return *new DisVar();
                }
        }
    }

    DisVar &operator>(const DisVar &a) const {
        switch (this->Type) {
            default:
                return *new DisVar();
            case Bool:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(*reinterpret_cast<bool *>(this->val) > *reinterpret_cast<bool *>(a.val));
                    case Integer:
                        return *new DisVar(*reinterpret_cast<bool *>(this->val) > *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(*reinterpret_cast<bool *>(this->val) > *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<bool *>(this->val) > *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(*reinterpret_cast<bool *>(this->val) > *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<bool *>(this->val) > *reinterpret_cast<long double *>(a.val));
                    default:
                        return *new DisVar();
                }
            case Integer:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(*reinterpret_cast<int *>(this->val) > *reinterpret_cast<bool *>(a.val));
                    case Integer:
                        return *new DisVar(*reinterpret_cast<int *>(this->val) > *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(*reinterpret_cast<int *>(this->val) > *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(*reinterpret_cast<int *>(this->val) > *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(*reinterpret_cast<int *>(this->val) > *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<int *>(this->val) > *reinterpret_cast<long double *>(a.val));
                    default:
                        return *new DisVar();
                }
            case Long:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(*reinterpret_cast<long *>(this->val) > *reinterpret_cast<bool *>(a.val));
                    case Integer:
                        return *new DisVar(*reinterpret_cast<long *>(this->val) > *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(*reinterpret_cast<long *>(this->val) > *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<long *>(this->val) > *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(*reinterpret_cast<long *>(this->val) > *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<long *>(this->val) > *reinterpret_cast<long double *>(a.val));
                    default:
                        return *new DisVar();
                }
            case LL:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) > *reinterpret_cast<bool *>(a.val));
                    case Integer:
                        return *new DisVar(*reinterpret_cast<long long *>(this->val) > *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) > *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) > *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) > *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) > *reinterpret_cast<long double *>(a.val));
                    default:
                        return *new DisVar();
                }
            case Double:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(*reinterpret_cast<double *>(this->val) > *reinterpret_cast<bool *>(a.val));
                    case Integer:
                        return *new DisVar(*reinterpret_cast<double *>(this->val) > *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(*reinterpret_cast<double *>(this->val) > *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<double *>(this->val) > *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(*reinterpret_cast<double *>(this->val) > *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<double *>(this->val) > *reinterpret_cast<long double *>(a.val));
                    default:
                        return *new DisVar();
                }
            case LD:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) > *reinterpret_cast<bool *>(a.val));
                    case Integer:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) > *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) > *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) > *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) > *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) > *reinterpret_cast<long double *>(a.val));
                    default:
                        return *new DisVar();
                }
        }
    }

    DisVar &operator<(const DisVar &a) const {
        switch (this->Type) {
            default:
                return *new DisVar();
            case Bool:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(*reinterpret_cast<bool *>(this->val) < *reinterpret_cast<bool *>(a.val));
                    case Integer:
                        return *new DisVar(*reinterpret_cast<bool *>(this->val) < *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(*reinterpret_cast<bool *>(this->val) < *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<bool *>(this->val) < *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(*reinterpret_cast<bool *>(this->val) < *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<bool *>(this->val) < *reinterpret_cast<long double *>(a.val));
                    default:
                        return *new DisVar();
                }
            case Integer:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(*reinterpret_cast<int *>(this->val) < *reinterpret_cast<bool *>(a.val));
                    case Integer:
                        return *new DisVar(*reinterpret_cast<int *>(this->val) < *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(*reinterpret_cast<int *>(this->val) < *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(*reinterpret_cast<int *>(this->val) < *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(*reinterpret_cast<int *>(this->val) < *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<int *>(this->val) < *reinterpret_cast<long double *>(a.val));
                    default:
                        return *new DisVar();
                }
            case Long:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(*reinterpret_cast<long *>(this->val) < *reinterpret_cast<bool *>(a.val));
                    case Integer:
                        return *new DisVar(*reinterpret_cast<long *>(this->val) < *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(*reinterpret_cast<long *>(this->val) < *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<long *>(this->val) < *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(*reinterpret_cast<long *>(this->val) < *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<long *>(this->val) < *reinterpret_cast<long double *>(a.val));
                    default:
                        return *new DisVar();
                }
            case LL:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) < *reinterpret_cast<bool *>(a.val));
                    case Integer:
                        return *new DisVar(*reinterpret_cast<long long *>(this->val) < *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) < *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) < *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) < *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) < *reinterpret_cast<long double *>(a.val));
                    default:
                        return *new DisVar();
                }
            case Double:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(*reinterpret_cast<double *>(this->val) < *reinterpret_cast<bool *>(a.val));
                    case Integer:
                        return *new DisVar(*reinterpret_cast<double *>(this->val) < *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(*reinterpret_cast<double *>(this->val) < *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<double *>(this->val) < *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(*reinterpret_cast<double *>(this->val) < *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<double *>(this->val) < *reinterpret_cast<long double *>(a.val));
                    default:
                        return *new DisVar();
                }
            case LD:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) < *reinterpret_cast<bool *>(a.val));
                    case Integer:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) < *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) < *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) < *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) < *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) < *reinterpret_cast<long double *>(a.val));
                    default:
                        return *new DisVar();
                }
        }
    }

    DisVar &operator>=(const DisVar &a) const {
        switch (this->Type) {
            default:
                return *new DisVar();
            case Bool:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(*reinterpret_cast<bool *>(this->val) >= *reinterpret_cast<bool *>(a.val));
                    case Integer:
                        return *new DisVar(*reinterpret_cast<bool *>(this->val) >= *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(*reinterpret_cast<bool *>(this->val) >= *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<bool *>(this->val) >= *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(*reinterpret_cast<bool *>(this->val) >= *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<bool *>(this->val) >= *reinterpret_cast<long double *>(a.val));
                    default:
                        return *new DisVar();
                }
            case Integer:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(*reinterpret_cast<int *>(this->val) >= *reinterpret_cast<bool *>(a.val));
                    case Integer:
                        return *new DisVar(*reinterpret_cast<int *>(this->val) >= *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(*reinterpret_cast<int *>(this->val) >= *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<int *>(this->val) >= *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(*reinterpret_cast<int *>(this->val) >= *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<int *>(this->val) >= *reinterpret_cast<long double *>(a.val));
                    default:
                        return *new DisVar();
                }
            case Long:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(*reinterpret_cast<long *>(this->val) >= *reinterpret_cast<bool *>(a.val));
                    case Integer:
                        return *new DisVar(*reinterpret_cast<long *>(this->val) >= *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(*reinterpret_cast<long *>(this->val) >= *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<long *>(this->val) >= *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(*reinterpret_cast<long *>(this->val) >= *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<long *>(this->val) >= *reinterpret_cast<long double *>(a.val));
                    default:
                        return *new DisVar();
                }
            case LL:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) >= *reinterpret_cast<bool *>(a.val));
                    case Integer:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) >= *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) >= *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) >= *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) >= *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) >= *reinterpret_cast<long double *>(a.val));
                    default:
                        return *new DisVar();
                }
            case Double:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(*reinterpret_cast<double *>(this->val) >= *reinterpret_cast<bool *>(a.val));
                    case Integer:
                        return *new DisVar(*reinterpret_cast<double *>(this->val) >= *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(*reinterpret_cast<double *>(this->val) >= *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<double *>(this->val) >= *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(
                                *reinterpret_cast<double *>(this->val) >= *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<double *>(this->val) >= *reinterpret_cast<long double *>(a.val));
                    default:
                        return *new DisVar();
                }
            case LD:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) >= *reinterpret_cast<bool *>(a.val));
                    case Integer:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) >= *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) >= *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) >= *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) >= *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) >= *reinterpret_cast<long double *>(a.val));
                    default:
                        return *new DisVar();
                }
        }
    }

    DisVar &operator<=(const DisVar &a) const {
        switch (this->Type) {
            default:
                return *new DisVar();
            case Bool:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(*reinterpret_cast<bool *>(this->val) <= *reinterpret_cast<bool *>(a.val));
                    case Integer:
                        return *new DisVar(*reinterpret_cast<bool *>(this->val) <= *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(*reinterpret_cast<bool *>(this->val) <= *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<bool *>(this->val) <= *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(*reinterpret_cast<bool *>(this->val) <= *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<bool *>(this->val) <= *reinterpret_cast<long double *>(a.val));
                    default:
                        return *new DisVar();
                }
            case Integer:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(*reinterpret_cast<int *>(this->val) <= *reinterpret_cast<bool *>(a.val));
                    case Integer:
                        return *new DisVar(*reinterpret_cast<int *>(this->val) <= *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(*reinterpret_cast<int *>(this->val) <= *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<int *>(this->val) <= *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(*reinterpret_cast<int *>(this->val) <= *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<int *>(this->val) <= *reinterpret_cast<long double *>(a.val));
                    default:
                        return *new DisVar();
                }
            case Long:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(*reinterpret_cast<long *>(this->val) <= *reinterpret_cast<bool *>(a.val));
                    case Integer:
                        return *new DisVar(*reinterpret_cast<long *>(this->val) <= *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(*reinterpret_cast<long *>(this->val) <= *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<long *>(this->val) <= *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(*reinterpret_cast<long *>(this->val) <= *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<long *>(this->val) <= *reinterpret_cast<long double *>(a.val));
                    default:
                        return *new DisVar();
                }
            case LL:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) <= *reinterpret_cast<bool *>(a.val));
                    case Integer:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) <= *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) <= *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) <= *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) <= *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) <= *reinterpret_cast<long double *>(a.val));
                    default:
                        return *new DisVar();
                }
            case Double:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(*reinterpret_cast<double *>(this->val) <= *reinterpret_cast<bool *>(a.val));
                    case Integer:
                        return *new DisVar(*reinterpret_cast<double *>(this->val) <= *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(*reinterpret_cast<double *>(this->val) <= *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<double *>(this->val) <= *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(
                                *reinterpret_cast<double *>(this->val) <= *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<double *>(this->val) <= *reinterpret_cast<long double *>(a.val));
                    default:
                        return *new DisVar();
                }
            case LD:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) <= *reinterpret_cast<bool *>(a.val));
                    case Integer:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) <= *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) <= *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) <= *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) <= *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) <= *reinterpret_cast<long double *>(a.val));
                    default:
                        return *new DisVar();
                }
        }
    }

    DisVar &operator==(const DisVar &a) const {
        switch (this->Type) {
            default:
                return *new DisVar();
            case Bool:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(*reinterpret_cast<bool *>(this->val) == *reinterpret_cast<bool *>(a.val));
                    case Integer:
                        return *new DisVar(*reinterpret_cast<bool *>(this->val) == *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(*reinterpret_cast<bool *>(this->val) == *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<bool *>(this->val) == *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(*reinterpret_cast<bool *>(this->val) == *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<bool *>(this->val) == *reinterpret_cast<long double *>(a.val));
                    default:
                        return *new DisVar();
                }
            case Integer:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(*reinterpret_cast<int *>(this->val) == *reinterpret_cast<bool *>(a.val));
                    case Integer:
                        return *new DisVar(*reinterpret_cast<int *>(this->val) == *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(*reinterpret_cast<int *>(this->val) == *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<int *>(this->val) == *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(*reinterpret_cast<int *>(this->val) == *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<int *>(this->val) == *reinterpret_cast<long double *>(a.val));
                    default:
                        return *new DisVar();
                }
            case Long:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(*reinterpret_cast<long *>(this->val) == *reinterpret_cast<bool *>(a.val));
                    case Integer:
                        return *new DisVar(*reinterpret_cast<long *>(this->val) == *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(*reinterpret_cast<long *>(this->val) == *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<long *>(this->val) == *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(*reinterpret_cast<long *>(this->val) == *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<long *>(this->val) == *reinterpret_cast<long double *>(a.val));
                    default:
                        return *new DisVar();
                }
            case LL:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) == *reinterpret_cast<bool *>(a.val));
                    case Integer:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) == *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) == *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) == *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) == *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) == *reinterpret_cast<long double *>(a.val));
                    default:
                        return *new DisVar();
                }
            case Double:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(*reinterpret_cast<double *>(this->val) == *reinterpret_cast<bool *>(a.val));
                    case Integer:
                        return *new DisVar(*reinterpret_cast<double *>(this->val) == *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(*reinterpret_cast<double *>(this->val) == *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<double *>(this->val) == *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(
                                *reinterpret_cast<double *>(this->val) == *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<double *>(this->val) == *reinterpret_cast<long double *>(a.val));
                    default:
                        return *new DisVar();
                }
            case LD:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) == *reinterpret_cast<bool *>(a.val));
                    case Integer:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) == *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) == *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) == *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) == *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) == *reinterpret_cast<long double *>(a.val));
                    default:
                        return *new DisVar();
                }
            case String:
                switch (a.Type) {
                    default:
                        return *new DisVar();
                    case String:
                        return *new DisVar(
                                *reinterpret_cast<string *>(this->val) == *reinterpret_cast<string *>(a.val));
                }
        }
    }

    DisVar &operator&&(const DisVar &a) const {
        switch (this->Type) {
            default:
                return *new DisVar();
            case Bool:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(*reinterpret_cast<bool *>(this->val) && *reinterpret_cast<bool *>(a.val));
                    case Integer:
                        return *new DisVar(*reinterpret_cast<bool *>(this->val) && *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(*reinterpret_cast<bool *>(this->val) && *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<bool *>(this->val) && *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(*reinterpret_cast<bool *>(this->val) && *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<bool *>(this->val) && *reinterpret_cast<long double *>(a.val));
                    default:
                        return *new DisVar();
                }
            case Integer:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(*reinterpret_cast<int *>(this->val) && *reinterpret_cast<bool *>(a.val));
                    case Integer:
                        return *new DisVar(*reinterpret_cast<int *>(this->val) && *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(*reinterpret_cast<int *>(this->val) && *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<int *>(this->val) && *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(*reinterpret_cast<int *>(this->val) && *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<int *>(this->val) && *reinterpret_cast<long double *>(a.val));
                    default:
                        return *new DisVar();
                }
            case Long:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(*reinterpret_cast<long *>(this->val) && *reinterpret_cast<bool *>(a.val));
                    case Integer:
                        return *new DisVar(*reinterpret_cast<long *>(this->val) && *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(*reinterpret_cast<long *>(this->val) && *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<long *>(this->val) && *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(*reinterpret_cast<long *>(this->val) && *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<long *>(this->val) && *reinterpret_cast<long double *>(a.val));
                    default:
                        return *new DisVar();
                }
            case LL:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) && *reinterpret_cast<bool *>(a.val));
                    case Integer:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) && *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) && *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) && *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) && *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) && *reinterpret_cast<long double *>(a.val));
                    default:
                        return *new DisVar();
                }
            case Double:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(*reinterpret_cast<double *>(this->val) && *reinterpret_cast<bool *>(a.val));
                    case Integer:
                        return *new DisVar(*reinterpret_cast<double *>(this->val) && *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(*reinterpret_cast<double *>(this->val) && *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<double *>(this->val) && *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(
                                *reinterpret_cast<double *>(this->val) && *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<double *>(this->val) && *reinterpret_cast<long double *>(a.val));
                    default:
                        return *new DisVar();
                }
            case LD:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) && *reinterpret_cast<bool *>(a.val));
                    case Integer:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) && *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) && *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) && *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) && *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) && *reinterpret_cast<long double *>(a.val));
                    default:
                        return *new DisVar();
                }
        }
    }

    DisVar &operator||(const DisVar &a) const {
        switch (this->Type) {
            default:
                return *new DisVar();
            case Bool:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(*reinterpret_cast<bool *>(this->val) || *reinterpret_cast<bool *>(a.val));
                    case Integer:
                        return *new DisVar(*reinterpret_cast<bool *>(this->val) || *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(*reinterpret_cast<bool *>(this->val) || *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<bool *>(this->val) || *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(*reinterpret_cast<bool *>(this->val) || *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<bool *>(this->val) || *reinterpret_cast<long double *>(a.val));
                    default:
                        return *new DisVar();
                }
            case Integer:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(*reinterpret_cast<int *>(this->val) || *reinterpret_cast<bool *>(a.val));
                    case Integer:
                        return *new DisVar(*reinterpret_cast<int *>(this->val) || *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(*reinterpret_cast<int *>(this->val) || *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<int *>(this->val) || *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(*reinterpret_cast<int *>(this->val) || *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<int *>(this->val) || *reinterpret_cast<long double *>(a.val));
                    default:
                        return *new DisVar();
                }
            case Long:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(*reinterpret_cast<long *>(this->val) || *reinterpret_cast<bool *>(a.val));
                    case Integer:
                        return *new DisVar(*reinterpret_cast<long *>(this->val) || *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(*reinterpret_cast<long *>(this->val) || *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<long *>(this->val) || *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(*reinterpret_cast<long *>(this->val) || *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<long *>(this->val) || *reinterpret_cast<long double *>(a.val));
                    default:
                        return *new DisVar();
                }
            case LL:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) || *reinterpret_cast<bool *>(a.val));
                    case Integer:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) || *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) || *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) || *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) || *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) || *reinterpret_cast<long double *>(a.val));
                    default:
                        return *new DisVar();
                }
            case Double:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(*reinterpret_cast<double *>(this->val) || *reinterpret_cast<bool *>(a.val));
                    case Integer:
                        return *new DisVar(*reinterpret_cast<double *>(this->val) || *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(*reinterpret_cast<double *>(this->val) || *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<double *>(this->val) || *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(
                                *reinterpret_cast<double *>(this->val) || *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<double *>(this->val) || *reinterpret_cast<long double *>(a.val));
                    default:
                        return *new DisVar();
                }
            case LD:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) || *reinterpret_cast<bool *>(a.val));
                    case Integer:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) || *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) || *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) || *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) || *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) || *reinterpret_cast<long double *>(a.val));
                    default:
                        return *new DisVar();
                }
        }
    }

    DisVar &operator!=(const DisVar &a) const {
        switch (this->Type) {
            default:
                return *new DisVar();
            case Bool:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(*reinterpret_cast<bool *>(this->val) != *reinterpret_cast<bool *>(a.val));
                    case Integer:
                        return *new DisVar(*reinterpret_cast<bool *>(this->val) != *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(*reinterpret_cast<bool *>(this->val) != *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<bool *>(this->val) != *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(*reinterpret_cast<bool *>(this->val) != *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<bool *>(this->val) != *reinterpret_cast<long double *>(a.val));
                    default:
                        return *new DisVar();
                }
            case Integer:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(*reinterpret_cast<int *>(this->val) != *reinterpret_cast<bool *>(a.val));
                    case Integer:
                        return *new DisVar(*reinterpret_cast<int *>(this->val) != *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(*reinterpret_cast<int *>(this->val) != *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<int *>(this->val) != *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(*reinterpret_cast<int *>(this->val) != *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<int *>(this->val) != *reinterpret_cast<long double *>(a.val));
                    default:
                        return *new DisVar();
                }
            case Long:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(*reinterpret_cast<long *>(this->val) != *reinterpret_cast<bool *>(a.val));
                    case Integer:
                        return *new DisVar(*reinterpret_cast<long *>(this->val) != *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(*reinterpret_cast<long *>(this->val) != *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<long *>(this->val) != *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(*reinterpret_cast<long *>(this->val) != *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<long *>(this->val) != *reinterpret_cast<long double *>(a.val));
                    default:
                        return *new DisVar();
                }
            case LL:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) != *reinterpret_cast<bool *>(a.val));
                    case Integer:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) != *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) != *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) != *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) != *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<long long *>(this->val) != *reinterpret_cast<long double *>(a.val));
                    default:
                        return *new DisVar();
                }
            case Double:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(*reinterpret_cast<double *>(this->val) != *reinterpret_cast<bool *>(a.val));
                    case Integer:
                        return *new DisVar(*reinterpret_cast<double *>(this->val) != *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(*reinterpret_cast<double *>(this->val) != *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<double *>(this->val) != *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(
                                *reinterpret_cast<double *>(this->val) != *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<double *>(this->val) != *reinterpret_cast<long double *>(a.val));
                    default:
                        return *new DisVar();
                }
            case LD:
                switch (a.Type) {
                    case Bool:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) != *reinterpret_cast<bool *>(a.val));
                    case Integer:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) != *reinterpret_cast<int *>(a.val));
                    case Long:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) != *reinterpret_cast<long *>(a.val));
                    case LL:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) != *reinterpret_cast<long long *>(a.val));
                    case Double:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) != *reinterpret_cast<double *>(a.val));
                    case LD:
                        return *new DisVar(
                                *reinterpret_cast<long double *>(this->val) != *reinterpret_cast<long double *>(a.val));
                    default:
                        return *new DisVar();
                }
        }
    }

    [[nodiscard]] inline string value() const {
        switch (this->Type) {
            case Bool:
                return to_string(*reinterpret_cast<bool *>(this->val));
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

    //explicit casting operators
    inline explicit operator short int() const {
        switch (Type) {
            default:
                throw bad_cast();
            case Bool:
                return static_cast<short int>(*reinterpret_cast<bool *>(val));
            case Integer:
                return static_cast<short int>(*reinterpret_cast<int *>(val));
            case Long:
                return static_cast<short int>(*reinterpret_cast<long *>(val));
            case LL:
                return static_cast<short int>(*reinterpret_cast<long long *>(val));
            case Double:
                return static_cast<short int>(*reinterpret_cast<double *>(val));
            case LD:
                return static_cast<short int>(*reinterpret_cast<long double *>(val));
        }
    }

    inline operator bool() const {
        switch (Type) {
            default:
                throw bad_cast();
            case Bool:
                return static_cast<bool>(*reinterpret_cast<bool *>(val));
            case Integer:
                return static_cast<bool>(*reinterpret_cast<int *>(val));
            case Long:
                return static_cast<bool>(*reinterpret_cast<long *>(val));
            case LL:
                return static_cast<bool>(*reinterpret_cast<long long *>(val));
            case Double:
                return static_cast<bool>(*reinterpret_cast<double *>(val));
            case LD:
                return static_cast<bool>(*reinterpret_cast<long double *>(val));
        }
    }

    inline explicit operator int() const {
        switch (Type) {
            default:
                throw bad_cast();
            case Bool:
                return static_cast<int>(*reinterpret_cast<bool *>(val));
            case Integer:
                return static_cast<int>(*reinterpret_cast<int *>(val));
            case Long:
                return static_cast<int>(*reinterpret_cast<long *>(val));
            case LL:
                return static_cast<int>(*reinterpret_cast<long long *>(val));
            case Double:
                return static_cast<int>(*reinterpret_cast<double *>(val));
            case LD:
                return static_cast<int>(*reinterpret_cast<long double *>(val));
        }
    }

    inline explicit operator long() const {
        switch (Type) {
            default:
                throw bad_cast();
            case Bool:
                return static_cast<long>(*reinterpret_cast<bool *>(val));
            case Integer:
                return static_cast<long>(*reinterpret_cast<int *>(val));
            case Long:
                return static_cast<long>(*reinterpret_cast<long *>(val));
            case LL:
                return static_cast<long>(*reinterpret_cast<long long *>(val));
            case Double:
                return static_cast<long>(*reinterpret_cast<double *>(val));
            case LD:
                return static_cast<long>(*reinterpret_cast<long double *>(val));
        }
    }

    inline operator long long() const {
        switch (Type) {
            default:
                throw bad_cast();
            case Bool:
                return static_cast<long long>(*reinterpret_cast<bool *>(val));
            case Integer:
                return static_cast<long long>(*reinterpret_cast<int *>(val));
            case Long:
                return static_cast<long long>(*reinterpret_cast<long *>(val));
            case LL:
                return static_cast<long long>(*reinterpret_cast<long long *>(val));
            case Double:
                return static_cast<long long>(*reinterpret_cast<double *>(val));
            case LD:
                return static_cast<long long>(*reinterpret_cast<long double *>(val));
        }
    }

    inline explicit operator float() const {
        switch (Type) {
            default:
                throw bad_cast();
            case Bool:
                return static_cast<float>(*reinterpret_cast<bool *>(val));
            case Integer:
                return static_cast<float>(*reinterpret_cast<int *>(val));
            case Long:
                return static_cast<float>(*reinterpret_cast<long *>(val));
            case LL:
                return static_cast<float>(*reinterpret_cast<long long *>(val));
            case Double:
                return static_cast<float>(*reinterpret_cast<double *>(val));
            case LD:
                return static_cast<float>(*reinterpret_cast<long double *>(val));
        }
    }

    inline explicit operator double() const {
        switch (Type) {
            default:
                throw bad_cast();
            case Bool:
                return static_cast<double>(*reinterpret_cast<bool *>(val));
            case Integer:
                return static_cast<double>(*reinterpret_cast<int *>(val));
            case Long:
                return static_cast<double>(*reinterpret_cast<long *>(val));
            case LL:
                return static_cast<double>(*reinterpret_cast<long long *>(val));
            case Double:
                return static_cast<double>(*reinterpret_cast<double *>(val));
            case LD:
                return static_cast<double>(*reinterpret_cast<long double *>(val));
        }
    }

    inline operator long double() const {
        switch (Type) {
            default:
                throw bad_cast();
            case Bool:
                return static_cast<long double>(*reinterpret_cast<bool *>(val));
            case Integer:
                return static_cast<long double>(*reinterpret_cast<int *>(val));
            case Long:
                return static_cast<long double>(*reinterpret_cast<long *>(val));
            case LL:
                return static_cast<long double>(*reinterpret_cast<long long *>(val));
            case Double:
                return static_cast<long double>(*reinterpret_cast<double *>(val));
            case LD:
                return static_cast<long double>(*reinterpret_cast<long double *>(val));
        }
    }

    inline operator string() const {
        switch (Type) {
            default:
                throw bad_cast();
            case String:
                return *reinterpret_cast<string *>(val);
        }
    }

};


#pragma clang diagnostic pop