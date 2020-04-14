#pragma once
#include <vector>
#include <array>
namespace dis{
    template<typename t>
    class vector : public std::vector<t> {
        using std::vector<t>::vector;
    public:
        template<typename s>
        inline vector<t> &operator=(vector<s> a) {
            for (int i = 0; i < a.size(); i++) {
                this->at(i) = a[i];
            }
        };

        template<typename s>
        inline operator vector<s>() {
            vector <s> x;
            x.resize(this->size());
            for (int i = 0; i < this->size(); i++) {
                x[i] = (s) this->at(i);
            }
            return x;
        }
    };
    template<typename t, size_t l>
    class array : public std::array<t,l> {
    public:
        template<typename s, size_t e>
        inline array &operator=(array<s, e> a) {
            for (int i = 0; i < a.size(); i++) {
                this->at(i) = a[i];
            }
        };

        template<typename s, size_t e>
        inline operator array<s,e>() {
            array<s,e> x;
            x.resize(this->size());
            for (int i = 0; i < this->size(); i++) {
                x[i] = (s) this->at(i);
            }
            return x;
        }
    };
}
