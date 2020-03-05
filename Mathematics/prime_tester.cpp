#include <bits/stdc++.h>

// prime tester

bool prime_test(int num) {
    if (num < 2) return false;
    else if (num == 2) return true;
    else if (num % 2 == 0) return false;

    int sqrtNum = sqrt(num);
    for (int i = 3; i <= sqrtNum; i += 2){
        if (num % i == 0) return false;
    }

    return true;
}