
#include "bits/stdc++.h"
using namespace std;

vector<int> a = {1,2,3,4,5};

int my_lower_bound(int x){
    //finds index of first element that >= x
    int l = 0;
    int r = a.size();
    while(l < r){
        int mid = (l+r)/2;
        if (a[mid] < x)
            l = mid + 1;
        else
            r = mid;
    }
    return r;
}

int my_upper_bound(int x){
    //finds index of first element that > x
    int l = 0;
    int r = a.size();
    while(l < r){
        int mid = (l+r)/2;
        if (a[mid] <= x)
            l = mid + 1;
        else
            r = mid;
    }
    return r;
}

int main(){
    cout << my_lower_bound(4) << endl;
    cout << my_upper_bound(4) << endl;

    return 0;
}
