//
// Created on 2020/04/08.
//
// !!!!!CAUTION!!!!!
//   IN SOME CASES, THIS CLASS "largeInt" IS NOT ABLE TO CALCULATE IN PRACTICAL TIME
//
// short description:
//      calc: *, /, *=, /= (largeInt)
//      compare: ==, != (largeInt)
//      assign: = (int_fast64_t, or largeInt)
//      I/O: cin, cout  -> return modint<mod>
//      convert: convert largeInt to modint<mod>
//
// dependency:
//      ./ModInt.cpp
//

/* Large Integer */
class largeInt {
private:
    std::map<int, int> val;
public:
    // constructor
    largeInt(const int_fast64_t a = 0) {
        int_fast64_t A = a;
        std::map<int, int> ret;
        for(int i = 2; i*i <= A; i++){
            while(A % i == 0){
                ret[i]++;
                A /= i;
            }
        }
        if(A != 1) ret[A] = 1;
        val = ret;
    }
    //std::cin, std::cout
    friend std::ostream &operator<<(std::ostream &os, largeInt &x) {
        return os << x.convert();
    }
    friend std::istream &operator>>(std::istream &is, largeInt &x) {
        int_fast64_t integer;
        is >> integer;
        x = integer;
        return is;
    }

    largeInt &operator=(const largeInt b) noexcept {
        val = b.val;
        return *this;
    }
    largeInt &operator=(const int_fast64_t b) noexcept {
        int_fast64_t B = b;
        std::map<int, int> ret;
        for(int i = 2; i*i <= B; i++){
            while(B % i == 0){
                ret[i]++;
                B /= i;
            }
        }
        if(B != 1) ret[B] = 1;
        val = ret;
    }
    largeInt &operator*=(const largeInt b) noexcept {
        for(auto p : b.val) val[p.first] += p.second;
        return *this;
    }
    largeInt &operator/=(const largeInt b) noexcept {
        for(auto p : b.val) val[p.first] -= p.second;
        return *this;
    }
    largeInt operator*(const largeInt b) const noexcept { return largeInt(*this) *= b; }
    largeInt operator/(const largeInt b) const noexcept { return largeInt(*this) /= b; }
    bool operator==(const largeInt &b) const noexcept { return this->val == b.val; }
    bool operator!=(const largeInt &b) const noexcept { return this->val != b.val; }

    largeInt lcm(largeInt X) {
        largeInt ret = *this;
        for (auto p : X.val) {
            ret.val[p.first] = std::max(ret.val[p.first], p.second);
        }
        return ret;
    }
    largeInt gcd(largeInt X) {
        largeInt ret = *this;
        for(auto p : X.val) {
            ret.val[p.first] = std::min(ret.val[p.first], p.second);
        }
        return ret;
    }

    modint<mod> convert() noexcept {
        modint<mod> ret = 1, tmp;
        for(auto p : val) {
            tmp = p.first;
            tmp = tmp.pow(std::abs(p.second));
            if(0 <= p.second) ret *= tmp;
            else ret /= tmp;
        }
        return ret;
    }
};