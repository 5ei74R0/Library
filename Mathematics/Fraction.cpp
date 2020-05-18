//
// Created by OtsuKotsu on 2020/05/18.
//
// Fraction
// 既約分数クラス
//
//  Operator:
//      +, -, *, /, +=, -=, *=, /=, =
//      ==, !=, <, <=, >, >=
//
//  Function:
//      inverse(): 分子分母の入れ替え
//      reduce(): 約分
//      err_0_division: 0除算を検知して異常終了

#include<bits/stdc++.h>

class Fraction {
    using i64 = int_fast64_t;
private:
    static i64 inline GCD(i64 a, i64 b) { return (b ? GCD(b, a%b) : a); }
    void inline reduce() noexcept {
        i64 g = GCD(numerator, denominator);
        numerator /= g;
        denominator /= g;
        if(numerator >= 0 && denominator < 0) {  // 分母をマイナスにしない
            numerator *= -1, denominator *= -1;
        }
    };
    void inline err_0_division(i64 p = 1) noexcept {
        if(denominator==0 || p==0) std::abort();
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
    bool operator == (const Fraction &F) noexcept {
        return numerator == F.numerator && denominator == F.denominator;
    }
    bool operator != (const Fraction &F) noexcept {
        return numerator != F.numerator || denominator != F.denominator;
    }
    bool operator < (Fraction F) noexcept {
        return this->convert() < F.convert();
    }
    bool operator <= (Fraction F) noexcept {
        return this->convert() < F.convert() || *this==F;
    }
    bool operator > (Fraction F) noexcept {
        return this->convert() > F.convert();
    }
    bool operator >= (Fraction F) noexcept {
        return this->convert() > F.convert() || *this==F;
    }
    Fraction operator + (const Fraction F) noexcept { return Fraction(*this += F);}
    Fraction operator - (const Fraction F) noexcept { return Fraction(*this) -= F;}
    Fraction operator * (const Fraction F) noexcept { return Fraction(*this) *= F;}
    Fraction operator / (const Fraction F) noexcept { return Fraction(*this) /= F;}
    Fraction &operator = (const std::pair<i64, i64> P) noexcept {
        std::tie(numerator, denominator) = P;
        err_0_division();
        reduce();
    }
    Fraction &operator = (const Fraction F) noexcept {
        numerator = F.numerator, denominator = F.denominator;
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
    Fraction a(123, 459), b;
    b = make_pair(123, 456);

    if(a <= b) cout << "a is smaller than b." << '\n';

    cout << a.numerator << '\n';
    cout << a.denominator << '\n';
    cout << b.numerator << '\n';
    cout << b.denominator << '\n';

    auto sum = a+b;

    cout << sum.numerator << '\n';
    cout << sum.denominator << '\n';
}