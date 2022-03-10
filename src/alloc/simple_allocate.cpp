#include "simple_allocate.h"
#include <vector>
#include <iostream>
using namespace std;
int main(){
    int arr[5] = {0, 1, 2, 3, 4};
    unsigned int i;
    vector<int, SIMPLE_STL::simple_allocate<int> > vec(arr, arr + 5);
    for(int i = 0; i < vec.size(); ++i)
        cout << vec[i] << ' ';
    cout << endl;
}