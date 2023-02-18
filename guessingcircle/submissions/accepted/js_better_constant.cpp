#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int MXN = 15000;
bitset<MXN> diff[MXN];
bitset<MXN> dist[MXN];
int counts[MXN];
int cnts[MXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;
    vi A(2 * N);
    rep(i,0,N) cin >> A[i], A[i + N] = A[i];
    unordered_map<int, int> remap;
    unordered_map<int, int> unmap;
    for (int& x : A) {
        if (remap.count(x)) x = remap[x];
        else {
            int nx = sz(remap);
            unmap[nx] = x;
            x = remap[x] = nx;
        }
    }
    rep(i,0,N) counts[A[i]]++;

    vector<pair<pii, pii>> allivs;

    int distinct = 0;
    for (int num = 0; num < MXN; ++num) {
        vi pos;
        rep(i,0,N) if (A[i] == num) pos.push_back(i);
        if (pos.empty()) continue;
        ++distinct;
        pos.push_back(pos.front() + N);
        pii largest(pos[0], pos[1]);
        for (int i = 1; i < sz(pos) - 1; ++i) {
            if (pos[i + 1] - pos[i] > largest.second - largest.first) {
                largest = make_pair(pos[i], pos[i + 1]);
            }
        }
        int len = largest.second - largest.first;
        int extra = len - (N + 2) / 2;
        if (extra <= 0) continue;
        if (largest.second - extra < 0) largest.second += N;
        allivs.push_back(make_pair(pii(largest.second - extra, largest.second), pii(largest.first + 1, largest.first + extra)));
    }

    sort(all(allivs));
    cerr << "tmp" << endl;
    rep(w,0,sz(allivs)) {
        pair<pii,pii> ivs = allivs[w];
        pii topush = ivs.first;
        int tp = (topush.first << 16) | topush.second;
        pii toit = ivs.second;
        for (int i = toit.first; i <= toit.second; ++i) {
            if (++cnts[A[i]] == counts[A[i]]) {
                dist[A[i]][w] = true;
            }
        }
        for (int i = toit.first; i <= toit.second; ++i) {
            --cnts[A[i]];
        }
    }
    cerr << "go" << endl;
    
    rep(i,0,MXN) {
        cnts[i] = -counts[i];
    }
    const int msk = (1 << 16) - 1;
    rep(i,0,MXN) {
        int pl = -1, pr = -1;
        rep(w,0,sz(allivs)) {
        if (!dist[i][w]) continue;
            pii iv = allivs[w].first;
            if (iv.second <= pr) continue;
            while (pl < iv.first) {
                cnts[A[pl]]--;
                pl++;
            }
            for (; pr < iv.second; ++pr) {
                int ot = A[pr];
                if (++cnts[ot] == 0) {
                    diff[i][ot] = diff[ot][i] = true;
                }
            }
        }
        while (pl < pr) --cnts[A[pl++]];
    }
    vi res;
    rep(i,0,MXN) {
        if (!counts[i] || diff[i].count() != distinct - 1) continue;
        res.push_back(unmap[i]);
    }
    sort(all(res));
    if (res.empty()) cout << "none" << endl;
    for (int i : res) cout << i << endl;
    _Exit(0);
}
