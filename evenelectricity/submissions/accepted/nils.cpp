#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll n,R;
const ll big = 1000000007;
vector<ll> sun, water;

ll maxmin(){
    ll lo = 0;
    ll hi = 4*big;
    while(lo < hi-1){
        ll mid = (lo+hi)/2;
        bool yes = 1;
        ll dam = 0;
        for(int c1 = 0; c1 < n; c1++){
            dam += water[c1];
            ll e = sun[c1];
            if(dam > R){
                e += dam-R;
                dam = R;
            }
            if(e < mid){
                dam -= mid-e;
                e = mid;
            }
            if(dam < 0)yes = 0;
        }
        if(yes){
            lo = mid;
        }
        else{
            hi = mid;
        }
    }
    return lo;
}

ll minmax(){
    ll lo = -1;
    ll hi = 4*big;
    while(lo < hi-1){
        ll mid = (lo+hi)/2;
        bool yes = 1;
        ll dam = 0;
        for(int c1 = 0; c1 < n; c1++){
            dam += water[c1];
            ll e = sun[c1];
            if(dam > R){
                e += dam-R;
                dam = R;
            }
            if(e > mid)yes = 0;
            if(e < mid){
                ll extra = min(mid-e, dam);
                dam -= extra;
            }
        }
        if(dam > 0)yes = 0;
        if(yes){
            hi = mid;
        }
        else{
            lo = mid;
        }
    }
    return hi;
}

int main() {
    cin >> n >> R;
    for(int c1 = 0; c1 < n; c1++){
        ll a,b;
        cin >> a >> b;
        sun.push_back(a);
        water.push_back(b);
    }

    ll ans = minmax()-maxmin();
    cout << ans << "\n";

    return 0;
}
