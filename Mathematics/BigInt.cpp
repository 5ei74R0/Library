//
// Created on 2020/04/09.
//
// Dependency:
//      no dependency.
//
// Description:
//      calculations:
//          +=, -=, +, -
//      others:
//          =(std::string), =(bigInt),
//          iostream,
//          digit(): 桁数を返す,
//          convert(): std::string型へ変換
//
//      多倍長整数。
//      現状では非負整数の加減算のみ行える。
//      機能は少しずつ増える予定です
//

#include <bits/stdc++.h>

class bigInt {
private:
    std::vector<int_fast8_t> val;  // 1-indexed

public:
// functions
    friend std::ostream &operator<<(std::ostream &os, bigInt &x) {
        return os << x.convert();
    }
    friend std::istream &operator>>(std::istream &is, bigInt &x) {
        std::string tmp;
        is >> tmp;
        x.val.assign(tmp.size()+1, 0);
        for(int i = 1; i <= tmp.size(); ++i) x.val[i] = tmp[tmp.size()-i]-'0';
        return is;
    }
    int digit() {
        return (int)val.size()-1;
    }
    std::string convert() {
        std::string ret;
        for(int i = 1; i <= digit(); ++i) {
            ret = (char)(val[i]+'0') + ret;
        }
        return ret;
    }

// operators
    bigInt &operator=(bigInt b) noexcept {
        val = b.val;
        return *this;
    }
    bigInt &operator=(std::string b) noexcept {
        val.assign(b.size()+1, 0);
        for(int i = 1; i <= b.size(); ++i) val[i] = b[b.size()-i]-'0';
        return *this;
    }
    bigInt &operator+=(bigInt b) noexcept {
        int up = 0;
        for(int i = 1; i <= b.digit(); ++i) {
            if(i >= val.size()) val.push_back(0);
            val[i] += b.val[i] + up;
            if(val[i] > 9) {
                val[i] -= 10;
                up = 1;
            }
            else up = 0;
        }
        return *this;
    }
    bigInt &operator-=(bigInt b) noexcept {
        for(int i = 0; i <= b.digit(); ++i) {
            val[i] -= b.val[i];
            if(val[i] < 0) {
                --val[i+1];
                val[i] += 10;
            }
        }
        return *this;
    }
//    bigInt &operator*=(bigInt b) noexcept {
//        std::vector<int_fast8_t> ret(val.size() + b.val.size() + 2);
//
//    }

    bigInt operator+(bigInt const b) noexcept { return bigInt(*this) += b; }
    bigInt operator-(bigInt const b) noexcept { return bigInt(*this) -= b; }
};



/*verify==================================================*/
signed main(){
    using namespace std;
    cin.tie(nullptr);
    ios::sync_with_stdio(false);   //cin cout 高速化


    bigInt a, b, c;
    cin >> a >> b >> c;
    cout << "a: " << a << '\n' << "b: " << b << '\n' << "c: " << c << '\n';
    bigInt d = a+b, e = a+b-c;
    cout << "a + b = " << d << '\n';
    cout << "a + b - c = " << e << '\n';

}
