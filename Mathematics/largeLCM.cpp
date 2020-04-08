//
// Created on 2020/04/09.
//
// Dependency:
//      ./ModInt.cpp
//
// Description:
//      64bit整数に収まらない最小公倍数を素因数分解された形で生成する
//      コンストラクタはない
//      calcメソッドで val と 引数x の最小公倍数を計算する
//      convertメソッドで valを　modint に変換した値を返す
//
//

/* Large LCM */
class largeLCM {
private:
    std::map<int, int> val;
public:
    void calc(int_fast32_t x) noexcept {
        std::map<int, int> v_X;
        int_fast32_t X = x;
        for(int i = 2; i*i <= x; ++i) {
            while(X%i == 0) {
                ++v_X[i];
                X /= i;
            }
        }
        if(X != 1) v_X[X] = 1;
        for(auto p : v_X) val[p.first] = std::max(val[p.first], p.second);
    }
    modint<mod> convert() const noexcept {
        modint<mod> ret = 1;
        for(auto p : val) ret *= modint<mod>(p.first).pow(p.second);
        return ret;
    }
};
