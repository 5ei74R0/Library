#include<bits/stdc++.h>

const int mod = 1e9+7;
/*MOD int=============================*/
template<std::int_fast64_t Mod>
class modint {
public:
    using i64 = std::int_fast64_t;
    i64 val;
    //constructor
    constexpr modint(const i64 p=0) noexcept : val(p>=0 ? p%Mod : (Mod+(p%Mod))%Mod) {}

    //std::cin, std::cout
    friend std::ostream &operator<<(std::ostream &os, const modint &x) {
        return os << x.val;
    }
    friend std::istream &operator>>(std::istream &is, modint &x) {
        is >> x.val;
        x.val %= Mod;
        if(x.val < 0) x.val += Mod;  // <- 負数対応
        return is;
    }

    //operator
    constexpr modint operator+(const modint b) const noexcept { return modint(*this) += b; }

    constexpr modint operator-(const modint b) const noexcept { return modint(*this) -= b; }

    constexpr modint operator*(const modint b) const noexcept { return modint(*this) *= b; }

    constexpr modint operator/(const modint b) const noexcept { return modint(*this) /= b; }

    constexpr modint operator-() const noexcept { return modint() - *this; }

    constexpr bool operator==(const modint &b) const noexcept { return this->val == b.val; }

    constexpr bool operator!=(const modint &b) const noexcept { return this->val != b.val; }

    constexpr modint &operator=(const modint b) noexcept {
        val = b.val;
        return *this;
    }
    constexpr modint &operator=(const i64 b) noexcept {
        val = modint<Mod>(b).val;
        return *this;
    }
    constexpr modint &operator+=(const modint b) noexcept {
        if((val += b.val) >= Mod) val -= Mod;
        return *this;
    }
    constexpr modint &operator-=(const modint b) noexcept {
        if(val < b.val) val += Mod;
        val -= b.val;
        return *this;
    }
    constexpr modint &operator*=(const modint b) noexcept {
        val = val * b.val % Mod;
        return *this;
    }
    constexpr modint &operator/=(modint b) noexcept {
        val *= b.inverse().val;
        val %= Mod;
        return *this;
    }
    constexpr modint inverse() noexcept {
        i64 m=Mod, u=1, v=0, t=1;
        while(m) {
            t = val/m;
            val -= t*m; std::swap(val,m);
            u -= t*v; std::swap(u,v);
        }
        return modint(u);
    }
    // calc val^n
    constexpr  modint pow(i64 n) noexcept {
        modint res = 1, a = val;
        while(n > 0) {
            if(n & 1) res = res * a;
            a = a * a;
            n >>= 1;
        }
        return res;
    }
};
using mint = modint<mod>;

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


// verify -----------------------------
int main() {
    using namespace std;
//    verify input operator
    mint x, y;
    cin >> x >> y;

//    verify calc operator
    x /= y;
    cout << x << '\n';
    x *= y;
    cout << x << '\n';

//    verify "==" and "!="
    mint z, Z = mint(1000000007);
    cin >> z;
    if(z == Z) cout << "equal" << '\n';
    else if (z != Z) cout << "Not equal" << '\n';

//    verify a^n
    mint a;
    long long n;
    cin >> a >> n;
    cout << a.pow(n) << '\n';
}
