#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma,mmx")

// A very quick matrix multiplier mod 10^9+7
#include<bits/stdc++.h>
#define ull unsigned long long
#define ll long long

using namespace std;

const ull MOD = 1000000007L;
const int MAX_MATRIX_SIZE = 3000;

void mult(unsigned int * __restrict__ A, unsigned int * __restrict__ B, unsigned int * __restrict__ C, int Cn, int Am, int Cm)
{
    static ull buf[MAX_MATRIX_SIZE];

    for (int j=0; j<Cm; ++j)
    {
        std::fill(buf,buf+Cn,0);
        int k = 0;
        for (; k+9<=Am; k+=9)
        {
            for (int _k=k; _k<k+9; ++_k)
                for (int i=0; i<Cn; ++i)
                    buf[i] += (ull)A[_k*Cn + i]*B[j*Am +_k];
            for (int i=0; i<Cn; ++i)
                buf[i] -= (-(buf[i] >> 63)) & (MOD * MOD * 9ULL);
        }
        for (; k<Am; ++k)
            for (int i=0; i<Cn; ++i)
                buf[i] += (ull)A[k*Cn + i]*B[j*Am + k];
        for (int i=0; i<Cn; ++i)
            C[j*Cn + i] = buf[i]%MOD;
    }
}


template<typename T>
struct Matrix {
    std::vector<T> data;
    int n;
    int m;
    Matrix(int n, int m) : n(n), m(m), data(n*m) {
    }
    T* operator [](int j) {
        return data.data() + j*n;
    }
    void fill(T val)
    {
        std::fill(data.begin(), data.end(), val);
    }
    Matrix operator* (Matrix& B)
    {
        assert(this->m==B.n);
        Matrix<T> C(this->n,B.m);
        mult((*this)[0],B[0],C[0],C.n,this->m,C.m);
        return C;
    }
    
    void operator<< (Matrix& B)
    {
        assert(this->m==B.n);
        int Cn = this->n;
        int Cm = B.m;
        assert(this->n==Cn);
        assert(this->m==Cm);
        auto C = new T[Cn*Cm];
        mult((*this)[0],B[0],C,Cn,this->m,Cm);
        std::copy(C,C+Cn*Cm,(*this)[0]);
        delete[] C;
    }
    
    void operator>> (Matrix& B)
    {
        assert(this->m==B.n);
        int Cn = this->n;
        int Cm = B.m;
        assert(B.n==Cn);
        assert(B.m==Cm);
        auto C = new T[Cn*Cm];
        mult((*this)[0],B[0],C,Cn,this->m,Cm);
        std::copy(C,C+Cn*Cm,B[0]);
        delete[] C;
    }
};

using Mat = Matrix<unsigned int>;

template<typename T>
T power(T &A, T &B, ull n)
{
    if (n==0)
        return B;
    while (n>1)    {
        if (n&1)
        {
            A>>B;
        }
        A>>A;
        n/=2;
    }
    A>>B;
    return B;
}

// https://judge.yosupo.jp/submission/45054
namespace fastio {
static constexpr int SZ = 1 << 17;
char ibuf[SZ], obuf[SZ];
int pil = 0, pir = 0, por = 0;

struct Pre {
  char num[40000];
  constexpr Pre() : num() {
    for (int i = 0; i < 10000; i++) {
      int n = i;
      for (int j = 3; j >= 0; j--) {
        num[i * 4 + j] = n % 10 + '0';
        n /= 10;
      }
    }
  }
} constexpr pre;

inline void load() {
  memcpy(ibuf, ibuf + pil, pir - pil);
  pir = pir - pil + fread(ibuf + pir - pil, 1, SZ - pir + pil, stdin);
  pil = 0;
}
inline void flush() {
  fwrite(obuf, 1, por, stdout);
  por = 0;
}

inline void skip_space() {
  if (pil + 32 > pir) load();
  while (ibuf[pil] <= ' ') pil++;
}

inline void rd(char &c) {
  if (pil + 32 > pir) load();
  c = ibuf[pil++];
}
template <typename T>
inline void rd(T &x) {
  if (pil + 32 > pir) load();
  char c;
  do c = ibuf[pil++];
  while (c < '-');
  [[maybe_unused]] bool minus = false;
  if constexpr (is_signed<T>::value == true) {
    if (c == '-') minus = true, c = ibuf[pil++];
  }
  x = 0;
  while (c >= '0') {
    x = x * 10 + (c & 15);
    c = ibuf[pil++];
  }
  if constexpr (is_signed<T>::value == true) {
    if (minus) x = -x;
  }
}
inline void rd() {}
template <typename Head, typename... Tail>
inline void rd(Head &head, Tail &...tail) {
  rd(head);
  rd(tail...);
}

inline void wt(char c) {
  if (por > SZ - 32) flush();
  obuf[por++] = c;
}
inline void wt(bool b) {
  if (por > SZ - 32) flush();
  obuf[por++] = b ? '1' : '0';
}
template <typename T>
inline void wt(T x) {
  if (por > SZ - 32) flush();
  if (!x) {
    obuf[por++] = '0';
    return;
  }
  if constexpr (is_signed<T>::value == true) {
    if (x < 0) obuf[por++] = '-', x = -x;
  }
  int i = 12;
  char buf[16];
  while (x >= 10000) {
    memcpy(buf + i, pre.num + (x % 10000) * 4, 4);
    x /= 10000;
    i -= 4;
  }
  if (x < 100) {
    if (x < 10) {
      obuf[por] = '0' + x;
      ++por;
    } else {
      uint32_t q = (uint32_t(x) * 205) >> 11;
      uint32_t r = uint32_t(x) - q * 10;
      obuf[por] = '0' + q;
      obuf[por + 1] = '0' + r;
      por += 2;
    }
  } else {
    if (x < 1000) {
      memcpy(obuf + por, pre.num + (x << 2) + 1, 3);
      por += 3;
    } else {
      memcpy(obuf + por, pre.num + (x << 2), 4);
      por += 4;
    }
  }
  memcpy(obuf + por, buf + i + 4, 12 - i);
  por += 12 - i;
}

inline void wt() {}
template <typename Head, typename... Tail>
inline void wt(Head &&head, Tail &&...tail) {
  wt(head);
  wt(forward<Tail>(tail)...);
}
template <typename... Args>
inline void wtn(Args &&...x) {
  wt(forward<Args>(x)...);
  wt('\n');
}

struct Dummy {
  Dummy() { atexit(flush); }
} dummy;

}  // namespace fastio
using fastio::rd;
using fastio::skip_space;
using fastio::wt;
using fastio::wtn;




int main()
{
    cin.tie(0)->sync_with_stdio(false);
    int n,I,J;
    rd(n, I, J);
    --I; --J;

    vector<ll> seq(2 * n + 1);
    for (int i=1; i < 2 * n; ++i)
        rd(seq[i]);

    Mat A(n,n);
    for (int i=0; i<n; ++i)
        for (int j=0; j<n; ++j)
            rd(A[j][i]);

    Mat ans(n,1);
    ans.fill(0);
    ans[0][J] = 1;
     
    ans = power(A, ans, 2 * n);
    
    wt(ans[0][I]); wt('\n');
}
