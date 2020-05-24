//
// Created by OtsuKotsu on 2020/05/18.
//
// Fraction
// 既約分数クラス
//
//  Operator:
//      +, -, *, /, +=, -=, *=, /=, =
//      ==, !=, <, <=, >, >=
//      ostream<<  : long doubleに変換して出力
//
//  Function:
//      inverse() : 分子分母の入れ替え
//      reduce()  : 約分
//      err_0_division  : 0除算を検知して異常終了

#include<bits/stdc++.h>

class Fraction {
    using i64 = int_fast64_t;
private:
    static i64 inline GCD(i64 a, i64 b) { return (b ? GCD(b, a%b) : a); }
    void inline reduce() noexcept {
        i64 g = GCD(std::abs(numerator), std::abs(denominator));
        numerator /= g;
        denominator /= g;
        if(denominator < 0) {  // 分子+で分母- or 分子分母共に- -> 符号反転
            numerator *= -1, denominator *= -1;
        }
    };
    void inline err_0_division() noexcept {
        if(denominator==0) std::abort();
    }
    long double inline convert() noexcept { return (long double)numerator/(long double)denominator; }
public:
    i64 numerator, denominator;
    Fraction(i64 Numerator = 0, i64 Denomirator = 1): numerator(Numerator), denominator(Denomirator) {
        err_0_division();
        reduce();
    };
    void inline inverse() {
        i64 tmp = denominator;
        denominator = numerator;
        numerator = tmp;
    }
    friend std::ostream &operator<<(std::ostream &os, const Fraction &F) {
        Fraction tmp = F;
        return os << tmp.convert();
    }
    inline bool operator == (const Fraction &F) const noexcept {
        return numerator == F.numerator && denominator == F.denominator;
    }
    inline bool operator != (const Fraction &F) const noexcept {
        return !(*this==F);
    }
    inline bool operator <= (const Fraction &F) const noexcept {
        Fraction slf = *this, tmp = F;
        return slf.convert() < tmp.convert() || *this==F;
    }
    inline bool operator >= (const Fraction &F) const noexcept {
        Fraction slf = *this, tmp = F;
        return slf.convert() > tmp.convert() || *this==F;
    }
    inline bool operator < (const Fraction &F) const noexcept {
        return !(*this>=F);
    }
    inline bool operator > (const Fraction &F) const noexcept {
        return !(*this<=F);
    }
    Fraction operator + (const Fraction F) noexcept { return Fraction(*this += F);}
    Fraction operator - (const Fraction F) noexcept { return Fraction(*this) -= F;}
    Fraction operator * (const Fraction F) noexcept { return Fraction(*this) *= F;}
    Fraction operator / (const Fraction F) noexcept { return Fraction(*this) /= F;}
    Fraction &operator = (const std::pair<i64, i64> P) noexcept {
        std::tie(numerator, denominator) = P;
        err_0_division();
        reduce();
        return *this;
    }
    Fraction &operator = (const Fraction F) noexcept {
        numerator = F.numerator, denominator = F.denominator;
        return *this;
    }
    Fraction &operator += (const Fraction F) noexcept {
        i64 g = GCD(denominator, F.denominator);
        numerator = numerator * (F.denominator/g) + F.numerator * (denominator/g);
        denominator = denominator/g * F.denominator;
        reduce();
        return *this;
    }
    Fraction &operator -= (const Fraction F) noexcept {
        i64 g = GCD(denominator, F.denominator);
        numerator = numerator * (F.denominator/g) - F.numerator * (denominator/g);
        denominator = denominator/g * F.denominator;
        reduce();
        return *this;
    }
    Fraction &operator *= (const Fraction F) noexcept {
        i64 g1 = GCD(numerator, F.denominator);
        i64 g2 = GCD(F.numerator, denominator);
        numerator = (numerator/g1) * (F.numerator/g2);
        denominator = (denominator/g2) * (F.denominator/g1);
        reduce();
        return *this;
    }
    Fraction &operator /= (const Fraction F) noexcept {
        Fraction f = F;
        f.inverse();
        *this *= f;
        reduce();
        return *this;
    }
};




// verify
int main () {
    using namespace std;

    // verify construct and input
    Fraction a(48, -36), b = {-16, -27};

    printf("\nverify reduce\n");  // verify reduce
    cout << a.numerator << '\n';
    cout << a.denominator << '\n';
    cout << b.numerator << '\n';
    cout << b.denominator << '\n';

    printf("\nverify calculation\n");  // verify calculation
    auto sum = a+b;
    auto diff = a-b;
    auto multi = a*b;
    auto div = a/b;
    cout << sum.numerator << '\n';
    cout << sum.denominator << '\n';
    cout << diff.numerator << '\n';
    cout << diff.denominator << '\n';
    cout << multi.numerator << '\n';
    cout << multi.denominator << '\n';
    cout << div.numerator << '\n';
    cout << div.denominator << '\n';

    printf("\nverify =\n");  // verify =
    a = b;
    cout << a.numerator << '\n';
    cout << a.denominator << '\n';
    cout << b.numerator << '\n';
    cout << b.denominator << '\n';

    printf("\nverify output and compare\n");  // verify output and compare
    std::priority_queue<Fraction> pq;
    for (int i = -5; i < 5; ++i) {
        for (int j = -5; j < 5; ++j) if(j != 0) {
                pq.push(Fraction(i,j));
            }
    }

    while (!pq.empty()) {
        cout << pq.top() << '\n';
        pq.pop();
    }


    // !!! verify abort() on 0_division !!!
//    Fraction zeroParZero;
//    zeroParZero = make_pair(321, 0);
//    cout << zeroParZero << '\n';
}