#pragma GCC optimize("O3")   //
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define per(i, b, a) for(int i = b - 1; i >= a; i--)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef long double ld;
typedef unsigned long long ull;

unsigned seed = chrono::system_clock::now().time_since_epoch().count();
mt19937 eng(seed);

ll random2(){
    return (1ll << 31ll)*eng()+eng();
}

ll n,m,k,q,T;

const ll big = 1000000007;
const ll big2 = 1000000009;
const ll mod =  998244353;

const int MAXN = 100001;
const int MAXT = 100001;

int t;

bitset<MAXT> subsetsum;
vi slowness;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    //freopen("input.txt","r",stdin);
    //freopen("autput.txt","w",stdout);

    ll a,b,c,d,e;

    cin >> n >> m >> k >> t;
    rep(c1,0,n){
        cin >> a;
        slowness.push_back(a);
    }
    subsetsum[0] = 1;
    rep(c1,0,m){
        cin >> a;
        subsetsum = (subsetsum | (subsetsum << a));
    }
    int fastest = MAXT;
    int n_fast = 0;
    rep(c1,0,n){
        if(slowness[c1] < fastest){
            fastest = slowness[c1];
        }
    }

    int problem_sum = t / fastest;
    while(!subsetsum[problem_sum]){
        problem_sum--;
    }
    int too_slow = big;
    if(problem_sum > 0){
        too_slow = t / problem_sum + 1;
    }

    int slows = 0;
    rep(c1,0,n){
        if(slowness[c1] >= too_slow)slows++;
        if(slowness[c1] < too_slow)n_fast++;
    }
    cout << max((int)k, n_fast) << "\n";

    return 0;
}

