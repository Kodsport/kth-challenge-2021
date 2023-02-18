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
    int m = num_idx.size();
    int words = (m+63)/64;
    vector<vector<word>> possL(m, vector<word>(words, 0));
    vector<vector<word>> possR(m, vector<word>(words, 0));
    for (int a = 0; a < m; ++a)
        for (int b = 0; b < m; ++b)
            for (int i: positions[a])
                for (int j: positions[b]) {
                    int dR = (j-i+n) % n, dL = (i-j+n) % n;
                    if (dL <= dR)
                        possL[a][b/64] |= word(1) << (b % 64);
                    if (dR <= dL)
                        possR[a][b/64] |= word(1) << (b % 64);
                }
    vector<int> ans;
    for (auto p: num_idx) {
        auto &[num, idx] = p;
        bool ok = true;

        for (int j = 0; ok && j < m; ++j) {
            if (j == idx) continue;
            bool same = true;
            for (int k = 0; same && k < words; ++k)
                same &= ((possL[idx][k] & possL[j][k]) | (possR[idx][k] & possR[j][k])) == (possL[idx][k] | possR[idx][k]);
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
