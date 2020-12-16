#include "bits/stdc++.h"
using namespace std;

void tower(int n, int from, int to, int tmp){
    if (n == 0) return;
    tower(n-1, from, tmp, to);
    cout << n << " " << from << " " << to << endl;
    tower(n-1, tmp, to, from);
}



int32_t main(){
#ifdef _MY
    freopen("VimProject/input.txt", "r", stdin);
    freopen("VimProject/output.txt", "w", stdout);
#endif

    int n;
    cin >> n;
    tower(n, 1, 3, 2);

    return 0;
}
