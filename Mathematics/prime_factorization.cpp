#include <bits/stdc++.h>

/*--------------------------------------------------------*/
//nの素因数とその個数のpairのmapを返す
template<typename T_n>
std::map<T_n, int> prime_factor(T_n n) {
    std::map<T_n, int> ret;
    for(T_n i = 2; i*i <= n; i++){
        while(n % i == 0){
            ret[i]++;
            n /= i;
        }
    }
    if(n != 1) ret[n] = 1;
    return ret;
}