#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int MXN = 15000;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;
    vi A(2 * N);
    rep(i,0,N) cin >> A[i], A[i + N] = A[i];
    vector<int> counts(MXN + 1);
    rep(i,0,N) counts[A[i]]++;

    vector<pair<pii, pii>> allivs;

    for (int num = 1; num <= MXN; ++num) {
        vi pos;
        rep(i,0,N) if (A[i] == num) pos.push_back(i);
        if (pos.empty()) continue;
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

    cerr << "its" << endl;
    sort(all(allivs));
    vector<vector<pii>> dist(MXN + 1);
    for (auto ivs : allivs) {
        pii topush = ivs.first;
        pii toit = ivs.second;
        vector<int> ncounts(MXN + 1);
        for (int i = toit.first; i <= toit.second; ++i) {
            if (++ncounts[A[i]] == counts[A[i]]) {
                dist[A[i]].push_back(topush);
            }
        }
    }
    cerr << "nxits" << endl;

    vector<vector<bool>> equiv(MXN + 1, vector<bool>(MXN + 1));
    vi left(MXN + 1);
    rep(i,0,N) rep(j,0,i) {
        if (equiv[A[i]][A[j]] || A[i] == A[j]) continue;
        equiv[A[i]][A[j]] = equiv[A[j]][A[i]] = true;
        left[A[i]]++; left[A[j]]++;
    }
    vector<int> cnts(MXN + 1);
    rep(i,0,MXN + 1) {
        if (dist[i].empty() || !left[i]) continue;
        // cerr << "for num " << i << endl;
        int pl = 0,
            pr = 0;
        for (auto iv : dist[i]) {
            if (iv.second <= pr) continue;
            // cerr << "can distinguish for interval [" << iv.first << " " << iv.second << ")" << endl;
            while (pl < iv.first) {
                cnts[A[pl]]--;
                pl++;
            }
            while (pr < iv.second) {
                int ot = A[pr];
                if (counts[ot] == ++cnts[ot]) {
                    if (equiv[i][ot]) {
                        equiv[i][ot] = equiv[ot][i] = false;
                        --left[i], --left[ot];
                    }
                    // cerr << "can distinguish from " << ot << endl;
                }
                ++pr;
            }
        }
        while (pl < pr) --cnts[A[pl++]];
    }
    vi res;
    rep(i,0,MXN+1) {
        if (!counts[i] || left[i]) continue;
        res.push_back(i);
    }
    if (res.empty()) cout << "none" << endl;
    for (int i : res) cout << i << endl;
}
