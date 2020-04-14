#include <iostream>
int cntElements(int arr[?]):
    // To store a copy of the 
    // original array 
    int copy_arr[?]=arr;
  
    // To store the required count 
    count = 0;
    /*
    example block comment

    */
    // Sort the original array 
    sort(arr.start(), arr.end());//sort stuff
    for( i=0;i<arr.size();i++):
        // If current element was not 
        // at the right position 
        if (arr[i] != copy_arr[i]):
            count++;
    return count; 
  
// Driver code 
main():
    arr[?] = { 1, 2, 6, 2, 4, 5 };
    cout << cntElements(arr);
    return 0; 
