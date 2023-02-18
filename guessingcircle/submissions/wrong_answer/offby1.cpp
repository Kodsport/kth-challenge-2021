#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int MXN = 5000;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;
    vi A(N);
    rep(i,0,N) cin >> A[i];
    map<int, int> counts;
    for (int a : A) counts[a]++;

    map<int, vector<pii>> dist;
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
        int extra = len - (N + 1) / 2;
        if (extra <= 0) continue;
        //cerr << "for num " << num << " iv is " << largest.first + 1 << "-" << largest.first + extra << " and " << largest.second - extra << "-" << largest.second - 1 << endl;

        map<int, int> ncounts;
        for (int i = largest.first + 1; i <= largest.first + extra; ++i) {
            ncounts[A[i % N]]++;
        }
        for (auto p : ncounts) {
            if (largest.second - extra < 0) largest.second += N;
            if (p.second == counts[p.first]) dist[p.first].emplace_back(largest.second - extra, largest.second);
        }
    }
    
    vector<vector<bool>> equiv(MXN + 1, vector<bool>(MXN + 1));
    for (int a : A) for (int b : A) if (a != b) equiv[a][b] = true;
    for (auto it : dist) {
        //cerr << "for num " << it.first << endl;
        sort(all(it.second));

        map<int, int> cnts;
        int pl = 0,
            pr = 0;
        for (auto iv : it.second) {
            if (iv.second <= pr) continue;
            //cerr << "can distinguish for interval [" << iv.first << " " << iv.second << ")" << endl;
            if (iv.first >= pr) {
                cnts.clear();
                pl = pr = iv.first;
            }
            while (pl < iv.first) {
                cnts[A[pl % N]]--;
                pl++;
            }
            while (pr < iv.second) {
                if (counts[A[pr % N]] == ++cnts[A[pr % N]]) {
                    int ot = A[pr % N];
                    equiv[it.first][ot] = equiv[ot][it.first] = false;
                    //cerr << "can distinguish from " << ot << endl;
                }
                ++pr;
            }
        }
    }
    vi res;
    for (auto it : counts) {
        int i = it.first;
        if (find(all(equiv[i]), true) == equiv[i].end()) res.push_back(i);
    }
    if (res.empty()) cout << "none" << endl;
    for (int i : res) cout << i << endl;
}
