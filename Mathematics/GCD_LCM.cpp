#include <bits/stdc++.h>
using namespace std;

/*Calculate GCD, LCM =============================*/
long long GCD(long long a, long long b){
    return (b ? GCD(b, a%b) : a);
}
long long LCM(long long a, long long b) {
    long long g = GCD(a,b);
    return (a/g) * (b/g) * g;  // オーバーフローを避ける
}
