#include<bits/stdc++.h>
using namespace std;

typedef unsigned long long word;

int main(void) {
    int n;
    scanf("%d", &n);
    vector<int> circle(n);
    unordered_map<int, int> num_idx;
    vector<vector<int>> positions;
    for (int i = 0; i < n; ++i) {
        scanf("%d", &circle[i]);
        if (num_idx.find(circle[i]) == num_idx.end()) {
            num_idx[circle[i]] = num_idx.size();
            positions.push_back({});
        }
        positions[num_idx[circle[i]]].push_back(i);
    }
    auto in_ival = [n](int l, int x, int r) {
                       while (r < l) r += n;
                       while (x < l) x += n;
                       return x <= r;
                   };
    auto overlap = [n](pair<int, int> I, pair<int, int> J) {
                       if (I.first == -1 || J.first == -1) return false;
                       while (I.second < I.first) I.second += n;
                       while (J.second < J.first) J.second += n;
                       while (I.second < J.first) I.first += n, I.second += n;
                       while (J.second < I.first) J.first += n, J.second += n;
                       return I.second >= J.first;
                   };
    int m = num_idx.size();
    vector<int> prev(n), next(n);
    for (int i = 0; i < m; ++i) {
        int x = positions[i].back();
        for (int y: positions[i]) {
            prev[y] = x;
            next[x] = y;
            x = y;
        }
    }
    vector<pair<int,int>> excludeL(m, make_pair(-1, 0));
    vector<pair<int,int>> excludeR(m, make_pair(-1, 0));
    auto fix_ival = [&](int l, int r) {
                        l = (l + n) % n;
                        r = (r + n) % n;
                        while (l != r && !in_ival(l, prev[l], r)) l = (l+1) % n;
                        while (l != r && !in_ival(l, next[r], r)) r = (r+n-1) % n;
                        if (!in_ival(l, prev[l], r)) return make_pair(-1, 0);
                        return make_pair(l, r);
                    };

    for (int i = 0; i < m; ++i) {
        if (positions[i].size() == 1) {
            int x = positions[i].front();
            excludeL[i] = fix_ival(x - (n-1)/2, x - 1);
            excludeR[i] = fix_ival(x + 1, x + (n-1)/2);
        } else {
            for (int b = 0, a = positions[i].size()-1; b < positions[i].size(); a = b++) {
                int x = positions[i][a], y = positions[i][b];
                if ((y-x+n) % n > n/2+1) {
                    excludeL[i] = fix_ival(x + n/2 + 1, y - 1);
                    excludeR[i] = fix_ival(x + 1, y - n/2 - 1);
                    break;
                }
            }
        }
    }

    vector<int> ans;
    for (auto p: num_idx) {
        auto &[num, i] = p;
        bool ok = true;
        auto exL = excludeL[i], exR = excludeR[i];

        for (int j = 0; ok && j < m; ++j) {
            if (j == i) continue;
            bool diff = overlap(excludeL[i], excludeR[j]) || overlap(excludeR[i], excludeL[j]);
            ok &= diff;
        }
        if (ok) ans.push_back(num);
    }
    if (ans.empty())
        printf("none\n");
    else {
        sort(ans.begin(), ans.end());
        for (int x: ans)
            printf("%d\n", x);
    }
}
