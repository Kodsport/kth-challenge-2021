#include <bits/stdc++.h>
using namespace std;

int main() {
    int n,m;
    cin >> n >> m;

    if(m < n-1 || m > 2*n-3){
        cout << "-1\n";
        return 0;
    }
    for(int c1 = 0; c1 < n-1; c1++){
        cout << c1+1 << " " << c1+2 << "\n";
    }
    for(int c1 = 0; c1 < m-n+1; c1++){
        cout << c1+1 << " " << c1+3 << "\n";
    }

    return 0;
}
