#include<bits/stdc++.h>
using namespace std;

typedef unsigned long long word;

int main(void) {
    int n;
    scanf("%d", &n);
    if (n % 2 == 0) {
        printf("none\n");
        return 0;
    }
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
    int m = num_idx.size();
    if (m == n) {
        sort(circle.begin(), circle.end());
        for (int c: circle)
            printf("%d\n", c);
        return 0;
    }
    int words = (m+63)/64;
    vector<vector<word>> possL(m, vector<word>(words, 0));
    vector<vector<word>> possR(m, vector<word>(words, 0));
    for (int a = 0; a < m; ++a) {
        if (m % 64) {
            possL[a][words-1] |= ~((1ULL<<(m%64)) - 1);
            possR[a][words-1] |= ~((1ULL<<(m%64)) - 1);
        }
        for (int b = 0; b < m; ++b)
            for (int i: positions[a])
                for (int j: positions[b]) {
                    int dR = (j-i+n) % n, dL = (i-j+n) % n;
                    if (dL <= dR)
                        possL[a][b/64] |= 1ULL << (b % 64);
                    if (dR <= dL)
                        possR[a][b/64] |= 1ULL << (b % 64);
                }
    }
    vector<int> ans;
    vector<int> bad(m, false);
    vector<vector<int>> diff(m, vector<int>(m, false));
    for (int i = 0; i < m; ++i) diff[i][i] = true;
    for (auto p: num_idx) {
        auto &[num, idx] = p;
        bool ok = true;
        if (bad[idx]) continue;

        for (int j = 0; ok && j < m; ++j) {
            if (diff[idx][j]) continue;
            bool same = true;
            for (int k = 0; same && k < words; ++k)
                same &= ((possL[idx][k] & possL[j][k]) | (possR[idx][k] & possR[j][k])) == ~0;
            if (same) bad[idx] = bad[j] = true;
            else diff[idx][j] = diff[j][idx] = true;
            ok &= !same;
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
