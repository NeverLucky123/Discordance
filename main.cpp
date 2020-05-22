#include "Discordance.h"
#include <cmath>
#include <cstring>

using namespace std;
using namespace discordance;
using discordance::deque;
discordance::var return_any (const discordance::var& any)
{
    return any;
}
int main ()
{
    class apple{
        string color="green";
        discordance::var  weight="2kg";
        apple(){
            weight=2;
            weight=2.0+weight;
            cout<<weight;
        }
    };

    discordance::deque<std::string > desserts(0);
    desserts={"apple pie", "chocolate cake", "waffles", "cupcakes"};
    discordance::vector<std::string > colors(5);
    colors={"green", "blue", "magenta", "teal", "crimson"};
    colors=desserts;
    discordance::deque<discordance::var  > bucket={2.0, "chocolate milk", "15789"};
    discordance::vector<discordance::var> small_bucket= bucket.slice(1,2);
    for ( auto item : small_bucket ){
        cout<<item<<endl;
    }
    /*
    discordance::deque<discordance::vector<int >> numbers={
            {1,2,3,4,5,6,7,8,9,10},
            {-1,-2,-3,-4,-5,-6,-7,-8,-9,-10}
    };
    for ( auto row : numbers ){
        for ( auto column : row ){
            cout<<column<<endl;
        }
    }

    discordance::deque<discordance::var  > bucket={2.0, "chocolate milk", "15789"};
    if ( bucket[0]==2.0 ){
        cout<<bucket[0]<<endl;
    }
    else if ( bucket[1]=="chocolate milk" ){
        cout<<bucket[1]<<endl;
    }
    else{
        cout<<bucket[2]<<endl;
    }
    for ( auto item : bucket )
        cout<<item<<endl;
    auto small_bucket=bucket.slice(1,2);
    for ( auto item : small_bucket )
        cout<<item<<endl;
    cout<<return_any(2.0)<<endl;
    cout<<return_any(5)<<endl;
    cout<<return_any("hello")<<endl;*/
    return 0;
}

