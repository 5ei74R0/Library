#include <bits/stdc++.h>

/* Lazy Segment Tree -----------*/
template <typename M>
class LazySegmentTree {
    using F = std::function<M(M, M)>;
    using G = std::function<M(M, int)>;
private:
    int n, h;
    std::vector<M> t, d;
    const F func;
    const G func2;
    const M M_init;
    inline void calc(int p, int length) {
        if(d[p] == M_init) t[p] = func(t[p<<1], t[p<<1|1]);
        else t[p] = func2(d[p], length);
    }
    inline void apply(int p, M value, int length) {
        t[p] = func2(value, length);
        if(p < n) d[p] = value;
    }
    void _build_(int l, int r) {
        int length = 2;
        for(l += n, r += n-1; l > 1; length <<= 1) {
            l >>= 1; r >>= 1;
            for(int i = r; i >= l; --i) calc(i, length);
        }
    }
    void push(int l, int r) {
        int s = h, length = 1 << (h-1);
        for(l += n, r += n-1; s > 0; --s, length >>= 1) {
            for(int i = (l >> s); i <= (r >> s); ++i) if(d[i] != M_init) {
                    apply(i<<1, d[i], length);
                    apply(i<<1|1, d[i], length);
                    d[i] = M_init;
                }
        }
    }
public:
    // constructor
    LazySegmentTree(int N,F Combiner, G Func_for_segment, M M_init):
            n(N), func(Combiner), func2(Func_for_segment), M_init(M_init)
    {
        h = 0; int m = 1; while(m <= n) {m <<= 1; ++h;}
        t.assign(2*n, M_init);
        d.assign(n, M_init);
    }
    // set value at position p
    void set(int &p, const M &value) {t[p+n] = value;}
    // build
    void build() { _build_(0,n); }

    void modify(int l, int r, M value) {  // update value in [l, r)
        if(value == M_init) return;
        push(l, l+1);
        push(r-1, r);
        bool canl = false, canr = false;
        int length = 1;
        for(l += n, r += n; l < r; l >>= 1, r >>= 1, length <<= 1) {
            if(canl) calc(l-1, length);
            if(canr) calc(r, length);
            if(l & 1) apply(l++, value, length), canl = true;
            if(r & 1) apply(--r, value, length), canr = true;
        }
        for(--l; r > 0; l >>= 1, r >>= 1, length <<= 1) {
            if(canl) calc(l, length);
            if(canr && (!canl || l != r)) calc(r, length);
        }
    }

    M query(int l, int r) {  // reply to query in [l, r)
        push(l, l+1);
        push(r-1, r);
        M resl = M_init, resr = M_init;
        for(l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if(l & 1) resl = func(resl, t[l++]);
            if(r & 1) resr = func(t[--r], resr);
        }
        return func(resl, resr);
    }
    M operator[](int &k) const { return query(k, k+1); }
};



/* assignment modifications and range sum queries */


signed main(){
    using namespace std;
    int _StartTime_ = clock();

    // input and build
    int n; cin >> n;
    LazySegmentTree<int> a(n, [](int a,int b){ return a+b;}, [](int p, int k){ return p*k;}, 0);
    for(int i = 0; i < n; i++) {int p; cin >> p; a.set(i,p);}

    // modify and reply to query
    for(int i = 0; i < n; i++) {
        a.modify(i, min(n,i+3) , i);
        for(int i = 0; i < n; ++i ) cout << a[i] << (i==n-1 ? '\n' : ' ');
        cout << a.query(0,i+1) << '\n';
    }

    printf("ExecutionTime : %d /ms\n",1000*(int)((clock()-_StartTime_)/CLOCKS_PER_SEC));
}