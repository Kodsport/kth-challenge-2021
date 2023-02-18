#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int NUMS = 10001;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);

  int N;
  cin >> N;
  vi A(N);
  rep(i,0,N) cin >> A[i];
  
  vector<vi> pos(NUMS);
  rep(i,0,N) {
    pos[A[i]].push_back(i);
  }

  vector<vector<bool>> L(NUMS, vector<bool>(NUMS));
  vector<vector<bool>> R(NUMS, vector<bool>(NUMS));
  rep(i,0,NUMS) {
    if (pos[i].empty()) continue;
    rep(j,0,NUMS) {
      if (pos[j].empty() || i == j) continue;
      for (int a : pos[i]) {
        for (int b : pos[j]) {
          if (b < a) b += N;
          if (b - a <= N / 2) L[i][j] = true;
          if (N - (b - a) <= N / 2) R[i][j] = true;
        }
      }
    }
  }

  ll cost = 0;
  vi res;
  rep(i,0,NUMS) {
    if (pos[i].empty()) continue;
    bool dup = false;
    rep(j,0,NUMS) {
      if (pos[j].empty() || i == j) continue;
      rep(k,0,NUMS) {
        if (L[i][k] && !R[i][k] && R[j][k] && !L[j][k]) goto nx;
        if (!L[i][k] && R[i][k] && !R[j][k] && L[j][k]) goto nx;
        cost++;
      }
      dup = true;
      break;
      nx:;
    }
    if (!dup) res.push_back(i);
  }
  cerr << "cost: " << double(cost) / N / N << endl;
  if (res.empty()) cout << "none" << endl;
  else {
    for (int x : res) cout << x << endl;
  }

}
