//
// Created by OtsuKotsu on 2020/06/18.
//
//  Sieve
//  素数篩
//
//
//  5以上の素数は 6p+1 か 6p-1 で表せることを利用して高速化を図った素数篩。
//  なおコンパイル時計算で構築を行う。
//  container[p][0] := 6p-1が素数かどうか
//  container[p][1] := 6p+1が素数かどうか
//
//  containerは直接操作してもよいが、基本的にはis_primeを使用する想定。
//
//
//  <構築実行時間目安>
//  (AtCoderコードテストで測定)
//
//  n = 1e5 :  6ms
//  n = 1e6 :  9ms
//  n = 1e7 :  33ms
//  n = 5e7 :  175ms
//
//  n = 1e8 :  481ms ~ 683ms
//
//  n = 1e9 :  8361ms ~ 8729ms
//

#include <bits/stdc++.h>

template<size_t MAX_N>
struct Sieve {
    using i64 = int_fast64_t;
    bool container[(MAX_N+11)/6][2];

    constexpr Sieve(): container() {
        for(i64 i = 1; i < (MAX_N+11)/6; ++i) {
            container[i][0] = container[i][1] = 1;
        }

        for(i64 i = 1; i < (MAX_N+11)/6; ++i) {
            if(container[i][0]) {  // 6i - 1 is prime
                for(i64 p = 1; p < (MAX_N+11)/6; ++p) {
                    i64 idx1 = 6*i*p + i - p;
                    i64 idx2 = 6*i*p - i - p;
                    if(idx2 >= (MAX_N+11)/6) break;
                    container[idx2][1] = false;
                    if(idx1 >= (MAX_N+11)/6) continue;
                    container[idx1][0] = false;
                }
            }
            if(container[i][1]) {  // 6i + 1 is prime
                for(i64 p = 1; p < (MAX_N+11)/6; ++p) {
                    i64 idx1 = 6*i*p + i + p;
                    i64 idx2 = 6*i*p - i + p;
                    if(idx2 >= (MAX_N+11)/6) break;
                    container[idx2][0] = false;
                    if(idx1 >= (MAX_N+11)/6) continue;
                    container[idx1][1] = false;
                }
            }
        }
    }

    bool is_prime(i64 num) {  // num > 0
        if(num == 2 || num == 3) return true;
        if((num+1)%6 == 0) return (container[(num+1)/6][0]);
        if((num-1)%6 == 0) return (container[(num-1)/6][1]);
        return false;
    }
};


/* Use ==================================================*/
constexpr size_t n = 2e6;

signed main(){
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    Sieve<n> sieve;

    for(int i = 1; i < n; ++i) {
        if(sieve.is_prime(i)) std::cout << i << '\n';
    }

    std::cout << '\n';
    std::cout << "157 is " << (sieve.is_prime(157) ? "prime number" : "not prime number") << '\n';

}
