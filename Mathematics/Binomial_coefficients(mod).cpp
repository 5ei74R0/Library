// renamed by OtsuKotsu on 2020/07/06
//
// Class - Binomial -
// precalculate binomial coefficients
//


#include <bits/stdc++.h>

/*Binomial=============================================*/
class Binomial {
private:
    const int MAX;
    const int MOD;
    std::vector<long long> fac, finv, inv;

public:
    Binomial(int MAX = 510000, int MOD = 1000000007): MAX(MAX), MOD(MOD)
    {
        fac.resize(MAX);
        finv.resize(MAX);
        inv.resize(MAX);
        // Build'Binomial-table'
        fac[0] = fac[1] = 1;
        finv[0] = finv[1] = 1;
        inv[1] = 1;
        for (int i = 2; i < MAX; i++){
            fac[i] = fac[i - 1] * i % MOD;
            inv[i] = MOD - inv[MOD%i] * (MOD / i) % MOD;
            finv[i] = finv[i - 1] * inv[i] % MOD;
        }
    }

    long long calc(int n, int k){
        if (n < k) return 0;
        if (n < 0 || k < 0) return 0;
        return fac[n] * (finv[k] * finv[n - k] % MOD) % MOD;
    }
};
