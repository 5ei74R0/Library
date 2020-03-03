#include <bits/stdc++.h>

/* Segment Tree -----------*/
template <typename M>
class SegmentTree {
    using F = std::function< M(M, M) >;
private:
    int n;
    F func;
    M M_init;
    std::vector<M> t;
public:
    // constructor
    SegmentTree(int &n, F func, const M &M_init): n(n), func(func), M_init(M_init) { t.assign(2*n, M_init); }
    SegmentTree(std::vector<M> &vec, F func, const M &M_init): n(vec.size()), func(func), M_init(M_init) {
        t.assign(2*vec.size(), M_init);
        for(int i = 0; i < vec.size(); ++i) t[i+vec.size()] = vec[i];
    }

    void build() {  // build segment tree
        for(int i = n-1; i > 1; --i) t[i] = func(t[i<<1], t[i<<1|1]);
    }
    void modify(int p, M val) {  // update value at position p
        for(t[p += n] = val; p > 1; p >>= 1) t[p>>1] = func(t[p], t[p^1]);
    }
    M query(int l, int r) {  // reply to query [l, r)
        M resl = M_init, resr = M_init;
        for(l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if(l & 1) resl = func(resl, t[l++]);
            if(r & 1) resr = func(t[--r], resr);
        }
        return func(resl, resr);
    }
    M &operator[](const int &k) &{return t[k+n];}
    const M &operator[](const int &k) const& {return t[k+n];}
};



/*  verified on ABC 125 - C -> https://atcoder.jp/contests/abc125/tasks/abc125_c  */


long long GCD(long long a, long long b) { return (b ? GCD(b, a%b) : a); }

signed main(){
    using namespace std;

    // input and build
    int n; cin >> n;
    SegmentTree<int> a(n, [](int p, int q){ return (q ? GCD(q, p%q) : p);}, 0LL);
    for(int i = 0; i < n; ++i) cin >> a[i];
    a.build();

    // solve
    int ans = -1;
    for (int i = 0; i < n; ++i) {
        if(i == 0) ans = max(ans, a.query(1, n));
        else if(i == n-1) ans = max(ans, a.query(0, n-1));
        else ans = max(ans, GCD(a.query(0,i), a.query(i+1, n)));
    }

    // output
    cout << ans << '\n';
}