#include <bits/stdc++.h>
#define debug(x) cout <<"DEBUG"<<" "<< #x << ":" << x << '\n'
#define rep(i,n) for(int_fast32_t i = 0; i < ((int_fast32_t)(n)); i++)   // 0-indexed up
#define rep1(i,n) for(int_fast32_t i = 1; i <= ((int_fast32_t)(n)); i++) // 1-indexed up
#define all(x) (x).begin(),(x).end()



/* Test */
using namespace std;

template<typename T>
using vec = vector<T>;
using i32 = int_fast32_t; using i64 = int_fast64_t;
using u32 = uint_fast32_t; using u64 = uint_fast64_t;
using ll = long long; using ld = long double;
using vi = vec<int_fast32_t>;
using vl = vec<int_fast64_t>;
using vii = vec<vi>;
using PII = pair<int_fast32_t, int_fast32_t>;
template<class T>
using maxheap = std::priority_queue<T>;
template<class T>
using minheap = std::priority_queue<T, std::vector<T>, std::greater<T>>;
template<class T,class U> inline bool chmax(T &a, const U &b){if(a<b){a=b;return 1;}return 0;}
template<class T,class U> inline bool chmin(T &a, const U &b){if(a>b){a=b;return 1;}return 0;}
constexpr ll infll = (1LL<<62)-1;
constexpr int inf = (1<<30)-1;

signed main(){
    double START_TIME = clock();
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
//    cout << fixed << setprecision(15);



    printf("ElapsedTime: %5.3f ms\n",1000*((clock()-START_TIME)/CLOCKS_PER_SEC));
}

