#include <bits/stdc++.h>

// enumerate divisor of N

std::vector<int> divisor(int n){
    std::vector<int> ret;
    for(int i = 1; i * i <= n; i++){
        if(n % i == 0){
            ret.push_back(i);
            if(i * i != n) ret.push_back(n / i);
        }
    }
    std::sort(ret.begin(), ret.end());
    return ret;
}
