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
                        possL[a][b/64] |= 1ULL << (b % 64);
                    if (dR <= dL)
                        possR[a][b/64] |= 1ULL << (b % 64);
                }
    vector<int> ans;
    for (auto p: num_idx) {
        auto &[num, idx] = p;

        vector<word> same(words, 0);
        for (int k = 0; k < words; ++k)
            same[k] |= possL[0][k] | possR[0][k];
        same[idx/64] &= ~(1ULL<<(idx%64));

        int max_w = words, min_w = 0;
        for (int j = 0; max_w && j < m; ++j) {
            bool L = possL[j][idx/64] & (1ULL<<(idx % 64));
            bool R = possR[j][idx/64] & (1ULL<<(idx % 64));
            if (L && R) continue;
            auto &poss = L ? possL[j] : possR[j];
            for (int k = min_w; k < max_w; ++k)
                same[k] &= poss[k];
            while (max_w > min_w && !same[max_w-1]) --max_w;
            while (min_w < max_w && !same[min_w]) ++min_w;
        }
        if (max_w == min_w) ans.push_back(num);
    }
    if (ans.empty())
        printf("none\n");
    else {
        sort(ans.begin(), ans.end());
        for (int x: ans)
            printf("%d\n", x);
    }
}
