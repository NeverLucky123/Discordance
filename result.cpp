#include "DisVar.h"
#include <algorithm>
#include "DisVector.h"
// C++ implementation of the approach
using namespace std;
int cntElements(dis::vector<int> arr)
{
    // To store a copy of the
    // original array
    vector<int> copy_arr=arr;

    // To store the required count
    int count = 0;
    // Sort the original array
    sort(arr.begin(), arr.end());
    for (int i=0;i<arr.size();i++){
        if (arr[i] != copy_arr[i]){
            count++;
        }
    }
    // If current element was not
    // at the right position
    return count;
}

// Driver code
int main()
{
    dis::vector<DisVar> arr={1, 2, 6, 2, 4, 5};
    cout<<cntElements(arr);

    return 0;
}