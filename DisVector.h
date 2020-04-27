#pragma once
#include <vector>
#include <deque>
namespace discordance{
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
        discordance::vector<t> slice(int first, int last){
            if(last<0){
                last=this->size()+last;
            }
            if(first<0){
                first=this->size()+first;
            }
            if(first<0||last<0){
                throw std::invalid_argument("index out of range");
            } else if(last<first){
                throw std::invalid_argument("last arguement before first arguement: slice invalid");
            }
            discordance::vector<t> dst(last-first);
            std::copy(this->begin()+first, this->begin()+last, dst.begin());
            return dst;
        }
    };

    template<typename t>
    class deque : public std::deque<t> {
        using std::deque<t>::deque;
    public:
        template<typename s>
        inline deque<t> &operator=(deque<s> a) {
            for (int i = 0; i < a.size(); i++) {
                this->at(i) = a[i];
            }
        };

        template<typename s>
        inline operator vector<s>() {
            deque <s> x;
            x.resize(this->size());
            for (int i = 0; i < this->size(); i++) {
                x[i] = (s) this->at(i);
            }
            return x;
        }
        template<typename s>
        inline operator deque<s>(){
            deque <s> x;
            x.resize(this->size());
            for (int i = 0; i < this->size(); i++) {
                x[i] = (s) this->at(i);
            }
            return x;
        }
        discordance::vector<t> slice(int first, int last){
            if(last<0){
                last=this->size()+last;
            }
            if(first<0){
                first=this->size()+first;
            }
            if(first<0||last<0){
                throw std::invalid_argument("index out of range");
            } else if(last<first){
                throw std::invalid_argument("last arguement before first arguement: slice invalid");
            }
            discordance::deque<t> dst(last-first);
            std::copy(this->begin()+first, this->begin()+last, dst.begin());
            return dst;
        }
    };
}
