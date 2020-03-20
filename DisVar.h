#pragma once

#include <iostream>
#include <memory>
#include <chrono>
#include <utility>
#include <string_view>
#include <typeinfo>

using namespace std;
using namespace chrono;

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
    enum type {
        Bool, Integer, Long, LL, Double, LD, String, Untype
    };
    void *val{};
    type Type{};
public:


    inline explicit DisVar() : Type(type::Untype), val(nullptr) {};

    inline explicit DisVar(bool a) : Type(type::Bool), val(new bool(a)) {};

    inline explicit DisVar(int a) : Type(type::Integer), val(new int(a)) {};

    inline explicit DisVar(long a) : Type(type::Long), val(new long(a)) {};

    inline explicit DisVar(long long a) : Type(type::LL), val(new long long(a)) {};

    inline explicit DisVar(double a) : Type(type::Double), val(new double(a)) {};

    inline explicit DisVar(long double a) : Type(type::LD), val(new long double(a)) {};

    inline explicit DisVar(string a) : Type(type::String), val(new string(std::move(a))) {};

    //copy constructor
    inline DisVar(const DisVar &other) : Type(other.Type), val(nullptr) {
        switch (other.Type) {
            case Bool:
                this->val = new bool(*reinterpret_cast<bool *>(other.val));
                break;
            case Integer:
                this->val = new int(*reinterpret_cast<int *>(other.val));
                break;
            case Long:
                this->val = new long(*reinterpret_cast<long *>(other.val));
                break;
            case LL:
                this->val = new long long(*reinterpret_cast<long long *>(other.val));
                break;
            case Double:
                this->val = new double(*reinterpret_cast<double *>(other.val));
                break;
            case LD:
                this->val = new long double(*reinterpret_cast<long double *>(other.val));
                break;
            case String:
                this->val = new string(*reinterpret_cast<string *>(other.val));
                break;
            case Untype:
                this->val = nullptr;
                break;
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

    inline DisVar &operator=(const DisVar &a) {
        DisVar tmp(a);
        swap(val, tmp.val);
        swap(Type, tmp.Type);
        return *this;
    };

    /*
    template<typename t>
    inline DisVar &operator=(t a) {
        cout<<"anon"<<endl;
        this->val = new t(a);
        Type = Untype;
        return *this;
    };
*/
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

//work in progress
    DisVar &operator+=(const DisVar &a) {
        switch (this->Type) {
            case Bool:
                switch (a.Type) {
                    case Bool:
                        *this =DisVar(*reinterpret_cast<bool *>(this->val) + *reinterpret_cast<bool *>(a.val));
                        return *this;
                    case Integer:
                        *this =DisVar(*reinterpret_cast<bool *>(this->val) + *reinterpret_cast<int *>(a.val));
                        return *this;
                    case Long:
                        *this =DisVar(*reinterpret_cast<bool *>(this->val) + *reinterpret_cast<long *>(a.val));
                        return *this;
                    case LL:
                        *this =DisVar(*reinterpret_cast<bool *>(this->val) + *reinterpret_cast<long long *>(a.val));
                        return *this;
                    case Double:
                        *this =DisVar(*reinterpret_cast<bool *>(this->val) + *reinterpret_cast<double *>(a.val));
                        return *this;
                    case LD:
                        *this =DisVar(*reinterpret_cast<bool *>(this->val) + *reinterpret_cast<long double *>(a.val));
                        return *this;
                    default:
                        *this = DisVar();
                }
            case Integer:
                switch (a.Type) {
                    case Bool:
                        *this =DisVar(*reinterpret_cast<int *>(this->val) + *reinterpret_cast<bool *>(a.val));
                        return *this;
                    case Integer:
                        *this =DisVar(*reinterpret_cast<int *>(this->val) + *reinterpret_cast<int *>(a.val));
                        return *this;
                    case Long:
                        *this =DisVar(*reinterpret_cast<int *>(this->val) + *reinterpret_cast<long *>(a.val));
                        return *this;
                    case LL:
                        *this =DisVar(*reinterpret_cast<int *>(this->val) + *reinterpret_cast<long long *>(a.val));
                        return *this;
                    case Double:
                        *this =DisVar(*reinterpret_cast<int *>(this->val) + *reinterpret_cast<double *>(a.val));
                        return *this;
                    case LD:
                        *this =DisVar(*reinterpret_cast<int *>(this->val) + *reinterpret_cast<long double *>(a.val));
                        return *this;
                    default:
                        *this = DisVar();
                }
            case Long:
                switch (a.Type) {
                    case Bool:
                        *this =DisVar(*reinterpret_cast<long *>(this->val) + *reinterpret_cast<bool *>(a.val));
                        return *this;
                    case Integer:
                        *this =DisVar(*reinterpret_cast<long *>(this->val) + *reinterpret_cast<int *>(a.val));
                        return *this;
                    case Long:
                        *this =DisVar(*reinterpret_cast<long *>(this->val) + *reinterpret_cast<long *>(a.val));
                        return *this;
                    case LL:
                        *this =DisVar(*reinterpret_cast<long *>(this->val) + *reinterpret_cast<long long *>(a.val));
                        return *this;
                    case Double:
                        *this =DisVar(*reinterpret_cast<long *>(this->val) + *reinterpret_cast<double *>(a.val));
                        return *this;
                    case LD:
                        *this =DisVar(*reinterpret_cast<long *>(this->val) + *reinterpret_cast<long double *>(a.val));
                        return *this;
                    default:
                        *this = DisVar();
                }
            case LL:
                switch (a.Type) {
                    case Bool:
                        *this =DisVar(*reinterpret_cast<long long *>(this->val) + *reinterpret_cast<bool *>(a.val));
                        return *this;
                    case Integer:
                        *this =DisVar(*reinterpret_cast<long long *>(this->val) + *reinterpret_cast<int *>(a.val));
                        return *this;
                    case Long:
                        *this =DisVar(*reinterpret_cast<long long *>(this->val) + *reinterpret_cast<long *>(a.val));
                        return *this;
                    case LL:
                        *this =DisVar(*reinterpret_cast<long long *>(this->val) + *reinterpret_cast<long long *>(a.val));
                        return *this;
                    case Double:
                        *this =DisVar(*reinterpret_cast<long long *>(this->val) + *reinterpret_cast<double *>(a.val));
                        return *this;
                    case LD:
                        *this =DisVar(*reinterpret_cast<long long *>(this->val) + *reinterpret_cast<long double *>(a.val));
                        return *this;
                    default:
                        *this = DisVar();
                }
            case Double:
                switch (a.Type) {
                    case Bool:
                        *this =DisVar(*reinterpret_cast<double *>(this->val) + *reinterpret_cast<bool *>(a.val));
                        return *this;
                    case Integer:
                        *this =DisVar(*reinterpret_cast<double *>(this->val) + *reinterpret_cast<int *>(a.val));
                        return *this;
                    case Long:
                        *this =DisVar(*reinterpret_cast<double *>(this->val) + *reinterpret_cast<long *>(a.val));
                        return *this;
                    case LL:
                        *this =DisVar(*reinterpret_cast<double *>(this->val) + *reinterpret_cast<long long *>(a.val));
                        return *this;
                    case Double:
                        *this =DisVar(*reinterpret_cast<double *>(this->val) + *reinterpret_cast<double *>(a.val));
                        return *this;
                    case LD:
                        *this =DisVar(*reinterpret_cast<double *>(this->val) + *reinterpret_cast<long double *>(a.val));
                        return *this;
                    default:
                        *this = DisVar();
                }
            case LD:
                switch (a.Type) {
                    case Bool:
                        *this =DisVar(*reinterpret_cast<long double *>(this->val) + *reinterpret_cast<bool *>(a.val));
                        return *this;
                    case Integer:
                        *this =DisVar(*reinterpret_cast<long double *>(this->val) + *reinterpret_cast<int *>(a.val));
                        return *this;
                    case Long:
                        *this =DisVar(*reinterpret_cast<long double *>(this->val) + *reinterpret_cast<long *>(a.val));
                        return *this;
                    case LL:
                        *this =DisVar(*reinterpret_cast<long double *>(this->val) + *reinterpret_cast<long long *>(a.val));
                        return *this;
                    case Double:
                        *this =DisVar(*reinterpret_cast<long double *>(this->val) + *reinterpret_cast<double *>(a.val));
                        return *this;
                    case LD:
                        *this =DisVar(*reinterpret_cast<long double *>(this->val) + *reinterpret_cast<long double *>(a.val));
                        return *this;
                    default:
                        *this = DisVar();
                }
            case String:
                switch (a.Type) {
                    case String:
                        *this =DisVar(*reinterpret_cast<string *>(this->val) + *reinterpret_cast<string *>(a.val));
                        return *this;
                    default:
                        *this = DisVar();
                }
            default:
                *this = DisVar();
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

    inline explicit operator bool() const {
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

    inline explicit operator long long() const {
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

    inline explicit operator long double() const {
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

    inline explicit operator string() const {
        switch (Type) {
            default:
                throw bad_cast();
            case String:
                return *reinterpret_cast<string *>(val);
        }
    }

};

