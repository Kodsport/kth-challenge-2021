#include<bits/stdc++.h>
using namespace std;

#pragma GCC optimize("O3")
#pragma GCC target("avx,avx2,fma,mmx")
#pragma GCC optimize("unroll-loops")

const int N = 15000;
typedef unsigned long long word;

int main(void) {
    int n;
    cin >> n;
    int nhalf = n / 2;

    vector<int> A(n);
    for (auto &a : A) {
        cin >> a;
        --a;
    }

    vector<bitset<N>> L(N);
    vector<bitset<N>> R(N);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if ((i - j + n) % n <= nhalf)
                L[A[i]][A[j]] = R[A[j]][A[i]] = 1;
        }
    }

    for (int x = 0; x < N; ++x) {
        bitset<N> both = L[x] & R[x];
        both.flip();
        L[x] &= both;
        R[x] &= both;
    }

    vector<bitset<N>> is_diff(N);
    for (int y = 0; y < N; ++y) {
        for (int x = 0; x < N; ++x) {
            if (L[y][x])
                is_diff[x] |= R[y];
        }
    }

    for (int x1 = 0; x1 < N; ++x1)
        for (int x2 = 0; x2 < N; ++x2)
            if (is_diff[x2][x1])
                is_diff[x1][x2] = 1;

    sort(A.begin(),A.end());
    A.erase(unique(A.begin(), A.end()), A.end());

    vector<int> out;
    for (auto x1 : A) {
        bool is_unique = true;
        for (auto x2 : A) {
            is_unique &= x1 == x2 || is_diff[x1][x2];
        }
        if (is_unique)
            out.push_back(x1);
    }

    if (out.size() > 0) {
        for (auto x : out)
            cout << x + 1 << ' ';
        cout << "\n";
    } else {
        cout << "none\n";
    }
}
