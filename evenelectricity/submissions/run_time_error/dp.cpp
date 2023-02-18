#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll n,R;
const ll big = 1000000007;
vector<ll> sun, water;

const int lim = 201;
int DP[lim][lim][lim] = {0};

int dp(){
    for(int i = n-1; i >= 0; i--){
        for(int mi = 0; mi < lim; mi++){
            for(int dam = 0; dam < lim; dam++){
                int dam2 = dam + water[i];
                int e = sun[i];
                if(i == n-1){
                    e += dam2;
                    if(e < mi){
                        DP[i][mi][dam] = big;
                    }
                    else{
                        DP[i][mi][dam] = e;
                    }
                }
                else{
                    DP[i][mi][dam] = big;
                    for(int dam3 = 0; dam3 <= min(ll(dam2),R); dam3++){
                        int e2 = e + dam2 - dam3;
                        if(e2 < mi)continue;
                        int temp = max(e2, DP[i+1][mi][dam3]);
                        DP[i][mi][dam] = min(DP[i][mi][dam], temp);
                    }
                }
            }
        }
    }
    int ans = big;
    for(int c1 = 0; c1 < lim; c1++){
        ans = min(ans, DP[0][c1][0] - c1);
    }
    return ans;
}

int main() {
    cin >> n >> R;
    assert(n < lim);
    for(int c1 = 0; c1 < n; c1++){
        ll a,b;
        cin >> a >> b;
        sun.push_back(a);
        water.push_back(b);
    }

    ll ans = dp();
    cout << ans << "\n";

    return 0;
}
